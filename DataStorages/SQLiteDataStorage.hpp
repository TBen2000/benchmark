#pragma once
#include "../IDataStorage.hpp"
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>

class SQLiteDataStorage : public IDataStorage
{
protected:
    sqlite3 *db;

    static int callback(void *NotUsed, int argc, char **argv, char **azColName)
    {
        int i;
        for (i = 0; i < argc; i++)
        {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }

public:


    SQLiteDataStorage(std::string filename, std::string bufferType)
    {
        char *zErrMsg = 0;
        int rc;

        if (bufferType != "TEXT" && bufferType != "BLOB")
            throw std::runtime_error("invalid argument in SQLiteDataStorage(std::string filename, std::string bufferType)");

        std::stringstream stream;
        stream << "CREATE TABLE IF NOT EXISTS trace" << bufferType << " (id INTEGER PRIMARY KEY, timestamp INTEGER NOT NULL, event INT NOT NULL, component TEXT NOT NULL, buffer " << bufferType << " NOT NULL);";
        std::string sqlString = stream.str();
        const char *sql = sqlString.c_str();

        rc = sqlite3_open(filename.c_str(), &db);

        if (rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            throw std::runtime_error("SQLite Error: Can't open database");
        }

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            throw std::runtime_error("SQLite Error: CREATE TABLE");
        }
    }

    ~SQLiteDataStorage()
    {
        sqlite3_close(db);
    }

    virtual void store(const int event, const std::string component, const std::string buffer) = 0;
    virtual std::string getName() = 0;
};
