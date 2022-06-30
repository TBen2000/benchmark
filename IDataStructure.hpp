#pragma once
#include <string>


class IDataStructure
{
public:
    virtual std::string describe() = 0;
    virtual int getID() = 0;
};
