#pragma once
#include "../IDataStorage.hpp"
#include <iostream>

class FileDataStorage : public IDataStorage
{
private:
    FILE *file;

public:
    FileDataStorage(const std::string filename)
    {
        file = std::fopen(filename.c_str(), "ab");
    }

    ~FileDataStorage()
    {
        std::fclose(file);
    }

    virtual void store(const int event, const std::string component, const std::string buffer);
    virtual std::string getName();
};
