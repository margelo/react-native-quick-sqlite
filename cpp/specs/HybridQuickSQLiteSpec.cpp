#include "sqliteBridge.h"
#include "logs.h"
#include "JSIHelper.h"
#include "ThreadPool.h"
#include "sqlfileloader.h"
#include "sqlbatchexecutor.h"
#include <vector>
#include <string>
#include "macros.h"
#include <iostream>
#include "HybridQuickSQLiteSpec.hpp"
#include "OnLoad.hpp"

using namespace margelo::nitro;

namespace margelo::nitro::rnquicksqlite {

void HybridQuickSQLiteSpec::open(const std::string& dbName, const std::optional<std::string>& location) {
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

}
