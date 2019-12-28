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

    ~GlobalSymbols() {
        delete string_args;
        delete int_args;
        delete empty_args;
        delete void_type;
        delete string_type;
        delete int_type;
    }

    void addLibFunctions() {
        appendFunc("printInt", void_type, int_args);
        appendFunc("printString", void_type, string_args);
        appendFunc("error", void_type, empty_args);
        appendFunc("readInt", int_type, empty_args);
        appendFunc("readString", string_type, empty_args);
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
        return this->checkInheritanceCorrectness() && this->searchForMain();
    }

    bool checkType(const std::string &type) const {
        auto class_it = classes_.find(type);

        if (class_it == classes_.end() &&
            type != "int" && type != "void" && type != "boolean" && type != "string" &&
            type != "int[]" && type != "boolean[]" && type != "string[]")
        {
            std::string error = type + " is not a valid type name!\n";
            throw std::invalid_argument(error.c_str());
        }

        return true;
    }

    std::string getFunctionType(const std::string &ident) const {
        auto function = functions_.find(ident);

        if (function != functions_.end())
        {
            return function->second.first->get();
        }
        else
        {
            std::string error = "Identifier " + ident + " does not exists as a function name!\n";
            throw std::invalid_argument(error.c_str());
        }
    }

    ListArg* getFunctionArgs(const std::string &ident) const {
        auto function = functions_.find(ident);

        if (function != functions_.end())
        {
            return function->second.second;
        }
        else
        {
            std::string error = "Identifier " + ident + " does not exists as a function name!\n";
            throw std::invalid_argument(error.c_str());
        }
    }


private:
    GlobalSymbols() {
        void_type = new StVarType(new Void);
        string_type = new StVarType(new Str);
        int_type = new StVarType(new Int);

        int_arg = new Ar(int_type, "x");
        str_arg = new Ar(string_type, "x");

        empty_args = new ListArg;
        int_args = new ListArg;
        int_args->push_back(int_arg);

        string_args = new ListArg;
        string_args->push_back(str_arg);
    }

    inline bool checkExistance(const std::string &ident) {
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

    inline bool searchForMain() const {
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

    inline bool checkInheritanceCorrectness() const {
        // Making graph from class definitions
        std::unordered_map<std::string, int> cls_index;
        std::vector<int> inheritance(classes_.size(), -1);

        int ind = 0;
        for (auto it = classes_.begin(); it != classes_.end(); ++it)
        {
            cls_index.emplace(it->first, ind++);
        }

        for (auto it = classes_.begin(); it != classes_.end(); ++it)
        {
            auto parent_it = cls_index.find(it->second);
            if (parent_it != cls_index.end())
            {
                inheritance.at(cls_index.find(it->first)->second) =
                    it->second == "" ? -1 : parent_it->second;
            }
            else if (it->second != "")
            {
                std::string error = "Parent class \"" + it->second + "\" of class \"" +
                    it->first + "\" does not exists!!\n";
                throw std::invalid_argument(error.c_str());
            }
        }

        std::vector<bool> visited(classes_.size(), false), stack(classes_.size(), false);

        for(size_t i = 0; i < classes_.size(); ++i)
        {
            if (checkInheritanceUtil(i, inheritance, visited, stack))
            {
                std::string error = "Detected cycles in inheritance of classes!\n";
                throw std::invalid_argument(error.c_str());
            }
        }

        return true;
    }

    bool checkInheritanceUtil(size_t cls_i, const std::vector<int> &inherit,
                              std::vector<bool> &visited, std::vector<bool> &stack) const {
        if(visited.at(cls_i) == false)
        {
            visited.at(cls_i) = true;
            stack.at(cls_i) = true;

            if (inherit.at(cls_i) != -1)
            {
                if (!visited.at(inherit.at(cls_i)) && checkInheritanceUtil(inherit.at(cls_i), inherit, visited, stack))
                {
                    return true;
                }
                else if (stack.at(inherit.at(cls_i)))
                {
                    return true;
                }
            }
        }

        stack.at(cls_i) = false;
        return false;
    }

    std::unordered_map<std::string, FunctionType> functions_;
    std::unordered_map<std::string, ClassParent> classes_;

    Type *void_type;
    Type *string_type;
    Type *int_type;

    Arg *int_arg;
    Arg *str_arg;

    ListArg *empty_args;
    ListArg *int_args;
    ListArg *string_args;
};

#endif
