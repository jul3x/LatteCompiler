#ifndef CONTROLFLOW_HEADER
#define CONTROLFLOW_HEADER

#include <vector>
#include <unordered_set>
#include <cstdio>


class ControlFlow
{
public:
    static ControlFlow& getInstance() {
        static ControlFlow instance;
        return instance;
    }

    void newFunction() {
        simple_blocks_.emplace_back();
        addBlock();
    }

    void addBlock() {
        simple_blocks_.back().emplace_back();
    }

    int getCurrentBlock() const {
        return simple_blocks_.back().size() - 1;
    }

    void addChild(int block, int child) {
        simple_blocks_.back().at(block).emplace(child);
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


private:
    ControlFlow() = default;

    // Functions vector -> vertices vector -> childs set
    std::vector<std::vector<std::unordered_set<int>>> simple_blocks_;

};

#endif
