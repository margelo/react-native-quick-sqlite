#include "HybridQuickSQLite.hpp"
#include "HybridNativeQueryResult.hpp"
#include "ThreadPool.hpp"
#include "QuickSQLiteException.hpp"
#include "logs.hpp"
#include "macros.hpp"
#include "sqliteExecuteBatch.hpp"
#include "importSqlFile.hpp"
#include "operations.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace margelo::nitro::rnquicksqlite {

auto pool = std::make_shared<margelo::rnquicksqlite::ThreadPool>();

const std::string getDocPath(const std::optional<std::string>& location) {
  std::string tempDocPath = std::string(HybridQuickSQLite::docPath);
  if (location) {
    tempDocPath = tempDocPath + "/" + *location;
  }

  return tempDocPath;
}

void HybridQuickSQLite::open(const std::string& dbName, const std::optional<std::string>& location) {
  const auto docPath = getDocPath(location);
  sqliteOpenDb(dbName, docPath);
}

void HybridQuickSQLite::close(const std::string& dbName) {
  sqliteCloseDb(dbName);
};

void HybridQuickSQLite::drop(const std::string& dbName, const std::optional<std::string>& location) {
  const auto docPath = getDocPath(location);
  sqliteRemoveDb(dbName, docPath);
};

void HybridQuickSQLite::attach(const std::string& mainDbName, const std::string& dbNameToAttach, const std::string& alias,
                               const std::optional<std::string>& location) {
  std::string tempDocPath = std::string(docPath);
  if (location) {
    tempDocPath = tempDocPath + "/" + *location;
  }

  sqliteAttachDb(mainDbName, tempDocPath, dbNameToAttach, alias);
};

void HybridQuickSQLite::detach(const std::string& mainDbName, const std::string& alias) {
  sqliteDetachDb(mainDbName, alias);
};

using ExecuteQueryResult = std::shared_ptr<HybridNativeQueryResultSpec>;

ExecuteQueryResult HybridQuickSQLite::execute(const std::string& dbName, const std::string& query,
                                             const std::optional<SQLiteQueryParams>& params) {
  auto result = sqliteExecute(dbName, query, params);
  return std::make_shared<HybridNativeQueryResult>(result.insertId, result.rowsAffected, *result.results, *result.metadata);
};

std::future<ExecuteQueryResult> HybridQuickSQLite::executeAsync(const std::string& dbName, const std::string& query,
                                                               const std::optional<SQLiteQueryParams>& params) {
  auto promise = std::make_shared<std::promise<ExecuteQueryResult>>();
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

  auto result = sqliteExecuteBatch(dbName, commands);
  return BatchQueryResult(result.rowsAffected);
};

std::future<BatchQueryResult> HybridQuickSQLite::executeBatchAsync(const std::string& dbName,
                                                                   const std::vector<BatchQueryCommand>& batchParams) {
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
  const auto result = importSqlFile(dbName, location);
  return FileLoadResult(result.commands, result.rowsAffected);
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

} // namespace margelo::nitro::rnquicksqlite
