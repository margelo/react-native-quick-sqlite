/**
 * SQL Batch execution implementation using default sqliteBridge implementation
*/
#include "JSIHelper.h"
#include "sqliteBridge.h"

using namespace facebook;

struct QuickQueryArguments {
    std::string sql;
    std::shared_ptr<std::vector<ExecuteParam>> params;
};

/**
 * Local Helper method to translate JSI objects QuickQueryArguments datastructure
 * MUST be called in the JavaScript Thread
*/
void jsiBatchParametersToQuickArguments(jsi::Runtime &rt, jsi::Array const &batchParams, std::vector<QuickQueryArguments> *commands);

/**
 * Execute a batch of commands in a exclusive transaction
*/
SequelBatchOperationResult sqliteExecuteBatch(std::string dbName, std::vector<QuickQueryArguments> *commands);
