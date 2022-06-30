#include <iostream>
#include "Encoder/TextEncoder.hpp"
#include "Encoder/ProtobufEncoder.hpp"
#include "ConcreteDataStructure/Person.hpp"
#include "DataStorages/FileDataStorage.hpp"
#include "DataStorages/PrintDataStorage.hpp"
#include "DataStorages/VoidDataStorage.hpp"
#include "DataStorages/SQLiteTEXTDataStorage.hpp"
#include "DataStorages/SQLiteBLOBDataStorage.hpp"
#include <memory>
#include <string>
#include "Scenario.hpp"
#include <algorithm>
#include <fstream>
#include <chrono>
#include <nlohmann/json.hpp>
#include "ConcreteScenarios/PersonScenario.hpp"
#include <sys/stat.h>

enum EncoderEnum
{
    Text,
    Protobuf,
    Capnproto
};

enum DataStorageEnum
{
    File,
    SQLiteTEXT,
    SQLiteBLOB,
    Print,
    Void
};

enum ScenarioEnum
{
    Person
};

EncoderEnum getEncoderEnumFromString(std::string str)
{
    // transform str to lower characters
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    if (str == "text")
        return Text;
    if (str == "protobuf")
        return Protobuf;
    if (str == "capnproto")
        return Capnproto;

    throw std::runtime_error("Invalid str in getEncoderEnumFromString(std::string str)");
}

DataStorageEnum getDataStorageEnumFromString(std::string str)
{
    // transform str to lower characters
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    if (str == "file")
        return File;
    if (str == "sqlitetext")
        return SQLiteTEXT;
    if (str == "sqliteblob")
        return SQLiteBLOB;
    if (str == "print")
        return Print;
    if (str == "void")
        return Void;

    throw std::runtime_error("Invalid str in getDataStorageEnumFromString(std::string str)");
}

ScenarioEnum getScenarioEnumFromString(std::string str)
{
    // transform str to lower characters
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    if (str == "person")
        return Person;

    throw std::runtime_error("Invalid str in getScenarioEnumFromString(std::string str)");
}

std::string getStringFromScenarioEnum(ScenarioEnum scenario)
{
    switch (scenario)
    {
    case Person:
        return "Person";

    default:
        throw std::runtime_error("Invalid enum in getStringFromScenarioEnum(ScenarioEnum enum)");
    }
}

std::shared_ptr<IEncoder> getEncoderPointer(EncoderEnum encoder)
{
    std::shared_ptr<IEncoder> pointer;

    switch (encoder)
    {
    case Text:
        pointer = std::make_shared<TextEncoder>();
        break;

    case Protobuf:
        pointer = std::make_shared<ProtobufEncoder>();
        break;

    case Capnproto:
        // pointer = std::make_shared<CapnprotoEncoder>();
        break;

    default:
        throw std::runtime_error("Invalid encoder in getEncoderPointer(EncoderEnum encoder)");
    }
    return pointer;
}

std::shared_ptr<IDataStorage> getDataStoragePointer(DataStorageEnum dataStorage, std::string filename = "")
{
    std::string path = "StoragedData";
    std::shared_ptr<IDataStorage> pointer;

    switch (dataStorage)
    {
    case File:
        if (filename == "")
        {
            mkdir(path.c_str(), 0777);
            filename = path + "/file.txt";
        }
        pointer = std::make_shared<FileDataStorage>(filename);
        break;

    case SQLiteTEXT:
        if (filename == "")
        {
            mkdir(path.c_str(), 0777);
            filename = path + "/sqliteTEXT.db";
        }
        pointer = std::make_shared<SQLiteTEXTDataStorage>(filename);
        break;

    case SQLiteBLOB:
        if (filename == "")
        {
            mkdir(path.c_str(), 0777);
            filename = path + "/sqliteTEXT.db";
        }
        pointer = std::make_shared<SQLiteBLOBDataStorage>(filename);
        break;

    case Print:
        pointer = std::make_shared<PrintDataStorage>();
        break;

    case Void:
        pointer = std::make_shared<VoidDataStorage>();
        break;

    default:
        throw std::runtime_error("Invalid dataStorage in getDataStoragePointer(DataStorageEnum dataStorage, std::string filename = \"\")");
    }

    return pointer;
}

