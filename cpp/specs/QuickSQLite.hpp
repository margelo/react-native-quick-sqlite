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
    static std::string docPathStr;
    std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();

public:
    static void setDocPath(std::string docPath) {
        docPathStr = docPath;
    }

    explicit QuickSQLite();

    void open(std::string dbName, std::optional<std::string> location);

    void loadHybridMethods() override {
            HybridObject::loadHybridMethods();
        registerHybrids(this, [](margelo::nitro::Prototype& prototype) {
        prototype.registerHybridMethod("open", &QuickSQLite::open);
        });
    }

private:
    static constexpr auto TAG = "QuickSQLite";
};

}
