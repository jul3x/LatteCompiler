#include "LocalSymbols.h"


LocalSymbols& LocalSymbols::getInstance() {
    static LocalSymbols instance;
    return instance;
}

bool LocalSymbols::append(const std::string &ident,
                          const std::string &type,
                          bool is_reference) {
    if (std::get<0>(checkExistance(symbols_.back(), ident)).empty())
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

        symbols_.back().emplace(std::make_pair(ident, std::make_tuple(type, index, is_reference)));

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

        if (!std::get<0>(symbol).empty())
        {
            return std::get<0>(symbol);
        }
    }

    std::string error = "Identifier " + ident + " not found!";
    throw std::invalid_argument(error.c_str());
}

int LocalSymbols::getSymbolIndex(const std::string &ident) const {
    for (auto it = symbols_.rbegin(); it != symbols_.rend(); ++it)
    {
        auto& symbol = checkExistance(*it, ident);

        if (!std::get<0>(symbol).empty())
        {
            return std::get<1>(symbol);
        }
    }

    std::string error = "Identifier " + ident + " not found!";
    throw std::invalid_argument(error.c_str());
}

bool LocalSymbols::isSymbolReference(const std::string &ident) const {
    for (auto it = symbols_.rbegin(); it != symbols_.rend(); ++it)
    {
        auto& symbol = checkExistance(*it, ident);

        if (!std::get<0>(symbol).empty())
        {
            return std::get<2>(symbol);
        }
    }

    std::string error = "Identifier " + ident + " not found!";
    throw std::invalid_argument(error.c_str());
}

const std::tuple<std::string, int, bool>& LocalSymbols::checkExistance(const SymbolTable &table,
                                                                       const std::string &ident) const {
    static std::tuple<std::string, int, bool> NOT_FOUND = std::make_tuple("", 0, false);

    auto it = table.find(ident);

    if (it != table.end())
    {
        return it->second;
    }

    return NOT_FOUND;
}
