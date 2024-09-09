#pragma once

#include "HybridQuickSQLiteSpec.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

class HybridQuickSQLiteObject: public HybridQuickSQLiteSpec {
public:
    // Methods
    void open(const std::string& dbName, const std::optional<std::string>& location) override;
    void close(const std::string& dbName) override;
    void drop(const std::string& dbName, const std::optional<std::string>& location) override;
    void attach(const std::string& mainDbName, const std::string& dbNameToAttach, const std::string& alias, const std::optional<std::string>& location) override;
    void detach(const std::string& mainDbName, const std::string& alias) override;
    std::future<void> transaction(const std::string& dbName, const std::function<std::future<std::future<void>>(const Transaction& /* tx */)>& fn) override;
    QueryResult execute(const std::string& dbName, const std::string& query, const std::optional<std::vector<std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>>>>& params) override;
    std::future<QueryResult> executeAsync(const std::string& dbName, const std::string& query, const std::optional<std::vector<std::variant<std::string, double, int64_t, bool, std::shared_ptr<ArrayBuffer>>>>& params) override;
    BatchQueryResult executeBatch(const std::string& dbName, const std::vector<BatchQueryCommand>& commands) override;
    std::future<BatchQueryResult> executeBatchAsync(const std::string& dbName, const std::vector<BatchQueryCommand>& commands) override;
    FileLoadResult loadFile(const std::string& dbName, const std::string& location) override;
    std::future<FileLoadResult> loadFileAsync(const std::string& dbName, const std::string& location) override;
};

}
