#include "MemoryFrames.h"


MemoryFrames& MemoryFrames::getInstance() {
    static MemoryFrames instance;
    return instance;
}

int MemoryFrames::getPointer(const std::string &fn_ident, const std::string &loc_ident, int index) const {
    auto function = functions_.find(fn_ident);

    if (function != functions_.end())
    {
        return (function->second.find(std::make_pair(loc_ident, index)))->second;
    }

    return 0;
}

int MemoryFrames::getNumberOfBytesAlloc(const std::string &fn_ident) const {
    auto bytes = bytes_alloc_.find(fn_ident);

    if (bytes != bytes_alloc_.end())
    {
        return bytes->second;
    }

    return 0;
}

int MemoryFrames::getOffsetInClass(const std::string &cls_ident, const std::string &var_ident) const {
    auto cls = classes_.find(cls_ident);

    if (cls != classes_.end())
    {
        return (cls->second.find(var_ident))->second;
    }

    return 0;
}

int MemoryFrames::getSizeofClass(const std::string &cls_ident) const {
    auto cls = classes_sizeof_.find(cls_ident);

    if (cls != classes_sizeof_.end())
    {
        return cls->second;
    }

    return 0;
}

void MemoryFrames::generatePointers() {
    auto &func = GlobalSymbols::getInstance().getFunctions();

    for (auto &fun : func)
    {
        functions_.insert(std::make_pair(fun.first, Locals{}));
        bytes_alloc_.insert(std::make_pair(fun.first, 0));
        generatePointers(fun.first);
    }
}

void MemoryFrames::generateClassOffsets() {
    auto &classes = GlobalSymbols::getInstance().getClasses();

    for (auto &cls : classes)
    {
        classes_.insert(std::make_pair(cls.first, ClassVars{}));
        classes_sizeof_.insert(std::make_pair(cls.first, 0));
        generateClassOffsets(cls.first);
    }
}

void MemoryFrames::printPointers() const {
    for (const auto &fun : functions_)
    {
        fprintf(stderr, "%s:\n", fun.first.c_str());

        for (const auto &loc : fun.second)
        {
            fprintf(stderr, "%s, %d: %d\n", 
                loc.first.first.c_str(), loc.first.second,
                getPointer(fun.first, loc.first.first, loc.first.second));
        }
    }
}

void MemoryFrames::printClasses() const {
    for (const auto &cls : classes_)
    {
        fprintf(stderr, "%s:\n", cls.first.c_str());
        fprintf(stderr, "size: %d\n", classes_sizeof_.find(cls.first)->second);
        for (const auto &var : cls.second)
        {
            fprintf(stderr, "%s, %d\n", var.first.c_str(), var.second);
        }
    }
}

void MemoryFrames::generatePointers(const std::string &fn_ident) {
    auto function = functions_.find(fn_ident);
    int args_pos = 8;
    int local_pos = -4;

    if (function != functions_.end())
    {
        auto& locals = GlobalSymbols::getInstance().getFunctionLocals(function->first);

        for (const auto &local : locals)
        {
            if (std::get<3>(local))
            {
                function->second.insert(std::make_pair(
                    std::make_pair(std::get<0>(local), std::get<2>(local)), args_pos));
                args_pos += 4;
            }
            else
            {
                function->second.insert(std::make_pair(
                    std::make_pair(std::get<0>(local), std::get<2>(local)), local_pos));
                local_pos -= 4;
                bytes_alloc_.find(fn_ident)->second += 4;
            }
        }

        return;
    }

    throw std::invalid_argument("Function " + fn_ident + " not found!");
}

void MemoryFrames::generateClassOffsets(const std::string &cls_ident) {
    auto cls = classes_.find(cls_ident);
    int offset = 0;

    if (cls != classes_.end())
    {
        auto& cls_vars = GlobalSymbols::getInstance().getClassVars(cls->first);
        auto cls_sizeof = classes_sizeof_.find(cls_ident);
        offset = 0;
        for (const auto &var : cls_vars)
        {
            cls->second.insert(std::make_pair(var.first, offset));
            cls_sizeof->second += 4;
            offset += 4;
        }

        return;
    }

    throw std::invalid_argument("Class " + cls_ident + " not found!");
}
