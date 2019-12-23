#ifndef LOCALSYMBOLS_HEADER
#define LOCALSYMBOLS_HEADER

#include <unordered_map>
#include <tuple>
#include <stack>
#include <string>

#include "Absyn.h"


class LocalSymbols
{
    using SymbolTable = std::unordered_map<std::string, std::string>;
public:
    static LocalSymbols& getInstance() {
        static LocalSymbols instance;
        return instance;
    }

    void append(const std::string &ident,
                const std::string &type) {
        if (checkExistance(symbols_.back(), ident).empty())
        {
            symbols_.back().emplace(std::make_pair(ident, type));
            fprintf(stderr, "Declaring %s as %s...\n", ident.c_str(), type.c_str());
        }
        else
        {
            std::string error = "Identifier " + ident + " was already declared in this scope!\n";
            throw std::invalid_argument(error.c_str());
        }
    }

    void enterBlock() {
        symbols_.emplace_back();
        fprintf(stderr, "Entering block.\n");
    }

    void exitBlock() {
        symbols_.pop_back();
        fprintf(stderr, "Exiting block.\n");
    }

    const std::string& getSymbolType(const std::string &ident) const {
        fprintf(stderr, "Checking %s..\n", ident.c_str());

        for (auto it = symbols_.rbegin(); it != symbols_.rend(); ++it)
        {
            auto& type = checkExistance(*it, ident);

            if (!type.empty())
            {
                return type;
            }
        }

        std::string error = "Identifier " + ident + " not found!\n";
        throw std::invalid_argument(error.c_str());
    }

private:
    LocalSymbols() = default;

    const std::string& checkExistance(const SymbolTable &table,
                                      const std::string &ident) const {
        static std::string NOT_FOUND = "";
        auto it = table.find(ident);

        if (it != table.end())
        {
            return it->second;
        }

        return NOT_FOUND;
    }

    std::vector<SymbolTable> symbols_;

};

#endif
