#ifndef LABELGENERATOR_HEADER
#define LABELGENERATOR_HEADER

#include <string>

class LabelGenerator
{
public:
    LabelGenerator(const LabelGenerator&) = delete;
    LabelGenerator& operator=(const LabelGenerator&) = delete;

    static LabelGenerator& getInstance() {
        static LabelGenerator instance;
        return instance;
    }

    std::string getNewLabel() {
        return ".L" + std::to_string(++current_index_);
    }

private:
    LabelGenerator() {
        current_index_ = 0;
    }

    unsigned int current_index_;
};

#endif
