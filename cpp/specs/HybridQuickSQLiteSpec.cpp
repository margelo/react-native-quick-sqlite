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

void HybridQuickSQLiteSpec::close(const std::string& dbName) {
    SQLiteOPResult result = sqliteCloseDb(dbName);

    if (result.type == SQLiteError)
    {
        throw std::runtime_error(result.errorMessage.c_str());
    }
};

void HybridQuickSQLiteSpec::drop(const std::string& dbName, const std::optional<std::string>& location) {
    string tempDocPath = string(docPathStr);
    if (location)
    {
        tempDocPath = tempDocPath + "/" + *location;
    }


    SQLiteOPResult result = sqliteRemoveDb(dbName, tempDocPath);

    if (result.type == SQLiteError)
    {
        throw std::runtime_error(result.errorMessage.c_str());
    }
};

void HybridQuickSQLiteSpec::attach(const std::string& mainDbName, const std::string& dbNameToAttach, const std::string& alias, const std::optional<std::string>& location) {
    string tempDocPath = string(docPathStr);
    if (location)
    {
        tempDocPath = tempDocPath + "/" + *location;
    }

    SQLiteOPResult result = sqliteAttachDb(mainDbName, tempDocPath, dbNameToAttach, alias);

    if (result.type == SQLiteError)
    {
        throw std::runtime_error(result.errorMessage.c_str());
    }
};

void HybridQuickSQLiteSpec::detach(const std::string& mainDbName, const std::string& alias) {
    SQLiteOPResult result = sqliteDetachDb(mainDbName, alias);

    if (result.type == SQLiteError)
    {
        throw std::runtime_error(result.errorMessage.c_str());
    }
};

std::future<void> transaction(const std::string& dbName, const std::function<std::future<std::future<void>>(const Transaction& /* tx */)>& fn) {

};

QueryResult HybridQuickSQLiteSpec::execute(const std::string& dbName, const std::string& query, const std::optional<std::vector<std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>>>>& params) {
    if (params) {
        
    }
    
    vector<map<string, QuickValue>> results;
    vector<QuickColumnMetadata> metadata;

    // Converting results into a JSI Response
    try {
        auto status = sqliteExecute(dbName, query, &params, &results, &metadata);

        if(status.type == SQLiteError) {
          throw std::runtime_error(status.errorMessage.c_str());
        }

        auto jsiResult = createSequelQueryExecutionResult(rt, status, &results, &metadata);
        return jsiResult;
    } catch(std::exception &e) {
        throw std::runtime_error(e.what());
    }
};

std::future<QueryResult> HybridQuickSQLiteSpec::executeAsync(const std::string& dbName, const std::string& query, const std::optional<std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>>>& params) {
    
};

BatchQueryResult HybridQuickSQLiteSpec::executeBatch(const std::string& dbName, const std::vector<std::variant<std::tuple<std::string>, std::tuple<std::string, std::variant<std::vector<std::nullptr_t>, std::vector<std::vector<std::nullptr_t>>>>>>& commands) {
    
};

std::future<BatchQueryResult> HybridQuickSQLiteSpec::executeBatchAsync(const std::string& dbName, const std::vector<std::variant<std::tuple<std::string>, std::tuple<std::string, std::variant<std::vector<std::nullptr_t>, std::vector<std::vector<std::nullptr_t>>>>>>& commands) {
    
};

FileLoadResult HybridQuickSQLiteSpec::loadFile(const std::string& dbName, const std::string& location) {
    const auto importResult = importSQLFile(dbName, sqlFileName);
    if (importResult.type == SQLiteOk)
    {
      //auto res = jsi::Object(rt);
      //res.setProperty(rt, "rowsAffected", jsi::Value(importResult.affectedRows));
      //res.setProperty(rt, "commands", jsi::Value(importResult.commands));
      return std::move(importResult);
    }
    else
    {
        throw std::runtime_error("[react-native-quick-sqlite][loadFile] Could not open file");
    }
};

std::future<FileLoadResult> HybridQuickSQLiteSpec::loadFileAsync(const std::string& dbName, const std::string& location) {
    
};

}
