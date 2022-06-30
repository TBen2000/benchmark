#pragma once
#include "../IEncoder.hpp"

class TextEncoder : public IEncoder
{
public:
    virtual std::string encode(std::shared_ptr<IDataStructure> structure);
    virtual std::string getName();
};