#include "HybridSelectQueryResult.hpp"

namespace margelo::rnquicksqlite {

HybridSelectQueryResult::HybridSelectQueryResult(std::vector<std::unordered_map<std::string, SQLiteValue>>&& results, std::vector<ColumnMetadata>&& metadata)
    : HybridSelectQueryResultSpec(), _results(std::move(results)), _metadata(std::move(metadata)) {}

std::vector<std::unordered_map<std::string, SQLiteValue>> HybridSelectQueryResult::getResults() {
    return this->_results;
};

void HybridSelectQueryResult::setResults(const std::vector<std::unordered_map<std::string, SQLiteValue>>& results) {
    this->_results = results;
};

std::vector<ColumnMetadata> HybridSelectQueryResult::getMetadata() {
    return this->_metadata;
}

void HybridSelectQueryResult::setMetadata(const std::vector<ColumnMetadata>& metadata) {
    this->_metadata = metadata;
}

}
