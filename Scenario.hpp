#pragma once
#include "IEncoder.hpp"
#include "IDataStorage.hpp"
#include <fstream>


using FilePtr = std::shared_ptr<std::fstream>;


class Scenario
{
protected:
    std::shared_ptr<IEncoder> encoder;
    std::shared_ptr<IDataStorage> dataStorage;
    FilePtr handle;

public:
    Scenario(std::shared_ptr<IEncoder> encoder, std::shared_ptr<IDataStorage> dataStorage, FilePtr handle)// : handle(handle)
    {
        this->encoder = encoder;
        this->dataStorage = dataStorage;
        this->handle = handle;
    }
    virtual ~Scenario()
    {
        handle->close();
    }

    std::string describe()
    {
        std::stringstream stream;
        stream << this->getName() << " Scenario" << ": " << encoder->getName() << " Encoder to " << dataStorage->getName() << " DataStorage" << std::endl;
        return stream.str();
    }

    virtual std::string getName() = 0;
    virtual void execute() = 0;
};
