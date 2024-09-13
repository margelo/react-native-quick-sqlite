#pragma once

#include "HybridNativeQueryResultSpec.hpp"
#include "Types.hpp"
#include <map>

using namespace margelo::rnquicksqlite;

namespace margelo::nitro::rnquicksqlite {

class HybridNativeQueryResult : public HybridNativeQueryResultSpec {
public:
  HybridSelectQueryResult() : HybridObject(TAG) {}
  HybridSelectQueryResult(SQLiteQueryResults&& results, SQLiteQueryTableMetadata&& metadata)
      : HybridObject(TAG), _results(std::move(results)), _metadata(std::move(metadata)) {}

private:
  QueryType _queryType;
  std::optional<double> _insertId;
  double _rowsAffected;
  SQLiteQueryResults _results;
  std::optional<SQLiteQueryTableMetadata> _metadata;

public:
  // Properties
  QueryType getQueryType() override;
  std::optional<double> getInsertId() override;
  double getRowsAffected() override;
  SQLiteQueryTableResults getResults() override;
  std::optional<SQLiteQueryTableMetadata> getMetadata() override;
};

} // namespace margelo::nitro::rnquicksqlite
