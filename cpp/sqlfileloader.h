
/**
 * SQL File Loader
 * Utilizes the regular sqlite bridge to load an SQLFile inside a transaction
 *
 */

#include "sqliteBridge.h"

namespace margelo::rnquicksqlite {

SequelBatchOperationResult importSQLFile(const std::string& dbName, const std::string& fileLocation);

}
