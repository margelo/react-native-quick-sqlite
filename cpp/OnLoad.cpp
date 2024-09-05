#include "OnLoad.hpp"
#include "HybridQuickSQLiteSpec.hpp"
#include "HybridSelectQueryResultSpec.hpp"

using namespace margelo::nitro;

void clearState() {
  sqliteCloseAll();
}

// Call this at app startup to register the HybridObjects
void registerHybridObjectConstructors() {
  HybridObjectRegistry::registerHybridObjectConstructor("QuickSQLite", []() -> std::shared_ptr<HybridObject> {
      return std::make_shared<HybridQuickSQLiteSpec>();
    });
  HybridObjectRegistry::registerHybridObjectConstructor("SelectQueryResult", []() -> std::shared_ptr<HybridObject> {
      return std::make_shared<HybridSelectQueryResultSpec>();
    });
}

// OnLoad::OnLoad() {
//     registerHybridObjectConstructors();
// }
