#pragma once

#include "HybridNativeQueryResultSpec.hpp"
#include "Types.hpp"
#include <map>

using namespace margelo::rnquicksqlite;

namespace margelo::nitro::rnquicksqlite {

class HybridNativeQueryResult : public HybridNativeQueryResultSpec {
public:
  HybridSelectQueryResult() : HybridObject(TAG) {}
  HybridSelectQueryResult(std::optional<double> insertId, double rowsAffected, SQLiteQueryResults&& results, SQLiteQueryTableMetadata&& metadata)
      : HybridObject(TAG), _insertId(insertId), _rowsAffected(rowsAffected) _results(std::move(results)), _metadata(std::move(metadata)) {}

private:
  std::optional<double> _insertId;
  double _rowsAffected;
  SQLiteQueryResults _results;
  std::optional<SQLiteQueryTableMetadata> _metadata;

public:
  // Properties
  std::optional<double> getInsertId() override;
  double getRowsAffected() override;
  SQLiteQueryTableResults getResults() override;
  std::optional<SQLiteQueryTableMetadata> getMetadata() override;
};

} // namespace margelo::nitro::rnquicksqlite
