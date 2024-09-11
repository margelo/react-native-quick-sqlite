/**
 * SQL Batch execution implementation using default sqliteBridge implementation
*/
#pragma once

#include "Types.hpp"
#include "BatchQueryCommand.hpp"

using namespace facebook;
using namespace margelo::nitro;

namespace margelo::rnquicksqlite {

struct BatchQuery {
    std::string sql;
    std::shared_ptr<SQLiteParams> params;
};

/**
 * Local Helper method to translate JSI objects BatchQuery datastructure
 * MUST be called in the JavaScript Thread
 */
std::vector<BatchQuery> batchParamsToCommands(const std::vector<BatchQueryCommand>& batchParams);

/**
 * Execute a batch of commands in a exclusive transaction
 */
SequelBatchOperationResult sqliteExecuteBatch(const std::string& dbName, const std::vector<BatchQuery>& commands);

}
