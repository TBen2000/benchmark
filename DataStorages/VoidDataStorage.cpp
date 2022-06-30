#include "VoidDataStorage.hpp"
#include <string>

void VoidDataStorage::store(const int event, const std::string component, const std::string buffer) {}

std::string VoidDataStorage::getName()
{
    return "Void";
}