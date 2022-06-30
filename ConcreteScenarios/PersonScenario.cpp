#include "PersonScenario.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include "../Measure.hpp"

void PersonScenario::execute()
{
    std::fstream file;
    file.open("./ConcreteScenarios/person.json");
    nlohmann::json j;
    j << file;

    auto entries = j["entries"];

    for (auto &e : entries)
    {
        int event = 0;
        std::string component = "None";
        std::string name = "None";
        int personID = 0;
        std::string email = "None";
        std::vector<PhoneNumber> numbers;

        if (e["event"].is_null() == false)
            event = e["event"];
        if (e["component"].is_null() == false)
            component = e["component"];
        if (e["object"].is_null() == false)
        {
            auto o = e["object"];

            if (o["name"].is_null() == false)
                name = o["name"];
            if (o["personID"].is_null() == false)
                personID = o["personID"];
            if (o["email"].is_null() == false)
                email = o["email"];
            if (o["numbers"].is_null() == false)
            {
                auto numberObjects = o["numbers"];

                for (auto &n : numberObjects)
                {
                    std::string number = n["number"];
                    std::string type = n["type"];

                    PhoneNumber pn(number, getPhoneTypeEnumFromString(type));
                    numbers.push_back(pn);
                }
            }

            auto data = std::make_shared<Person>(name, personID, email, numbers);

            struct EncodeDataMeasurement measurement = callMeasureEncoderStep(encoder, data);
            int64_t storeDuration = callMesureStoreDataStep(dataStorage, event, component, measurement.buffer);

            saveTimespan(measurement.duration, storeDuration, handle);
        }
    }
}

std::string PersonScenario::getName()
{
    return "Person";
}
