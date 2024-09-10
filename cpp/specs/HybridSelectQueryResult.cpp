#include "HybridSelectQueryResult.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

HybridSelectQueryResult::HybridSelectQueryResult(const std::vector<std::unordered_map<std::string, SQLiteValue>>& results, const std::vector<ColumnMetadata>& metadata)
    : HybridSelectQueryResultSpec(), _results(results), _metadata(metadata) {}

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

//std::string HybridSelectQueryResult::getString() {
//    return "TODO";
//}
//
//double HybridSelectQueryResult::getNumber() {
//    return -1.0;
//}
//
//bool HybridSelectQueryResult::getBoolean() {
//    return false;
//}

std::shared_ptr<ArrayBuffer> HybridSelectQueryResult::getArrayBuffer() {
    return nullptr;
}

}
