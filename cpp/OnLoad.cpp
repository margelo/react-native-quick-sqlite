#include <NitroModules/HybridObjectRegistry.hpp>

// Call this at app startup to register the HybridObjects
void load() {
  HybridObjectRegistry::registerHybridObjectConstructor("QuickSQLite", []() -> std::shared_ptr<HybridObject> {
      return std::make_shared<HybridQuickSQLiteSpec>();
    });
  HybridObjectRegistry::registerHybridObjectConstructor("QueryResult", []() -> std::shared_ptr<HybridObject> {
      return std::make_shared<HybridQueryResultSpec>();
    });
}

class OnLoad {
public:
    OnLoad() {
        load();
    }
};

static OnLoad onLoad;
