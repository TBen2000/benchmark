#include "PrintDataStorage.hpp"
#include <iostream>

void PrintDataStorage::store(const int event, const std::string component, const std::string buffer)
{
    std::cout << datetime() << "|" << eventLookupTable[event] << "|" << component << "|" << buffer << std::endl;
}

std::string PrintDataStorage::getName()
{
    return "Print";
}
