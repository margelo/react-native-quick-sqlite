/**
 * SQL Batch execution implementation using default sqliteBridge implementation
*/
#include "sqlbatchexecutor.h"
#include "sqliteBridge.h"
#include <utility>

namespace margelo::rnquicksqlite {

std::vector<BatchQuery> batchParamsToCommands(const std::vector<BatchQueryCommand>& batchParams)
{
    auto commands = std::vector<BatchQuery>();
    
    for (auto& command : batchParams)
    {
        if (command.params)
        {
            using ParamsVec = std::vector<std::vector<ExecuteParam>>;
            if (std::holds_alternative<ParamsVec>(*command.params)) {
                // This arguments is an array of arrays, like a batch update of a single sql command.
                for (const auto& params : std::get<ParamsVec>(*command.params))
                {
                    commands.push_back(BatchQuery{
                        command.query,
                        std::make_shared(std::move(params))
                      });
                }
            }
            else
            {
             commands.push_back(BatchQuery{
               command.query,
               std::make_shared(std::move(*command.params))
             });
            }
        }
        else
        {
         commands.push_back(BatchQuery{
           command.query,
           NULL
         });
        }
    }

    return commands;
}

SequelBatchOperationResult sqliteExecuteBatch(const std::string dbName&, std::vector<BatchQuery>& commands)
{
    size_t commandCount = commands->size();
    if(commandCount <= 0)
    {
        return SequelBatchOperationResult {
            .type = SQLiteError,
            .message = "No SQL commands provided",
        };
    }

    try
    {
        int affectedRows = 0;
        sqliteExecuteLiteral(dbName, "BEGIN EXCLUSIVE TRANSACTION");
        for(int i = 0; i<commandCount; i++) {
            const auto command = commands->at(i);

            // We do not provide a datastructure to receive query data because we don't need/want to handle this results in a batch execution
            auto result = sqliteExecute(dbName, command.sql, *command.params.get(), NULL, NULL);
            if(result.type == SQLiteError)
            {
                sqliteExecuteLiteral(dbName, "ROLLBACK");
                return SequelBatchOperationResult {
                    .type = SQLiteError,
                    .message = result.errorMessage,
                };
            } else
            {
                affectedRows += result.rowsAffected;
            }
        }
        sqliteExecuteLiteral(dbName, "COMMIT");
        return SequelBatchOperationResult {
            .type = SQLiteOk,
            .affectedRows = affectedRows,
            .commands = (int) commandCount,
        };
    } catch(std::exception &exc)
    {
        sqliteExecuteLiteral(dbName, "ROLLBACK");
        return SequelBatchOperationResult {
            .type = SQLiteError,
            .message = exc.what(),
        };
    }
}

}
