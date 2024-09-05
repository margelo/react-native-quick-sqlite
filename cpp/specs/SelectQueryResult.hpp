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

class SelectQueryResult: public HybridQuickSQLiteSpec {
public:

    explicit SelectQueryResult();

    // void open(std::string dbName, std::optional<std::string> location);

    // void loadHybridMethods() override {
    //         HybridObject::loadHybridMethods();
    //     registerHybrids(this, [](margelo::nitro::Prototype& prototype) {
    //     prototype.registerHybridMethod("open", &QuickSQLite::open);
    //     });
    // }

private:
    static constexpr auto TAG = "SelectQueryResult";
};

}
