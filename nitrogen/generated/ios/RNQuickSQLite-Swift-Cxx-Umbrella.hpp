///
/// RNQuickSQLite-Swift-Cxx-Umbrella.hpp
/// Sun Sep 01 2024
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#pragma once

// Forward declarations of C++ defined types
// Forward declaration of `ArrayBuffer` to properly resolve imports.
namespace NitroModules { class ArrayBuffer; }
// Forward declaration of `BatchQueryResult` to properly resolve imports.
namespace margelo::nitro::rnquicksqlite { struct BatchQueryResult; }
// Forward declaration of `ColumnMetadata` to properly resolve imports.
namespace margelo::nitro::rnquicksqlite { struct ColumnMetadata; }
// Forward declaration of `FileLoadResult` to properly resolve imports.
namespace margelo::nitro::rnquicksqlite { struct FileLoadResult; }
// Forward declaration of `QueryResultRows` to properly resolve imports.
namespace margelo::nitro::rnquicksqlite { struct QueryResultRows; }
// Forward declaration of `QueryResult` to properly resolve imports.
namespace margelo::nitro::rnquicksqlite { struct QueryResult; }
// Forward declaration of `QuickDataType` to properly resolve imports.
namespace margelo::nitro::rnquicksqlite { enum class QuickDataType; }
// Forward declaration of `QuickValue` to properly resolve imports.
namespace margelo::nitro::rnquicksqlite { struct QuickValue; }
// Forward declaration of `Transaction` to properly resolve imports.
namespace margelo::nitro::rnquicksqlite { struct Transaction; }

// Include C++ defined types
#include "BatchQueryResult.hpp"
#include "ColumnMetadata.hpp"
#include "FileLoadResult.hpp"
#include "QueryResult.hpp"
#include "QueryResultRows.hpp"
#include "QuickDataType.hpp"
#include "QuickValue.hpp"
#include "Transaction.hpp"
#include <NitroModules/ArrayBuffer.hpp>
#include <functional>
#include <future>
#include <optional>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

// C++ helpers for Swift
#include "RNQuickSQLite-Swift-Cxx-Bridge.hpp"

// Common C++ types used in Swift
#include <NitroModules/ArrayBufferHolder.hpp>
#include <NitroModules/AnyMapHolder.hpp>
#include <NitroModules/HybridContext.hpp>
#include <NitroModules/PromiseHolder.hpp>

// Forward declarations of Swift defined types


// Include Swift defined types
#if __has_include("RNQuickSQLite-Swift.h")
// This header is generated by Xcode/Swift on every app build.
// If it cannot be found, make sure the Swift module's name (= podspec name) is actually "RNQuickSQLite".
#include "RNQuickSQLite-Swift.h"
#else
#error RNQuickSQLite's autogenerated Swift header cannot be found! Make sure the Swift module's name (= podspec name) is actually "RNQuickSQLite", and try building the app first.
#endif