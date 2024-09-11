#pragma once

#include <string>
#include "ArrayBuffer.hpp"
#include "ColumnType.hpp"
#include "ColumnMetadata.hpp"

using namespace margelo::nitro;
using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

/**
 * Various structs to help with the results of the SQLite operations
 */
enum ResultType
{
  SQLiteOk,
  SQLiteError
};

struct SQLiteOPResult
{
  ResultType type;
  std::string errorMessage;
  int rowsAffected;
  double insertId;
};

struct SequelLiteralUpdateResult
{
  ResultType type;
    std::string message;
  int affectedRows;
};

struct SequelBatchOperationResult
{
  ResultType type;
    std::string message;
  int affectedRows;
  int commands;
};

// using SQLiteValue = std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>, std::monostate>;
using SQLiteValue = std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>>;
using SQLiteParams = std::vector<SQLiteValue>;
using TableResults = std::vector<std::unordered_map<std::string, SQLiteValue>>;
using TableMetadata = std::unordered_map<std::string, ColumnMetadata>;

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

}
