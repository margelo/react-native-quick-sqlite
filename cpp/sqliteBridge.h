#pragma once

#include "ColumnMetadata.hpp"
#include "Types.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

SQLiteOPResult sqliteOpenDb(const std::string& dbName, const std::string& docPath);

SQLiteOPResult sqliteCloseDb(const std::string& dbName);

SQLiteOPResult sqliteRemoveDb(const std::string& dbName, const std::string& docPath);

SQLiteOPResult sqliteAttachDb(const std::string& mainDBName, const std::string& docPath, const std::string& databaseToAttach, const std::string& alias);

SQLiteOPResult sqliteDetachDb(const std::string& mainDBName, const std::string& alias);

SQLiteOPResult sqliteExecute(const std::string& dbName, const std::string& query, const std::optional<std::vector<SQLiteValue>>& params, std::shared_ptr<std::vector<std::map<std::string, SQLiteValue>>> result, std::shared_ptr<std::optional<std::vector<ColumnMetadata>>> metadata);

SequelLiteralUpdateResult sqliteExecuteLiteral(const std::string& dbName, const std::string& query);

void sqliteCloseAll();

}
