/**
 * SQL Batch execution implementation using default sqliteBridge implementation
 */
#pragma once

#include "BatchQueryCommand.hpp"
#include "types.hpp"

using namespace facebook;
using namespace margelo::nitro;

namespace margelo::rnquicksqlite {

struct BatchQuery {
  std::string sql;
  std::shared_ptr<SQLiteQueryParams> params;
};

/**
 * Local Helper method to translate JSI objects BatchQuery datastructure
 * MUST be called in the JavaScript Thread
 */
std::vector<BatchQuery> batchParamsToCommands(const std::vector<BatchQueryCommand>& batchParams);

/**
 * Execute a batch of commands in a exclusive transaction
 */
SQLiteOperationResult sqliteExecuteBatch(const std::string& dbName, const std::vector<BatchQuery>& commands);

} // namespace margelo::rnquicksqlite
