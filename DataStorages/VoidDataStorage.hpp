#pragma once
#include "../IDataStorage.hpp"

class VoidDataStorage : public IDataStorage
{
public:
    virtual void store(const int event, const std::string component, const std::string buffer);
    virtual std::string getName();
};
