#include "HybridNativeQueryResult.hpp"

namespace margelo::nitro::rnquicksqlite {

QueryType HybridNativeQueryResult::getQueryType() {
  return this->_queryType;
}

std::optional<double> HybridNativeQueryResult::getInsertId() {
  return this->_insertId;
}
double HybridNativeQueryResult::getRowsAffected() {
  return this->_rowsAffected;
}

SQLiteQueryResults HybridNativeQueryResult::getResults() {
  return this->_results;
};

std::optional<SQLiteQueryTableMetadata> HybridNativeQueryResult::getMetadata() {
  return this->_metadata;
}

} // namespace margelo::nitro::rnquicksqlite
