#ifndef COMPILERMSGS_HEADER
#define COMPILERMSGS_HEADER

#include <vector>
#include <string>
#include <cstdio>


class CompilerMsgs
{
public:
    static CompilerMsgs& getInstance() {
        static CompilerMsgs instance;
        return instance;
    }

    void error(int line, const std::string &msg) {
        if (line != -1)
            error_msgs_.emplace_back("Error line " + std::to_string(line) + ": " + msg + "\n");
        else
            error_msgs_.emplace_back("Error detected: " + msg + "\n");
    }

    bool printErrorMsgs() const {
        if (error_msgs_.empty())
            return 0;

        fprintf(stderr, "ERROR!\n");
        for (const auto &msg : error_msgs_)
        {
            fprintf(stderr, "%s", msg.c_str());
        }

        return 1;
    }

    void printOk() const {
        fprintf(stderr, "OK!\n");
    }

private:
    CompilerMsgs() = default;

    std::vector<std::string> error_msgs_;

};

#endif
