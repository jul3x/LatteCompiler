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

    void newFunction(const std::string &name, const std::string &ret_type) {
        simple_blocks_.emplace_back();
        function_names_.emplace_back(name);
        ret_types_.emplace_back(ret_type);
        termination_.emplace_back();
        reachable_.emplace_back();
        addBlock();
    }

    const std::string& getCurrentFunctionName() const {
        return function_names_.back();
    }

    void addBlock() {
        simple_blocks_.back().emplace_back();
        termination_.back().emplace_back(false);
        reachable_.back().emplace_back(false);
        was_if_ = false;
    }

    void addVirtualBlock(int p1, int p2)
    {
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

    void setTermination(const std::string &type) {
        if (type != ret_types_.back())
        {
            std::string error = "Return type " + type +
                " does not match declared function return type: " + ret_types_.back() + "!\n";
            throw std::invalid_argument(error);
        }

        termination_.back().back() = true;
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
                    throw std::invalid_argument("Not every path in control flow graph"
                                                " is properly terminated by return instruction!\n");
                }
                ++j;
            }

            ++i;
        }

        return true;
    }


private:
    ControlFlow() = default;

    void setNonReachablePoints(int fun) {
        reachable_.at(fun).at(0) = true;

        for (const auto &vertex : simple_blocks_.at(fun))
        {
            for (const auto &child : vertex)
                reachable_.at(fun).at(child) = true;
        }
    }

    // Functions vector -> vertices vector -> childs set
    std::vector<std::vector<std::unordered_set<int>>> simple_blocks_;

    // Functions return types
    std::vector<std::string> ret_types_;

    // Functions names
    std::vector<std::string> function_names_;

    // True if block in function was terminated by return
    std::vector<std::vector<bool>> termination_;

    // True if block in function is reachable
    std::vector<std::vector<bool>> reachable_;

    int virtual_p1_, virtual_p2_;
    bool was_if_;

};

#endif
