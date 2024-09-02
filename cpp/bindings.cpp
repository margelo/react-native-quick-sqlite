#include "bindings.h"
#include "sqliteBridge.h"
#include "logs.h"
#include "JSIHelper.h"
#include "ThreadPool.h"
#include "sqlfileloader.h"
#include "sqlbatchexecutor.h"
#include <vector>
#include <string>
#include "macros.h"
#include <iostream>
#include <NitroModules/HybridObjectRegistry.hpp>
#include <NitroModules/HybridObject.hpp>
#include "QuickSQLite.hpp"

using namespace std;
using namespace facebook;

namespace margelo {

void clearState() {
  sqliteCloseAll(); 
}

void load() {
    margelo::nitro::HybridObjectRegistry::registerHybridObjectConstructor(
    "QuickSQLite",
    []() -> std::shared_ptr<margelo::nitro::HybridObject> {
      return std::make_shared<QuickSQLite>();
    }
  );
}

void install(jsi::Runtime &rt, std::shared_ptr<react::CallInvoker> jsCallInvoker, const char *docPath)
{
  load();
}

}
