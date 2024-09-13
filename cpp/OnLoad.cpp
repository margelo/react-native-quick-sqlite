#include "OnLoad.hpp"
#include "HybridQuickSQLite.hpp"
#include "HybridSelectQueryResult.hpp"

using namespace margelo::nitro;
using namespace margelo::rnquicksqlite;

// void clearState() {
//     sqliteCloseAll();
// }

// auto wasRegistered = false;
// // Call this at app startup to register the HybridObjects
// void registerHybridObjectConstructors() {
//     // if (wasRegistered) return;
//     wasRegistered = true;

//     HybridObjectRegistry::registerHybridObjectConstructor("QuickSQLite", []() -> std::shared_ptr<HybridObject> {
//         return std::make_shared<HybridQuickSQLite>();
//     });
// }

// OnLoadCpp::OnLoadCpp() {
//     registerHybridObjectConstructors();
// }
