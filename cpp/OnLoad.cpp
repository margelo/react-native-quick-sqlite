#include "OnLoad.hpp"
#include "HybridQuickSQLite.hpp"
#include "HybridSelectQueryResult.hpp"

using namespace margelo::nitro;
using namespace margelo::rnquicksqlite;

void clearState() {
    sqliteCloseAll();
}

// Call this at app startup to register the HybridObjects
void registerHybridObjectConstructors() {
    HybridObjectRegistry::registerHybridObjectConstructor("QuickSQLite", []() -> std::shared_ptr<HybridObject> {
        return std::make_shared<HybridQuickSQLite>();
    });
}

// OnLoad::OnLoad() {
//     registerHybridObjectConstructors();
// }
