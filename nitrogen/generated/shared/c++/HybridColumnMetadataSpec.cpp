///
/// HybridColumnMetadataSpec.cpp
/// Wed Sep 11 2024
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#include "HybridColumnMetadataSpec.hpp"

namespace margelo::nitro::rnquicksqlite {

  void HybridColumnMetadataSpec::loadHybridMethods() {
    // load base methods/properties
    HybridObject::loadHybridMethods();
    // load custom methods/properties
    registerHybrids(this, [](Prototype& prototype) {
      prototype.registerHybridGetter("name", &HybridColumnMetadataSpec::getName);
      prototype.registerHybridSetter("name", &HybridColumnMetadataSpec::setName);
      prototype.registerHybridGetter("type", &HybridColumnMetadataSpec::getType);
      prototype.registerHybridSetter("type", &HybridColumnMetadataSpec::setType);
      prototype.registerHybridGetter("index", &HybridColumnMetadataSpec::getIndex);
      prototype.registerHybridSetter("index", &HybridColumnMetadataSpec::setIndex);
    });
  }

} // namespace margelo::nitro::rnquicksqlite