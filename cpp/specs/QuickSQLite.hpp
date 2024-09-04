#pragma once

#include "sqliteBridge.h"
#include "logs.h"
#include "sqlfileloader.h"
#include "sqlbatchexecutor.h"
#include <vector>
#include <string>
#include "macros.h"
#include <iostream>
#include <exception>
#include "HybridQuickSQLiteSpec.hpp"

namespace margelo::nitro::rnquicksqlite {

class QuickSQLite: public HybridQuickSQLiteSpec {
private:
    string docPathStr;

public:
    explicit QuickSQLite();

    void open(std::string dbName, std::optional<std::string> location);

public:
    void loadHybridMethods() override;

private:
  static constexpr auto TAG = "QuickSQLite";
};

}
