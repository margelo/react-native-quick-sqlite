#include "QuickSQLite.hpp"

using namespace margelo::nitro;

QuickSQLite::QuickSQLite() : margelo::nitro::HybridObject(TAG) {}

void QuickSQLite::open(std::string dbName, std::optional<std::string> location) {
    std::string tempDocPath = std::string(docPathStr);
    if (location) {
      tempDocPath = tempDocPath + "/" + *location;
    }

    SQLiteOPResult result = sqliteOpenDb(dbName, tempDocPath);

    if (result.type == SQLiteError)
    {
      throw std::runtime_error(result.errorMessage.c_str());
    }
}
