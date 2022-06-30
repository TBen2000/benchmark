#include "FileDataStorage.hpp"
#include <iostream>
#include <fstream>

void FileDataStorage::store(const int event, const std::string component, const std::string buffer)
{
    std::stringstream stream;
    stream << datetime() << "|" << event << "|" << component << "|" << buffer << std::endl;

    std::string outputBuffer = stream.str();

    if (file)
        std::fwrite(outputBuffer.c_str(), sizeof(char), outputBuffer.size(), file);
}

std::string FileDataStorage::getName()
{
    return "File";
}