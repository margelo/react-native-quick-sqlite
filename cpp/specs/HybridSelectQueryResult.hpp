#pragma once

#include <map>
#include "HybridSelectQueryResultSpec.hpp"
#include "Types.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

class HybridSelectQueryResult: public HybridSelectQueryResultSpec {
public:
    HybridSelectQueryResult(TableResults&& results, TableMetadata&& metadata);

public:
    // Properties
    TableResults getResults() override;
    void setResults(const TableResults& results) override;
    TableMetadata getMetadata() override;
    void setMetadata(const TableMetadata& metadata) override;

private:
    TableResults _results;
    TableMetadata _metadata;
};

}
