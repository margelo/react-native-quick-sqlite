#pragma once

#include "Types.hpp"

namespace margelo::rnquicksqlite {

SQLiteOPResult sqliteOpenDb(const std::string& dbName, const std::string& docPath);

SQLiteOPResult sqliteCloseDb(const std::string& dbName);

SQLiteOPResult sqliteRemoveDb(const std::string& dbName, const std::string& docPath);

SQLiteOPResult sqliteAttachDb(const std::string& mainDBName, const std::string& docPath, const std::string& databaseToAttach, const std::string& alias);

SQLiteOPResult sqliteDetachDb(const std::string& mainDBName, const std::string& alias);

SQLiteOPResult sqliteExecute(const std::string& dbName, const std::string& query, const std::optional<SQLiteParams>& params, TableResults& results, std::optional<TableMetadata>& metadata);

SequelLiteralUpdateResult sqliteExecuteLiteral(const std::string& dbName, const std::string& query);

void sqliteCloseAll();

}