std::shared_ptr<Scenario> getScenarioPointer(ScenarioEnum scenario, std::shared_ptr<IEncoder> encoder, std::shared_ptr<IDataStorage> dataStorage)
{
    std::string subfolder = "TimeResults";
    mkdir(subfolder.c_str(), 0777);

    // get filename to write time durations to
    std::stringstream stream;
    stream << subfolder << "/" << getStringFromScenarioEnum(scenario) << encoder->getName() << "To" << dataStorage->getName() << ".csv";
    std::string timeFile = stream.str();

    // make handle to write time durations to file
    auto handle = std::make_shared<std::fstream>();
    handle->open(timeFile, std::fstream::app | std::fstream::out);
    if (handle->is_open() == false)
    {
        throw std::runtime_error("Couldn't open file handle");
    }

    std::shared_ptr<Scenario> pointer;

    switch (scenario)
    {
    case Person:
        pointer = std::make_shared<PersonScenario>(encoder, dataStorage, handle);
        break;

    default:
        throw std::runtime_error("Invalid scenario in getScenarioPointer(ScenarioEnum scenario, std::shared_ptr<IEncoder> encoder, std::shared_ptr<IDataStorage> dataStorage)");
    }

    return pointer;
}

std::shared_ptr<Scenario> scenarioFactory(ScenarioEnum scenario, EncoderEnum encoder, DataStorageEnum dataStorage, std::string filename = "")
{
    auto encoderPointer = getEncoderPointer(encoder);
    auto dataStoragePointer = getDataStoragePointer(dataStorage, filename);
    return getScenarioPointer(scenario, encoderPointer, dataStoragePointer);
}

std::vector<std::shared_ptr<Scenario>> readScenarios(std::string jsonFilename)
{
    std::vector<std::shared_ptr<Scenario>> scenarios;

    // open json file with name of jsonFilename
    std::fstream jsonFile;
    jsonFile.open(jsonFilename);
    if (jsonFile.is_open() == false)
    {
        throw std::runtime_error("Couldn't open json input file '" + jsonFilename + "'");
    }

    nlohmann::json j;
    j << jsonFile;

    // read json file and fill scenarios vector with content
    auto scenarioPointers = j["scenarioPointers"];
    for (auto &s : scenarioPointers)
    {
        ScenarioEnum scenario = getScenarioEnumFromString(s["scenario"]);
        EncoderEnum encoder = getEncoderEnumFromString(s["encoder"]);
        DataStorageEnum dataStorage = getDataStorageEnumFromString(s["dataStorage"]);
        std::string filename = "";
        if (s["filename"].is_null() == false)
            filename = s["filename"];

        scenarios.push_back(scenarioFactory(scenario, encoder, dataStorage, filename));
    }

    return scenarios;
}

void executeScenarios(std::vector<std::shared_ptr<Scenario>> scenarios)
{
    for (auto &s : scenarios)
    {
        std::cout << s->describe() << std::endl;
        s->execute();
    }
}

std::string getJsonFilename(int argc, char *argv[])
{
    // check if some argument is "--input=[filename]"
    for (int i = 1; i < argc; ++i)
    {
        std::string argument = argv[i];
        std::transform(argument.begin(), argument.end(), argument.begin(), ::tolower);
        if (argument.rfind("--input=", 0) == 0)
        {
            argument.erase(0, 8);
            if (argument.empty() == false)
            {
                return argument;
            }
        }
    }

    return "main.json";
}

int main(int argc, char *argv[])
{
    try
    {
        auto jsonFilename = getJsonFilename(argc, argv);
        auto scenarios = readScenarios(jsonFilename);
        executeScenarios(scenarios);
    }
    catch (std::runtime_error &error)
    {
        std::cout << "Error while executing: " << error.what() << std::endl;
        return -1;
    }
    return 0;
}
