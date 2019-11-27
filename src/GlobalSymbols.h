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
        if (checkExistance(ident))
        {
            functions_.emplace(std::make_pair(ident, std::make_pair(type, args)));
        }
    }

    void appendClass(const std::string &ident,
                     const std::string &parent) {
        if (checkExistance(ident))
        {
            classes_.emplace(std::make_pair(ident, parent));
        }
    }

    bool areCorrect() const {
        // For now only checking if int main() exists
        auto it = functions_.find("main");

        if (it == functions_.end())
        {
            std::string error = "Main function definition does not exists!\n";
            throw std::invalid_argument(error.c_str());
        }
        else
        {
            if (it->second.first->get() != "int")
            {
                std::string error = "Main function should return int!\n";
                throw std::invalid_argument(error.c_str());
            }

            if (!it->second.second->getTypes().empty())
            {
                std::string error = "Main function should not take any arguments!\n";
                throw std::invalid_argument(error.c_str());
            }
        }

        return true;
    }

private:
    GlobalSymbols() = default;

    bool checkExistance(const std::string &ident) {
        if (classes_.find(ident) != classes_.end())
        {
            std::string error = "Identifier " + ident + " already exists as a class name!\n";
            throw std::invalid_argument(error.c_str());
        }

        if (functions_.find(ident) != functions_.end())
        {
            std::string error = "Identifier " + ident + " already exists as a function name!\n";
            throw std::invalid_argument(error.c_str());
        }

        return true;
    }

    std::unordered_map<std::string, FunctionType> functions_;
    std::unordered_map<std::string, ClassParent> classes_;
};

#endif
