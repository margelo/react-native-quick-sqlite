#include "HybridColumnMetadata.hpp"

namespace margelo::rnquicksqlite {

HybridColumnMetadata::HybridColumnMetadata(std::string&& name, ColumnType&& type, double index)
    : HybridColumnMetadataSpec(), _name(std::move(name)), _type(std::move(type)), _index(index) {}

std::string HybridColumnMetadata::getName() {
    return this->_name;
};

void HybridColumnMetadata::setName(const std::string& name) {
    this->_name = name;
};
ColumnType HybridColumnMetadata::getType() {
    return this->_type;
};

void HybridColumnMetadata::setType(ColumnType type) {
    this->_type = type;
};

double HybridColumnMetadata::getIndex() {
    return this->_index;
};

void HybridColumnMetadata::setIndex(double index) {
    this->_index = index;
};

}
