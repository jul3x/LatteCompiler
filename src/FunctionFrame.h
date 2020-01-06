#ifndef FUNCTIONFRAME_HEADER
#define FUNCTIONFRAME_HEADER

#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <map>

#include "GlobalSymbols.h"


class FunctionFrame
{
public:
    using Locals = std::map<std::pair<std::string, int>, int>;

    static FunctionFrame& getInstance();

    int getPointer(const std::string &fn_ident, const std::string &loc_ident, int index);

    int getNumberOfBytesAlloc(const std::string &fn_ident);

    void generatePointers();

    void printPointers();

private:
    FunctionFrame() = default;

    void generatePointers(const std::string &fn_ident);

    std::unordered_map<std::string, Locals> functions_;
    std::unordered_map<std::string, int> bytes_alloc_;
};

#endif
