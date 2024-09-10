#pragma once

#include <map>
#include "HybridSelectQueryResultSpec.hpp"
#include "Types.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

class HybridSelectQueryResult: public HybridSelectQueryResultSpec {
public:
    HybridSelectQueryResult(const std::vector<std::map<std::string, SQLiteValue>>& results, const std::optional<std::vector<ColumnMetadata>>& metadata);

public:
    // Properties
    std::vector<std::unordered_map<std::string, SQLiteValue>> getResults() override;
    void setResults(const std::vector<std::unordered_map<std::string, SQLiteValue>>& results) override;
    std::vector<ColumnMetadata> getMetadata() override;
    void setMetadata(const std::vector<ColumnMetadata>& metadata) override;

public:
    // Methods
//    std::string getString() override;
//    double getNumber() override;
//    bool getBoolean() override;
//    std::shared_ptr<ArrayBuffer> getArrayBuffer() override;

private:
    std::vector<ColumnMetadata> _metadata;
    std::vector<std::unordered_map<std::string, SQLiteValue>> _results:
    std::vector<std::map<std::string, SQLiteValue>> _results;
};

}
