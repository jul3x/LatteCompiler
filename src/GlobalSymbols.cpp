#include "GlobalSymbols.h"


GlobalSymbols& GlobalSymbols::getInstance() {
    static GlobalSymbols instance;
    return instance;
}

GlobalSymbols::~GlobalSymbols() {
    delete string_args;
    delete int_args;
    delete empty_args;
    delete void_type;
    delete string_type;
    delete int_type;
}

bool GlobalSymbols::isLibFunction(const std::string &name) {
    if (lib_functions_.find(name) != lib_functions_.end())
    {
        return true;
    }

    return false;
}

void GlobalSymbols::addLibFunctions() {
    lib_functions_.insert("printInt");
    lib_functions_.insert("printString");
    lib_functions_.insert("error");
    lib_functions_.insert("readInt");
    lib_functions_.insert("readString");

    appendFunc("printInt", void_type, int_args);
    appendFunc("printString", void_type, string_args);
    appendFunc("error", void_type, empty_args);
    appendFunc("readInt", int_type, empty_args);
    appendFunc("readString", string_type, empty_args);
}

bool GlobalSymbols::appendFunc(const std::string &ident,
                               Type *type,
                               ListArg *args) {
    if (!checkExistance(ident))
    {
        functions_.emplace(std::make_pair(ident, std::make_tuple(type, args, Locals{})));

        return true;
    }

    return false;
}

bool GlobalSymbols::appendClass(const std::string &ident,
                                const std::string &parent) {
    if (!checkExistance(ident))
    {
        classes_.emplace(std::make_pair(ident,
            std::make_tuple(parent, ClassVars{}, ClassMethods{})));
        class_initialized_.emplace(std::make_pair(ident, false));
        return true;
    }

    return false;
}

bool GlobalSymbols::appendParameters(const std::string &fn_ident, const std::string &loc_ident,
                                     const std::string &type, int index) {
    auto function = functions_.find(fn_ident);

    if (function != functions_.end())
    {
        std::get<2>(function->second).push_back({loc_ident, type, index, true});
        return true;
    }

    return false;
}

bool GlobalSymbols::appendLocals(const std::string &fn_ident, const std::string &loc_ident,
                                 const std::string &type, int index) {
    auto function = functions_.find(fn_ident);

    if (function != functions_.end())
    {
        std::get<2>(function->second).push_back({loc_ident, type, index, false});
        return true;
    }

    return false;
}

bool GlobalSymbols::appendClassVars(const std::string &cls_ident, const std::string &var_ident,
                                    const std::string &type) {
    auto cls = classes_.find(cls_ident);

    if (cls != classes_.end())
    {
        for (const auto &cls_var : std::get<1>(cls->second))
        {
            if (cls_var.first == var_ident)
                return false;
        }

        std::get<1>(cls->second).push_back(std::make_pair(var_ident, type));
        return true;
    }

    return false;
}

bool GlobalSymbols::appendClassMethod(const std::string &cls_ident, const std::string &ident,
                                      Type *type, ListArg *args) {
    auto cls = classes_.find(cls_ident);

    if (checkExistance(ident))
    {
        return false;
    }

    if (cls != classes_.end())
    {
        auto meth = std::get<2>(cls->second).find(ident);

        if (meth != std::get<2>(cls->second).end())
            return false;

        std::get<2>(cls->second).insert(std::make_pair(ident, std::make_tuple(type, args, cls_ident)));
        temporary_method_locals_.clear();
        return true;
    }

    return false;
}

void GlobalSymbols::appendClassMethodLocal(const std::string &local) {
    temporary_method_locals_.insert(local);
}

bool GlobalSymbols::methodLocalExists(const std::string &local) {
    auto it = temporary_method_locals_.find(local);

    return it != temporary_method_locals_.end();
}

void GlobalSymbols::appendSymbolsFromInheritedClass(const std::string &cls_ident,
                                                    const std::string &inh_ident) {
    auto cls = classes_.find(cls_ident);
    auto inh = classes_.find(inh_ident);

    for (const auto &inh_var : std::get<1>(inh->second))
    {
        std::get<1>(cls->second).push_back(inh_var);
    }

    for (const auto &inh_meth : std::get<2>(inh->second))
    {
        std::get<2>(cls->second).insert(inh_meth);
    }
}

const GlobalSymbols::Locals& GlobalSymbols::getFunctionLocals(const std::string &fn_ident) const {
    auto function = functions_.find(fn_ident);

    if (function != functions_.end())
    {
        return std::get<2>(function->second);
    }

    throw std::invalid_argument("Function " + fn_ident + " not found!");
}

