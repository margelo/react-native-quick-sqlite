#include "HybridSelectQueryResultObject.hpp"

using namespace margelo::nitro::rnquicksqlite;

namespace margelo::rnquicksqlite {

HybridSelectQueryResultObject::HybridSelectQueryResultObject(const std::vector<std::map<std::string, SQLiteValue>>& results, const std::optional<std::vector<ColumnMetadata>>& metadata)
    : HybridSelectQueryResultSpec(), _results(results), _metadata(metadata) {}

std::optional<std::vector<ColumnMetadata>> HybridSelectQueryResultObject::getMetadata() {
    return this->_metadata;
}

void HybridSelectQueryResultObject::setMetadata(const std::optional<std::vector<ColumnMetadata>>& metadata) {
    this->_metadata = metadata;
}

std::string HybridSelectQueryResultObject::getString() {
    return "TODO";
}

double HybridSelectQueryResultObject::getNumber() {
    return -1.0;
}

bool HybridSelectQueryResultObject::getBoolean() {
    return false;
}

std::shared_ptr<ArrayBuffer> HybridSelectQueryResultObject::getArrayBuffer() {
    return nullptr;
}

}
