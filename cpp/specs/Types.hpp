#pragma once

#include <string>
#include "ArrayBuffer.hpp"
#include "ColumnType.hpp"

namespace margelo::nitro::rnquicksqlite {

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

using SQLiteValue = std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>, std::monostate>;

// constexpr function that maps SQLiteColumnType to string literals
constexpr ColumnType mapSQLiteTypeToColumnType(std::string type) {
    if (type == "INTEGER") {
        return ColumnType::INTEGER;
    } else if (type == "BOOLEAN") {
        return ColumnType::BOOLEAN;
    } else if (type == "TEXT") {
        return ColumnType::TEXT;
    } else if (type == "BLOB") {
        return ColumnType::ARRAY_BUFFER;
    } else if (type == "REAL") {
        return ColumnType::DOUBLE;
    } else {
        return ColumnType::UNKNOWN;
    }
}

}