const GlobalSymbols::ClassVars& GlobalSymbols::getClassVars(const std::string &cls_ident) const {
    auto cls = classes_.find(cls_ident);

    if (cls != classes_.end())
    {
        return std::get<1>(cls->second);
    }

    throw std::invalid_argument("Class " + cls_ident + " not found!");
}

const GlobalSymbols::ClassMethods& GlobalSymbols::getClassMethods(const std::string &cls_ident) const {
    auto cls = classes_.find(cls_ident);

    if (cls != classes_.end())
    {
        return std::get<2>(cls->second);
    }

    throw std::invalid_argument("Class " + cls_ident + " not found!");
}

void GlobalSymbols::appendString(const std::string &str) {
    std::string label = "loc_str_val$" + std::to_string(strings_.size());

    strings_.insert(std::make_pair(str, label));
}

const std::string& GlobalSymbols::getStringLabel(const std::string &str) const {
    return strings_.find(str)->second;
}

const std::unordered_map<std::string, std::string> GlobalSymbols::getStrings() const {
    return strings_;
}

bool GlobalSymbols::areCorrect() const {
    return this->checkInheritanceCorrectness() && this->searchForMain();
}

bool GlobalSymbols::checkType(const std::string &type) const {
    auto class_it = classes_.find(type);

    if (class_it == classes_.end() &&
        type != "int" && type != "void" && type != "boolean" && type != "string" &&
        type != "int[]" && type != "boolean[]" && type != "string[]")
    {
        if (type.length() > 2 && type.substr(type.length() - 2) == "[]")
        {
            auto class_it_2 = classes_.find(type.substr(0, type.length() - 2));

            if (class_it_2 != classes_.end())
                return true;
        }

        return false;
    }

    return true;
}

std::string GlobalSymbols::getFunctionType(const std::string &ident) const {
    auto function = functions_.find(ident);

    if (function != functions_.end())
    {
        return std::get<0>(function->second)->get();
    }
    else
    {
        throw std::invalid_argument("");
    }
}

ListArg* GlobalSymbols::getFunctionArgs(const std::string &ident) const {
    auto function = functions_.find(ident);

    if (function != functions_.end())
    {
        return std::get<1>(function->second);
    }
    else
    {
        throw std::invalid_argument("");
    }
}

std::string GlobalSymbols::getMethodType(const std::string &cls_ident, const std::string &ident) const {
    auto cls = classes_.find(cls_ident);

    if (cls != classes_.end())
    {
        auto meth = std::get<2>(cls->second).find(ident);

        if (meth != std::get<2>(cls->second).end())
        {
            return std::get<0>(meth->second)->get();
        }

        throw std::invalid_argument("Class \"" + cls_ident + "\" does not contain symbol \"" + ident + "\"!");
    }

    throw std::invalid_argument("Unknown variable type \"" + cls_ident + "\"!");
}

ListArg* GlobalSymbols::getMethodArgs(const std::string &cls_ident, const std::string &ident) const {
    auto cls = classes_.find(cls_ident);

    if (cls != classes_.end())
    {
        auto meth = std::get<2>(cls->second).find(ident);

        if (meth != std::get<2>(cls->second).end())
        {
            return std::get<1>(meth->second);
        }

        throw std::invalid_argument("Class \"" + cls_ident + "\" does not contain symbol \"" + ident + "\"!");
    }

    throw std::invalid_argument("Unknown variable type \"" + cls_ident + "\"!");
}

const std::string& GlobalSymbols::getMethodOwner(const std::string &cls_ident, const std::string &ident) const {
    auto cls = classes_.find(cls_ident);

    if (cls != classes_.end())
    {
        auto meth = std::get<2>(cls->second).find(ident);

        if (meth != std::get<2>(cls->second).end())
        {
            return std::get<2>(meth->second);
        }

        throw std::invalid_argument("Class \"" + cls_ident + "\" does not contain symbol \"" + ident + "\"!");
    }

    throw std::invalid_argument("Unknown variable type \"" + cls_ident + "\"!");
}

const std::string& GlobalSymbols::getVarInClassType(const std::string &cls_ident, const std::string &ident) const {
    auto cls = classes_.find(cls_ident);

    if (cls != classes_.end())
    {
        for (const auto &cls_var : std::get<1>(cls->second))
        {
            if (cls_var.first == ident)
                return cls_var.second;
        }

        throw std::invalid_argument("Class \"" + cls_ident + "\" does not contain symbol \"" + ident + "\"!");
    }

    throw std::invalid_argument("Unknown variable type \"" + cls_ident + "\"!");
}

