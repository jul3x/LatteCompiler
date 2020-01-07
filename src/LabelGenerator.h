#ifndef LABELGENERATOR_HEADER
#define LABELGENERATOR_HEADER

#include <string>

class LabelGenerator
{
public:
    LabelGenerator(const LabelGenerator&) = delete;
    LabelGenerator& operator=(const LabelGenerator&) = delete;

    static LabelGenerator& getInstance();

    std::string getNewLabel();

private:
    LabelGenerator();

    unsigned int current_index_;
};

#endif
