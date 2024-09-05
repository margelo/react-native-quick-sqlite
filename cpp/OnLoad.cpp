#include "OnLoad.hpp"
#include "specs/QuickSQLite.hpp"
#include "specs/SelectQueryResult.hpp"

using namespace margelo::nitro;

void clearState() {
  sqliteCloseAll();
}

// Call this at app startup to register the HybridObjects
void registerHybridObjectConstructors() {
  HybridObjectRegistry::registerHybridObjectConstructor("QuickSQLite", []() -> std::shared_ptr<HybridObject> {
      return std::make_shared<QuickSQLite>();
    });
  HybridObjectRegistry::registerHybridObjectConstructor("SelectQueryResult", []() -> std::shared_ptr<HybridObject> {
      return std::make_shared<SelectQueryResult>();
    });
}

// OnLoad::OnLoad() {
//     registerHybridObjectConstructors();
// }