void GlobalSymbols::setClassInitialized(const std::string &cls_ident) {
    auto cls = class_initialized_.find(cls_ident);

    if (cls != class_initialized_.end())
    {
        cls->second = true;
    }
}

bool GlobalSymbols::isClassInitialized(const std::string &cls_ident) const {
    auto cls = class_initialized_.find(cls_ident);

    if (cls != class_initialized_.end())
    {
        return cls->second;
    }

    return false;
}

void GlobalSymbols::prettyPrint() const {
    for (const auto &function : functions_)
    {
        fprintf(stderr, "\n%s: \n", function.first.c_str());

        for (const auto &local : std::get<2>(function.second))
        {
            fprintf(stderr, "%s %s, %d\n",
                std::get<0>(local).c_str(), std::get<1>(local).c_str(), std::get<2>(local));
        }
    }
}

const std::unordered_map<std::string, GlobalSymbols::FunctionType>& GlobalSymbols::getFunctions() const {
    return functions_;
}

const std::unordered_map<std::string, GlobalSymbols::ClassType>& GlobalSymbols::getClasses() const {
    return classes_;
}

GlobalSymbols::GlobalSymbols() {
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

inline bool GlobalSymbols::checkExistance(const std::string &ident) {
    if (classes_.find(ident) != classes_.end())
    {
        return true;
    }

    if (functions_.find(ident) != functions_.end())
    {
        return true;
    }

    return false;
}

inline bool GlobalSymbols::searchForMain() const {
    auto it = functions_.find("main");

    if (it == functions_.end())
    {
        std::string error = "Main function definition does not exists!";
        throw std::invalid_argument(error.c_str());
    }
    else
    {
        if (std::get<0>(it->second)->get() != "int")
        {
            std::string error = "Main function should return int!";
            throw std::invalid_argument(error.c_str());
        }

        if (!std::get<1>(it->second)->getTypes().empty())
        {
            std::string error = "Main function should not take any arguments!";
            throw std::invalid_argument(error.c_str());
        }
    }

    return true;
}

inline bool GlobalSymbols::checkInheritanceCorrectness() const {
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
        auto parent_it = cls_index.find(std::get<0>(it->second));
        if (parent_it != cls_index.end())
        {
            inheritance.at(cls_index.find(it->first)->second) =
                std::get<0>(it->second) == "" ? -1 : parent_it->second;
        }
        else if (std::get<0>(it->second) != "")
        {
            std::string error = "Parent class \"" + std::get<0>(it->second) + "\" of class \"" +
                it->first + "\" does not exists!!";
            throw std::invalid_argument(error.c_str());
        }
    }

    std::vector<bool> visited(classes_.size(), false), stack(classes_.size(), false);

    for (size_t i = 0; i < classes_.size(); ++i)
    {
        if (checkInheritanceUtil(i, inheritance, visited, stack))
        {
            std::string error = "Detected cycles in inheritance of classes!";
            throw std::invalid_argument(error.c_str());
        }
    }

    return true;
}

bool GlobalSymbols::checkInheritanceUtil(size_t cls_i, const std::vector<int> &inherit,
                                         std::vector<bool> &visited, std::vector<bool> &stack) const {
    if(visited.at(cls_i) == false)
    {
        visited.at(cls_i) = true;
        stack.at(cls_i) = true;

        if (inherit.at(cls_i) != -1)
        {
            if (!visited.at(inherit.at(cls_i)) &&
                checkInheritanceUtil(inherit.at(cls_i), inherit, visited, stack))
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

void GlobalSymbols::generateClassParents() {
    for (const auto &cls : classes_)
    {
        class_parents_.insert(std::make_pair(cls.first, std::set<std::string>{}));
        generateClassParents(cls.first);
    }
}

bool GlobalSymbols::isClassParent(const std::string &cls_ident, const std::string &parent) {
    auto cls = class_parents_.find(cls_ident);

    if (cls != class_parents_.end())
    {
        auto prnt = cls->second.find(parent);

        if (prnt != cls->second.end())
            return true;
    }

    return false;
}

inline void GlobalSymbols::generateClassParents(const std::string &cls_ident) {
    auto cls = classes_.find(cls_ident);
    auto parents = class_parents_.find(cls_ident);

    while (!std::get<0>(cls->second).empty())
    {
        parents->second.insert(std::get<0>(cls->second));

        cls = classes_.find(std::get<0>(cls->second));
    }
}
