#pragma once

#include <map>
#include "HybridColumnMetadataSpec.hpp"
#include "Types.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

class HybridColumnMetadata: public HybridColumnMetadataSpec {
public:
    HybridColumnMetadata(std::string&& name, ColumnType&& type, double index);

public:
  // Properties
  std::string getName() override;
  void setName(const std::string& name) override;
  ColumnType getType() override;
  void setType(ColumnType type) override;
  double getIndex() override;
  void setIndex(double index) override;

private:
    std::string _name;
    ColumnType _type;
    double _index;
};

}
