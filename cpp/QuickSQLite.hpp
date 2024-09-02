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
#include <NitroModules/HybridObject.hpp>

class QuickSQLite: public margelo::nitro::HybridObject {
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
