#pragma once
#include "IDataStructure.hpp"
#include <memory>

class IEncoder
{
public:
    virtual std::string encode(std::shared_ptr<IDataStructure> pointer) = 0;
    virtual std::string getName() = 0;
};
