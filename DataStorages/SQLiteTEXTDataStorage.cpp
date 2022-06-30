#include "SQLiteTEXTDataStorage.hpp"

void SQLiteTEXTDataStorage::store(const int event, const std::string component, const std::string buffer)
{
    char *zErrMsg = 0;
    int rc;

    std::stringstream stream;
    stream << "BEGIN TRANSACTION; INSERT INTO trace VALUES(NULL," << nanosecondsSinceEpoch() << "," << event << ",'" << component << "','" << buffer << "'); COMMIT;";

    std::string sqlString = stream.str();
    const char *sql = sqlString.c_str();

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        throw std::runtime_error("SQLite Error: INSERT INTO");
    }
}

std::string SQLiteTEXTDataStorage::getName()
{
    return "SQLiteTEXT";
}
