#include <NitroModules/HybridObjectRegistry.hpp>
#include "HybridQuickSQLiteSpec.hpp"
#include "HybridSelectQueryResultSpec.hpp"
#include "sqliteBridge.h"

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

class OnLoad {
public:
    OnLoad() {
        registerHybridObjectConstructors();

        // Get appGroupID value from Info.plist using key "AppGroup"
        NSString *appGroupID = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"ReactNativeQuickSQLite_AppGroup"];
        NSString *documentPath;

        if (appGroupID != nil) {
          // Get the app groups container storage url
          NSFileManager *fileManager = [NSFileManager defaultManager];
          NSURL *storeUrl = [fileManager containerURLForSecurityApplicationGroupIdentifier:appGroupID];

          if (storeUrl == nil) {
            NSLog(@"Invalid AppGroup ID provided (%@). Check the value of \"AppGroup\" in your Info.plist file", appGroupID);
            return @false;
          }
          NSLog(@"Configured with AppGroup ID: %@", appGroupID);

          documentPath = [storeUrl path];
        } else {
          // Get iOS app's document directory (to safely store database .sqlite3 file)
          NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, true);
          documentPath = [paths objectAtIndex:0];
        }
    }
};

static OnLoad onLoad;
