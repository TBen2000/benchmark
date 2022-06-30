#pragma once
#include <string>
#include <vector>
#include "../IDataStructure.hpp"
#include <iostream>
#include <sstream>
#include "../IDs.hpp"
#include <algorithm>

enum PhoneType
{
    MOBILE = 0,
    HOME = 1,
    WORK = 2
};

static PhoneType getPhoneTypeEnumFromString(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    if (str == "mobile")
        return MOBILE;
    if (str == "home")
        return HOME;
    if (str == "work")
        return WORK;

    throw std::runtime_error("Invalid str in getPhoneTypeEnumFromString(std::string str)");
}


class PhoneNumber : public IDataStructure
{
private:
    int id = PhoneNumberID;
    std::string number;
    PhoneType type;

public:
    PhoneNumber(std::string number, PhoneType type)
    {
        this->number = number;
        this->type = type;
    }

    std::string getNumber()
    {
        return number;
    }

    PhoneType getNumberType()
    {
        return type;
    }

    virtual std::string describe() override
    {
        std::stringstream stream;
        stream << type << ": " << number;
        return stream.str();
    }

    virtual int getID() override
    {
        return id;
    }
};

class Person : public IDataStructure
{
private:
    int id = PersonID;
    std::string name;
    int personID;
    std::string email;
    std::vector<PhoneNumber> numbers;

public:
    Person(std::string name, int personID, std::string email, std::vector<PhoneNumber> numbers)
    {
        this->name = name;
        this->personID = personID;
        this->email = email;
        this->numbers = numbers;
    }

    std::string getName()
    {
        return name;
    }

    std::string getEmail()
    {
        return email;
    }

    std::vector<PhoneNumber> getNumbers()
    {
        return numbers;
    }

    virtual std::string describe() override
    {
        std::stringstream numberstream;
        for (PhoneNumber &num : numbers)
        {
            numberstream << ", " << num.describe();
        }

        std::stringstream stream;
        stream << personID << ", " << name << ", " << email << numberstream.str();
        return stream.str();
    }

    virtual int getID() override
    {
        return id;
    }
};
