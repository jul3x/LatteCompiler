#ifndef CONTROLFLOW_HEADER
#define CONTROLFLOW_HEADER

#include <vector>
#include <unordered_set>
#include <cstdio>
#include <algorithm>


class ControlFlow
{
public:
    static ControlFlow& getInstance();

    void newFunction(const std::string &name, const std::string &ret_type, int line_number);

    void newClass(const std::string &name);

    void enterInfiniteLoop();

    void exitInfiniteLoop();

    const std::string& getCurrentFunctionName() const;

    const std::string& getCurrentFunctionType() const;

    const std::string& getCurrentClassName() const;

    void addBlock();

    void addVirtualBlock(int p1, int p2);

    void addMissingBlock();

    bool wasIf();

    int getCurrentBlock() const;

    void addChild(int block, int child);

    bool setTermination(const std::string &type);

    void prettyPrint();

    bool checkFlow();

private:
    ControlFlow();

    void setNonReachablePoints(int fun);

    // Functions vector -> vertices vector -> childs set
    std::vector<std::vector<std::unordered_set<int>>> simple_blocks_;

    // Functions return types
    std::vector<std::string> ret_types_;

    // Functions names
    std::vector<std::pair<std::string, int>> function_names_;

    // True if block in function was terminated by return
    std::vector<std::vector<bool>> termination_;

    // True if block in function is reachable
    std::vector<std::vector<bool>> reachable_;

    std::vector<int> infinite_loops_;

    std::string current_class_;

    int virtual_p1_, virtual_p2_;
    bool was_if_;

    int while_block_;
    bool while_block_term_;

};

#endif
