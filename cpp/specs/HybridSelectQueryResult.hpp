#pragma once

#include <map>
#include "HybridSelectQueryResultSpec.hpp"
#include "Types.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

class HybridSelectQueryResult: public HybridSelectQueryResultSpec {
public:
    HybridSelectQueryResult(std::vector<std::unordered_map<std::string, SQLiteValue>>&& results, std::vector<ColumnMetadata>&& metadata);

public:
    // Properties
    std::vector<std::unordered_map<std::string, SQLiteValue>> getResults() override;
    void setResults(const std::vector<std::unordered_map<std::string, SQLiteValue>>& results) override;
    std::vector<ColumnMetadata> getMetadata() override;
    void setMetadata(const std::vector<ColumnMetadata>& metadata) override;

private:
    std::vector<std::unordered_map<std::string, SQLiteValue>> _results;
    std::vector<ColumnMetadata> _metadata;
};

}
