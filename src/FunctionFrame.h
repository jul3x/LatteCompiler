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

    static FunctionFrame& getInstance() {
        static FunctionFrame instance;
        return instance;
    }

    int getPointer(const std::string &fn_ident, const std::string &loc_ident, int index) {
        auto function = functions_.find(fn_ident);

        if (function != functions_.end())
        {
            return (function->second.find(std::make_pair(loc_ident, index)))->second;
        }

        return 0;
    }

    int getNumberOfBytesAlloc(const std::string &fn_ident) {
        auto bytes = bytes_alloc_.find(fn_ident);

        if (bytes != bytes_alloc_.end())
        {
            return bytes->second;
        }

        return 0;
    }

    void generatePointers() {
        auto &func = GlobalSymbols::getInstance().getFunctions();

        for (auto &fun : func)
        {
            functions_.insert(std::make_pair(fun.first, Locals{}));
            bytes_alloc_.insert(std::make_pair(fun.first, 0));
            generatePointers(fun.first);
        }
    }

    void printPointers() {
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

private:
    FunctionFrame() = default;

    void generatePointers(const std::string &fn_ident) {
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

    std::unordered_map<std::string, Locals> functions_;
    std::unordered_map<std::string, int> bytes_alloc_;
};

#endif
