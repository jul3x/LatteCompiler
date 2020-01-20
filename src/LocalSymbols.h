#ifndef LOCALSYMBOLS_HEADER
#define LOCALSYMBOLS_HEADER

#include <unordered_map>
#include <tuple>
#include <stack>
#include <string>

#include "Absyn.h"


class LocalSymbols
{
    using SymbolTable = std::unordered_map<std::string, std::tuple<std::string, int, bool>>;

public:
    static LocalSymbols& getInstance();

    bool append(const std::string &ident,
                const std::string &type,
                bool is_reference = false);

    void reset();

    void enterBlock();

    void exitBlock();

    const std::string& getSymbolType(const std::string &ident) const;

    int getSymbolIndex(const std::string &ident) const;

    bool isSymbolReference(const std::string &ident) const;

private:
    LocalSymbols() = default;

    const std::tuple<std::string, int, bool>& checkExistance(const SymbolTable &table,
                                                             const std::string &ident) const;

    std::vector<SymbolTable> symbols_;
    std::unordered_map<std::string, int> count_of_decl_;

};

#endif
