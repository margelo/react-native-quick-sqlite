#pragma once

#include "SQLiteQueryColumnMetadata.hpp"
#include "ColumnType.hpp"
#include <NitroModules/ArrayBuffer.hpp>
#include <string>

using namespace margelo::nitro;
using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

// using SQLiteValue = std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>, std::monostate>;
using SQLiteValue = std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>>;
using SQLiteQueryParams = std::vector<SQLiteValue>;
using SQLiteQueryResultRow = std::unordered_map<std::string, SQLiteValue>;
using SQLiteQueryResults = std::vector<SQLiteQueryResultRow>;
using SQLiteQueryTableMetadata = std::unordered_map<std::string, SQLiteQueryColumnMetadata>;

/**
 * Various structs to help with the results of the SQLite operations
 */
enum SQLiteResultType { SQLiteOk, SQLiteError };

struct SQLiteOperationResult {
  SQLiteResultType type;
  std::string errorMessage;
  int rowsAffected;
  double insertId;
  
  std::unique_ptr<SQLiteQueryResults> results;
  std::unique_ptr<SQLiteQueryTableMetadata> metadata;
};


struct SQLiteExecuteQueryResult {
  SQLiteResultType type;
  std::string errorMessage;
  int rowsAffected;
  double insertId;
  
  std::unique_ptr<SQLiteQueryResults> results;
  std::unique_ptr<SQLiteQueryTableMetadata> metadata;
};

struct SQLiteLiteralUpdateResult {
  SQLiteResultType type;
  std::string message;
  int affectedRows;
};

struct SQLiteBatchOperationResult {
  SQLiteResultType type;
  std::string message;
  int affectedRows;
  int commands;
};

// constexpr function that maps SQLiteColumnType to string literals
constexpr ColumnType mapSQLiteTypeToColumnType(std::string type) {
  if (type == "BOOLEAN") {
    return ColumnType::BOOLEAN;
  } else if (type == "REAL" || type == "NUMERIC") {
    return ColumnType::NUMBER;
  } else if (type == "INTEGER") {
    return ColumnType::INT64;
  } else if (type == "TEXT" || type == "VARCHAR(N)" || type == "CHAR(N)") {
    return ColumnType::TEXT;
  } else if (type == "BLOB") {
    return ColumnType::ARRAY_BUFFER;
  } else if (type == "NULL") {
    return ColumnType::NULL_VALUE;
  } else {
    return ColumnType::UNKNOWN;
  }
}

} // namespace margelo::rnquicksqlite
