#include <string>
#include "ArrayBuffer.hpp"
#include "ColumnType.hpp"

namespace margelo::nitro::rnquicksqlite {

using ExecuteParam = std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>>;
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
