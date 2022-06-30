#pragma once
#include "../IEncoder.hpp"
#include <iostream>

class ProtobufEncoder : public IEncoder
{
public:
    virtual std::string encode(std::shared_ptr<IDataStructure> structure);
    virtual std::string getName();
};
