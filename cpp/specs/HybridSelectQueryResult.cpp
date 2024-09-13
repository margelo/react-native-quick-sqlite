#include "HybridSelectQueryResult.hpp"

namespace margelo::nitro::rnquicksqlite {

TableResults HybridSelectQueryResult::getResults() {
  return this->_results;
};

void HybridSelectQueryResult::setResults(const TableResults& results) {
  this->_results = results;
};

TableMetadata HybridSelectQueryResult::getMetadata() {
  return this->_metadata;
}

void HybridSelectQueryResult::setMetadata(const TableMetadata& metadata) {
  this->_metadata = metadata;
}

} // namespace margelo::nitro::rnquicksqlite
