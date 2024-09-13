#pragma once

#include "Types.hpp"

namespace margelo::rnquicksqlite {

SQLiteOperationResult sqliteOpenDb(const std::string& dbName, const std::string& docPath);

SQLiteOperationResult sqliteCloseDb(const std::string& dbName);

SQLiteOperationResult sqliteRemoveDb(const std::string& dbName, const std::string& docPath);

SQLiteOperationResult sqliteAttachDb(const std::string& mainDBName, const std::string& docPath, const std::string& databaseToAttach,
                              const std::string& alias);

SQLiteOperationResult sqliteDetachDb(const std::string& mainDBName, const std::string& alias);

SQLiteExecuteQueryResult sqliteExecute(const std::string& dbName, const std::string& query, const std::optional<SQLiteQueryParams>& params);

SQLiteLiteralUpdateResult sqliteExecuteLiteral(const std::string& dbName, const std::string& query);

void sqliteCloseAll();

} // namespace margelo::rnquicksqlite
