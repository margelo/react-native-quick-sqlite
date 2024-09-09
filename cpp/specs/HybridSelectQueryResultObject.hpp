#pragma once

#include "HybridSelectQueryResultSpec.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

class HybridSelectQueryResultObject: public HybridSelectQueryResultSpec {
public:
    // Properties
    std::optional<std::vector<ColumnMetadata>> getMetadata() override;
    void setMetadata(const std::optional<std::vector<ColumnMetadata>>& metadata) override;

public:
    // Methods
    std::string getString() override;
    double getNumber() override;
    bool getBoolean() override;
    std::shared_ptr<ArrayBuffer> getArrayBuffer() override;
};

}
