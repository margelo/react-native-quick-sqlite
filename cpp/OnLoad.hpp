#pragma once

#include <NitroModules/HybridObjectRegistry.hpp>
#include "HybridQuickSQLiteSpec.hpp"
#include "HybridSelectQueryResultSpec.hpp"
#include "sqliteBridge.h"
#include "ThreadPool.h"

std::string docPathStr;
auto pool = std::make_shared<margelo::rnquicksqlite::ThreadPool>();

void clearState();

void registerHybridObjectConstructors();

// class OnLoad {
// public:
//     OnLoad()
// };

// #pragma optimize("", off)
// static volatile OnLoad onLoad;
