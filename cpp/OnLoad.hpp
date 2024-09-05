#include <NitroModules/HybridObjectRegistry.hpp>
#include "HybridQuickSQLiteSpec.hpp"
#include "HybridSelectQueryResultSpec.hpp"
#include "sqliteBridge.h"

std::string docPathStr;

void clearState();

void registerHybridObjectConstructors();

// class OnLoad {
// public:
//     OnLoad()
// };

// static OnLoad onLoad;
