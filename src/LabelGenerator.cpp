#include "LabelGenerator.h"


LabelGenerator& LabelGenerator::getInstance() {
    static LabelGenerator instance;
    return instance;
}

std::string LabelGenerator::getNewLabel() {
    return ".L" + std::to_string(++current_index_);
}

LabelGenerator::LabelGenerator() {
    current_index_ = 0;
}
