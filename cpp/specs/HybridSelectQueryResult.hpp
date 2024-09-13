#pragma once

#include <map>
#include "HybridSelectQueryResultSpec.hpp"
#include "Types.hpp"

using namespace margelo::rnquicksqlite;

namespace margelo::nitro::rnquicksqlite {

class HybridSelectQueryResult: public HybridSelectQueryResultSpec {
public:
    HybridSelectQueryResult() : HybridObject(TAG) {}
    HybridSelectQueryResult(TableResults&& results, TableMetadata&& metadata)
    : HybridObject(TAG), _results(std::move(results)), _metadata(std::move(metadata)) {}
    
private:
    TableResults _results;
    TableMetadata _metadata;

public:
    // Properties
    TableResults getResults() override;
    void setResults(const TableResults& results) override;
    TableMetadata getMetadata() override;
    void setMetadata(const TableMetadata& metadata) override;
};
    
}
