#pragma once

#include <map>
#include "HybridSelectQueryResultSpec.hpp"
#include "Types.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

class HybridSelectQueryResult: public HybridSelectQueryResultSpec {
public:
    HybridSelectQueryResult(std::vector<std::unordered_map<std::string, SQLiteValue>>&& results, std::vector<TableMetadata>&& metadata);

public:
    // Properties
    std::vector<std::unordered_map<std::string, SQLiteValue>> getResults() override;
    void setResults(const std::vector<std::unordered_map<std::string, SQLiteValue>>& results) override;
    std::vector<TableMetadata> getMetadata() override;
    void setMetadata(const std::vector<TableMetadata>& metadata) override;

private:
    std::vector<std::unordered_map<std::string, SQLiteValue>> _results;
    std::vector<TableMetadata> _metadata;
};

}
