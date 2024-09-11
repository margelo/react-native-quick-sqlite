#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "HybridQuickSQLite.hpp"
#include "HybridSelectQueryResult.hpp"
#include "sqliteBridge.h"
#include "logs.h"
#include "ThreadPool.h"
#include "sqlfileloader.h"
#include "sqlbatchexecutor.h"
#include "macros.h"
#include "OnLoad.hpp"
#include "QueryType.hpp"
#include "Types.hpp"

namespace margelo::rnquicksqlite {

void HybridQuickSQLite::HybridQuickSQLite() : HybridQuickSQLiteSpec() {}

void HybridQuickSQLite::open(const std::string& dbName, const std::optional<std::string>& location) {
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

void HybridQuickSQLite::close(const std::string& dbName) {
    SQLiteOPResult result = sqliteCloseDb(dbName);

    if (result.type == SQLiteError)
    {
        throw std::runtime_error(result.errorMessage.c_str());
    }
};

void HybridQuickSQLite::drop(const std::string& dbName, const std::optional<std::string>& location) {
    std::string tempDocPath = std::string(docPathStr);
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

void HybridQuickSQLite::attach(const std::string& mainDbName, const std::string& dbNameToAttach, const std::string& alias, const std::optional<std::string>& location) {
    std::string tempDocPath = std::string(docPathStr);
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

void HybridQuickSQLite::detach(const std::string& mainDbName, const std::string& alias) {
    SQLiteOPResult result = sqliteDetachDb(mainDbName, alias);

    if (result.type == SQLiteError)
    {
        throw std::runtime_error(result.errorMessage.c_str());
    }
};

NativeQueryResult HybridQuickSQLite::execute(const std::string& dbName, const std::string& query, const std::optional<SQLiteParams>& params) {
    auto results = TableResults();
    auto metadata = std::optional<TableMetadata>(std::nullopt);

    // Converting results into a JSI Response
    try {
        auto status = sqliteExecute(dbName, query, params, results, metadata);

        if(status.type == SQLiteError) {
          throw std::runtime_error(status.errorMessage);
        }

        if (metadata) {
            const auto selectQueryResult = std::make_shared<HybridSelectQueryResult>(std::move(results), std::move(*metadata));
            return NativeQueryResult(QueryType::SELECT, status.insertId, status.rowsAffected, selectQueryResult);
        }

        return NativeQueryResult(QueryType::SELECT, status.insertId, status.rowsAffected, std::nullopt);
    } catch(std::exception &e) {
        throw std::runtime_error(e.what());
    }
};

std::future<NativeQueryResult> HybridQuickSQLite::executeAsync(const std::string& dbName, const std::string& query, const std::optional<SQLiteParams>& params) {
    auto promise = std::make_shared<std::promise<NativeQueryResult>>();
    auto future = promise->get_future();

    auto task = [this, promise, dbName, query, params]() {
        try {
            auto result = execute(dbName, query, params);
            promise->set_value(result);
        } catch (...) {
            promise->set_exception(std::current_exception());
        }
    };

    pool->queueWork(std::move(task));

    return future;
};

BatchQueryResult HybridQuickSQLite::executeBatch(const std::string& dbName, const std::vector<BatchQueryCommand>& batchParams) {
    const auto commands = batchParamsToCommands(batchParams);

    auto batchResult = sqliteExecuteBatch(dbName, commands);
    if (batchResult.type == SQLiteOk)
    {
        return BatchQueryResult(batchResult.affectedRows);
    }
    else
    {
        throw std::runtime_error(batchResult.message);
    }
};

std::future<BatchQueryResult> HybridQuickSQLite::executeBatchAsync(const std::string& dbName, const std::vector<BatchQueryCommand>& batchParams) {
    auto promise = std::make_shared<std::promise<BatchQueryResult>>();
    auto future = promise->get_future();

    auto task = [this, promise, dbName, batchParams]() {
        try {
            auto result = executeBatch(dbName, batchParams);
            promise->set_value(result);
        } catch (...) {
            promise->set_exception(std::current_exception());
        }
    };

    pool->queueWork(std::move(task));

    return future;
};

FileLoadResult HybridQuickSQLite::loadFile(const std::string& dbName, const std::string& location) {
    const auto importResult = importSQLFile(dbName, location);
    if (importResult.type == SQLiteOk)
    {
        auto result = new FileLoadResult(importResult.commands, importResult.affectedRows);
        return *result;
    }
    else
    {
        throw std::runtime_error("[react-native-quick-sqlite][loadFile] Could not open file");
    }
};

std::future<FileLoadResult> HybridQuickSQLite::loadFileAsync(const std::string& dbName, const std::string& location) {
    auto promise = std::make_shared<std::promise<FileLoadResult>>();
    auto future = promise->get_future();

    auto task = [this, promise, dbName, location]() {
        try {
            auto result = loadFile(dbName, location);
            promise->set_value(result);
        } catch (...) {
            promise->set_exception(std::current_exception());
        }
    };

    pool->queueWork(std::move(task));

    return future;
};

}
