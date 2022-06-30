#pragma once
#include "SQLiteDataStorage.hpp"

class SQLiteTEXTDataStorage : public SQLiteDataStorage
{
public:
    SQLiteTEXTDataStorage(std::string filename) : SQLiteDataStorage(filename, "TEXT") {}
    virtual void store(const int event, const std::string component, const std::string buffer);
    virtual std::string getName();
};
