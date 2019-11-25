#ifndef GLOBALSYMBOLS_HEADER
#define GLOBALSYMBOLS_HEADER

#include <unordered_map>
#include <tuple>
#include <string>

#include "Absyn.h"

class GlobalSymbols
{
public:
    using FunctionType = std::pair<Type*, ListArg*>;
    using ClassParent = std::string;

    static GlobalSymbols& getInstance() {
        static GlobalSymbols instance;
        return instance;
    }

    void appendFunc(const std::string &ident,
                    Type *type,
                    ListArg *args) {
        auto it = functions_.find(ident);
        auto it_class = classes_.find(ident);

        if (it_class != classes_.end())
        {
            std::string error = "Identifier " + ident + " already exists as a class name!\n";
            throw std::invalid_argument(error.c_str());
        }

        if (it != functions_.end())
        {
            std::string error = "Identifier " + ident + " already exists as a function name!\n";
            throw std::invalid_argument(error.c_str());
        }

        functions_.emplace(std::make_pair(ident, std::make_pair(type, args)));
    }

    void appendClass(const std::string &ident,
                     const std::string &parent) {
        auto it_func = functions_.find(ident);
        auto it = classes_.find(ident);

        if (it_func != functions_.end())
        {
            std::string error = "Identifier " + ident + " already exists as a function name!\n";
            throw std::invalid_argument(error.c_str());
        }

        if (it != classes_.end())
        {
            std::string error = "Identifier " + ident + " already exists as a class name!\n";
            throw std::invalid_argument(error.c_str());
        }

        classes_.emplace(std::make_pair(ident, parent));
    }

private:
    GlobalSymbols() = default;

    std::unordered_map<std::string, FunctionType> functions_;
    std::unordered_map<std::string, ClassParent> classes_;
};

#endif
