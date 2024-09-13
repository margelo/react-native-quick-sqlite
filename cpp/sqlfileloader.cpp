/**
 * SQL File Loader implementation
 */
#include "sqlfileloader.h"
#include <fstream>
#include <iostream>

namespace margelo::rnquicksqlite {

SQLiteBatchOperationResult importSQLFile(const std::string& dbName, const std::string& fileLocation) {
  std::string line;
  std::ifstream sqFile(fileLocation);
  if (sqFile.is_open()) {
    try {
      int affectedRows = 0;
      int commands = 0;
      sqliteExecuteLiteral(dbName, "BEGIN EXCLUSIVE TRANSACTION");
      while (std::getline(sqFile, line, '\n')) {
        if (!line.empty()) {
          SQLiteLiteralUpdateResult result = sqliteExecuteLiteral(dbName, line);
          if (result.type == SQLiteError) {
            sqliteExecuteLiteral(dbName, "ROLLBACK");
            sqFile.close();
            return {SQLiteError, result.message, 0, commands};
          } else {
            affectedRows += result.affectedRows;
            commands++;
          }
        }
      }
      sqFile.close();
      sqliteExecuteLiteral(dbName, "COMMIT");
      return {SQLiteOk, "", affectedRows, commands};
    } catch (...) {
      sqFile.close();
      sqliteExecuteLiteral(dbName, "ROLLBACK");
      return {SQLiteError, "[react-native-quick-sqlite][loadSQLFile] Unexpected error, transaction was rolledback", 0, 0};
    }
  } else {
    return {SQLiteError, "[react-native-quick-sqlite][loadSQLFile] Could not open file", 0, 0};
  }
}

} // namespace margelo::rnquicksqlite
