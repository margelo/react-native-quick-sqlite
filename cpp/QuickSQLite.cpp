#include "QuickSQLite.hpp"

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

void QuickSQLite::loadHybridMethods() {
    HybridObject::loadHybridMethods();
    registerHybrids(this, [](margelo::nitro::Prototype& prototype) {
      prototype.registerHybridMethod("open", &QuickSQLite::open);
    });
}
