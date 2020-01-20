#ifndef GLOBALSYMBOLS_HEADER
#define GLOBALSYMBOLS_HEADER

#include <unordered_map>
#include <set>
#include <algorithm>
#include <tuple>
#include <string>
#include <iostream>

#include "Absyn.h"

class GlobalSymbols
{

public:
    using Locals = std::vector<std::tuple<std::string, std::string, int, bool>>;
    using FunctionType = std::tuple<Type*, ListArg*, Locals>;

    using ClassVars = std::vector<std::pair<std::string, std::string>>;
    using ClassMethods = std::unordered_map<std::string, std::tuple<Type*, ListArg*, std::string>>;
    using ClassType = std::tuple<std::string, ClassVars, ClassMethods>;

    static GlobalSymbols& getInstance();

    ~GlobalSymbols();

    bool isLibFunction(const std::string &name);

    void addLibFunctions();

    bool appendFunc(const std::string &ident,
                    Type *type,
                    ListArg *args);

    bool appendClass(const std::string &ident,
                     const std::string &parent);

    bool appendParameters(const std::string &fn_ident, const std::string &loc_ident,
                          const std::string &type, int index);

    bool appendLocals(const std::string &fn_ident, const std::string &loc_ident,
                      const std::string &type, int index);

    bool appendClassVars(const std::string &cls_ident, const std::string &var_ident,
                         const std::string &type);

    bool appendClassMethod(const std::string &cls_ident, const std::string &ident,
                           Type *type, ListArg *args);

    void appendClassMethodLocal(const std::string &local);

    bool methodLocalExists(const std::string &local);

    void appendSymbolsFromInheritedClass(const std::string &cls_ident, const std::string &inh_ident);

    const Locals& getFunctionLocals(const std::string &fn_ident) const;

    const ClassVars& getClassVars(const std::string &cls_ident) const;

    const ClassMethods& getClassMethods(const std::string &cls_ident) const;

    void appendString(const std::string &str);

    const std::string& getStringLabel(const std::string &str) const;

    const std::unordered_map<std::string, std::string> getStrings() const;

    bool areCorrect() const;

    bool checkType(const std::string &type) const;

    std::string getFunctionType(const std::string &ident) const;

    ListArg* getFunctionArgs(const std::string &ident) const;

    std::string getMethodType(const std::string &cls_ident, const std::string &ident) const;

    ListArg* getMethodArgs(const std::string &cls_ident, const std::string &ident) const;

    const std::string& getMethodOwner(const std::string &cls_ident, const std::string &ident) const;

    const std::string& getVarInClassType(const std::string &cls_ident, const std::string &ident) const;

    void setClassInitialized(const std::string &cls_ident);

    bool isClassInitialized(const std::string &cls_ident) const;

    void prettyPrint() const;

    const std::unordered_map<std::string, FunctionType>& getFunctions() const;

    const std::unordered_map<std::string, ClassType>& getClasses() const;

    void generateClassParents();

    bool isClassParent(const std::string &cls, const std::string &parent);

private:
    GlobalSymbols();

    inline bool checkExistance(const std::string &ident);

    inline bool searchForMain() const;

    inline bool checkInheritanceCorrectness() const;

    inline void generateClassParents(const std::string &cls_ident);

    bool checkInheritanceUtil(size_t cls_i, const std::vector<int> &inherit,
                              std::vector<bool> &visited, std::vector<bool> &stack) const;

    std::unordered_map<std::string, FunctionType> functions_;

    std::unordered_map<std::string, ClassType> classes_;
    std::unordered_map<std::string, std::set<std::string>> class_parents_;
    std::unordered_map<std::string, bool> class_initialized_;
    std::set<std::string> temporary_method_locals_;

    std::unordered_map<std::string, std::string> strings_;
    std::set<std::string> lib_functions_;

    // helpers
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
