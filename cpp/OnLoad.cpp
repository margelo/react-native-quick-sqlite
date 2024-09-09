#include "OnLoad.hpp"
#include "HybridQuickSQLiteObject.hpp"
#include "HybridSelectQueryResultObject.hpp"

using namespace margelo::nitro;
using namespace margelo::rnquicksqlite;

void clearState() {
  sqliteCloseAll();
}

// Call this at app startup to register the HybridObjects
void registerHybridObjectConstructors() {
  HybridObjectRegistry::registerHybridObjectConstructor("QuickSQLite", []() -> std::shared_ptr<HybridObject> {
      return std::make_shared<HybridQuickSQLiteObject>();
    });
  HybridObjectRegistry::registerHybridObjectConstructor("SelectQueryResult", []() -> std::shared_ptr<HybridObject> {
      return std::make_shared<HybridSelectQueryResultObject>();
    });
}

// OnLoad::OnLoad() {
//     registerHybridObjectConstructors();
// }
