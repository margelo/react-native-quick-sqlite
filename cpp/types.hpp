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

struct SQLiteOperationResult {
  int rowsAffected;
  double insertId;
  int commands;
};

struct SQLiteExecuteQueryResult {
  int rowsAffected;
  double insertId;

  std::unique_ptr<SQLiteQueryResults> results;
  std::unique_ptr<std::optional<SQLiteQueryTableMetadata>> metadata;
};

// constexpr function that maps SQLiteColumnType to string literals
constexpr ColumnType mapSQLiteTypeToColumnType(std::string type) {
  if (type == "BOOLEAN") {
    return ColumnType::BOOLEAN;
  } else if (type == "FLOAT") {
    return ColumnType::NUMBER;
  } else if (type == "INTEGER") {
    return ColumnType::INT64;
  } else if (type == "TEXT") {
    return ColumnType::TEXT;
  } else if (type == "BLOB") {
    return ColumnType::ARRAY_BUFFER;
  } else {
    return ColumnType::NULL_VALUE;
  }
}

} // namespace margelo::rnquicksqlite