#ifndef MEMORYFRAMES_HEADER
#define MEMORYFRAMES_HEADER

#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <map>

#include "GlobalSymbols.h"


class MemoryFrames
{
public:
    using Locals = std::map<std::pair<std::string, int>, int>;

    using ClassVars = std::unordered_map<std::string, int>;

    static MemoryFrames& getInstance();

    int getPointer(const std::string &fn_ident, const std::string &loc_ident, int index) const;

    int getNumberOfBytesAlloc(const std::string &fn_ident) const;

    int getOffsetInClass(const std::string &cls_ident, const std::string &var_ident) const;

    int getSizeofClass(const std::string &cls_ident) const;

    void generatePointers();

    void generateClassOffsets();

    void printPointers() const;

    void printClasses() const;

private:
    MemoryFrames() = default;

    void generatePointers(const std::string &fn_ident);

    void generateClassOffsets(const std::string &cls_ident);

    std::unordered_map<std::string, Locals> functions_;
    std::unordered_map<std::string, int> bytes_alloc_;

    std::unordered_map<std::string, ClassVars> classes_;
    std::unordered_map<std::string, int> classes_sizeof_;
};

#endif
