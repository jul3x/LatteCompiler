#include "LocalSymbols.h"


LocalSymbols& LocalSymbols::getInstance() {
    static LocalSymbols instance;
    return instance;
}

bool LocalSymbols::append(const std::string &ident,
                          const std::string &type) {
    if (checkExistance(symbols_.back(), ident).first.empty())
    {
        auto it = count_of_decl_.find(ident);
        int index = 0;

        if (it != count_of_decl_.end())
        {
            index = ++(it->second);
        }
        else
        {
            count_of_decl_.insert(std::make_pair(ident, 1));
            index = 1;
        }

        symbols_.back().emplace(std::make_pair(ident, std::make_pair(type, index)));

        return true;
    }

    return false;
}

void LocalSymbols::reset() {
    symbols_.clear();
    count_of_decl_.clear();
}

void LocalSymbols::enterBlock() {
    symbols_.emplace_back();
}

void LocalSymbols::exitBlock() {
    symbols_.pop_back();
}

const std::string& LocalSymbols::getSymbolType(const std::string &ident) const {
    // fprintf(stderr, "Checking %s..\n", ident.c_str());

    for (auto it = symbols_.rbegin(); it != symbols_.rend(); ++it)
    {
        auto& symbol = checkExistance(*it, ident);

        if (!symbol.first.empty())
        {
            return symbol.first;
        }
    }

    std::string error = "Identifier " + ident + " not found!";
    throw std::invalid_argument(error.c_str());
}

int LocalSymbols::getSymbolIndex(const std::string &ident) const {
    for (auto it = symbols_.rbegin(); it != symbols_.rend(); ++it)
    {
        auto& symbol = checkExistance(*it, ident);

        if (!symbol.first.empty())
        {
            return symbol.second;
        }
    }

    std::string error = "Identifier " + ident + " not found!";
    throw std::invalid_argument(error.c_str());
}

const std::pair<std::string, int>& LocalSymbols::checkExistance(const SymbolTable &table,
                                                                const std::string &ident) const {
    static std::pair<std::string, int> NOT_FOUND = std::make_pair("", 0);

    auto it = table.find(ident);

    if (it != table.end())
    {
        return it->second;
    }

    return NOT_FOUND;
}
