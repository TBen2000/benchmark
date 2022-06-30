#pragma once
#include "../Scenario.hpp"
#include "../ConcreteDataStructure/Person.hpp"

class PersonScenario : public Scenario
{
public:
    PersonScenario(std::shared_ptr<IEncoder> encoder, std::shared_ptr<IDataStorage> dataStorage, FilePtr handle) : Scenario(encoder, dataStorage, handle) {}
    virtual void execute();
    virtual std::string getName();
};