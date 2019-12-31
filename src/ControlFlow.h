#ifndef CONTROLFLOW_HEADER
#define CONTROLFLOW_HEADER

#include <vector>
#include <unordered_set>
#include <cstdio>
#include <algorithm>


class ControlFlow
{
public:
    static ControlFlow& getInstance() {
        static ControlFlow instance;
        return instance;
    }

    void newFunction(const std::string &name, const std::string &ret_type, int line_number) {
        simple_blocks_.emplace_back();
        function_names_.emplace_back(name, line_number);
        ret_types_.emplace_back(ret_type);
        termination_.emplace_back();
        reachable_.emplace_back();
        addBlock();
    }

    void enterInfiniteLoop() {
        infinite_loops_.push_back(getCurrentBlock());
    }

    void exitInfiniteLoop() {
        infinite_loops_.pop_back();
    }

    const std::string& getCurrentFunctionName() const {
        return function_names_.back().first;
    }

    const std::string& getCurrentFunctionType() const {
        return ret_types_.back();
    }

    void addBlock() {
        simple_blocks_.back().emplace_back();
        termination_.back().emplace_back(false);
        reachable_.back().emplace_back(false);
        was_if_ = false;
    }

    void addVirtualBlock(int p1, int p2) {
        virtual_p1_ = p1;
        virtual_p2_ = p2;

        was_if_ = true;
    }

    void addMissingBlock() {
        addBlock();
        auto virt_blk = getCurrentBlock();

        addChild(virtual_p1_, virt_blk);
        addChild(virtual_p2_, virt_blk);

        was_if_ = false;
    }

    bool wasIf() {
        return was_if_;
    }

    int getCurrentBlock() const {
        return simple_blocks_.back().size() - 1;
    }

    void addChild(int block, int child) {
        if (!termination_.back().at(block))
            simple_blocks_.back().at(block).emplace(child);
    }

    bool setTermination(const std::string &type) {
        termination_.back().back() = true;

        for (const auto &loop : infinite_loops_)
        {
            termination_.back().at(loop) = true;
            while_block_ = loop < while_block_ ? loop : while_block_;
            while_block_term_ = true;
        }

        if (type != ret_types_.back())
        {
            return false;
        }

        return true;
    }

    void prettyPrint() {
        int i = 0, j = 0, k = 0;
        for (const auto &fun : simple_blocks_)
        {
            fprintf(stderr, "Fun%d: \n", i);
            j = 0;
            for (const auto &vertex : fun)
            {
                fprintf(stderr, "%d: ", j);
                for (const auto &child : vertex)
                {
                    fprintf(stderr, "%d, ", child);
                }
                fprintf(stderr, "\n");
                ++j;
            }
            ++i;
        }
    }

    bool checkFlow() {
        int i = 0, j = 0;
        for (auto &fun : simple_blocks_)
        {
            setNonReachablePoints(i);
            j = 0;

            for (const auto &vertex : fun)
            {
                if (ret_types_.at(i) != "void" &&
                    vertex.empty() && !termination_.at(i).at(j) &&
                    reachable_.at(i).at(j))
                {
                    std::string error = "Function \"" + function_names_.at(i).first + "\""
                            " (line " + std::to_string(function_names_.at(i).second) + ")"
                            " does not have appropriate termination by return statement"
                            " in every path in control flow graph!\n";
                    throw std::invalid_argument(error);
                }
                ++j;
            }

            ++i;
        }

        return true;
    }


private:
    ControlFlow() : while_block_term_(false) {}

    void setNonReachablePoints(int fun) {
        reachable_.at(fun).at(0) = true;

        for (const auto &vertex : simple_blocks_.at(fun))
        {
            for (const auto &child : vertex)
                reachable_.at(fun).at(child) = true;
        }

        if (while_block_term_)
        {
            for (size_t i = while_block_; i < reachable_.at(fun).size(); ++i)
            {
                reachable_.at(fun).at(i) = false;
            }
        }
    }

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

    int virtual_p1_, virtual_p2_;
    bool was_if_;

    int while_block_;
    bool while_block_term_;

};

#endif
