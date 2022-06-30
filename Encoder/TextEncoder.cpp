#include "TextEncoder.hpp"
#include <string>

std::string TextEncoder::encode(std::shared_ptr<IDataStructure> structure)
{
    std::string data = structure->describe();
    return data;
}

std::string TextEncoder::getName()
{
    return "Text";
}
