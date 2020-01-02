#ifndef COMPILEROUTPUT_HEADER
#define COMPILEROUTPUT_HEADER

#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>


class CompilerOutput
{
public:
    static CompilerOutput& getInstance() {
        static CompilerOutput instance;
        return instance;
    }

    void initializeOutputFile(const std::string &filename) {
        filename_ = filename;
        out_file_.open(filename);
    }

    void deinitializeOutputFile() {
        out_file_.close();
        output_.clear();
    }

    void appendOutput(const std::string &new_line) {
        output_ = output_ + new_line;
    }

    void saveOutput() {
        out_file_ << output_;
        output_.clear();
    }

    void printOutput(const std::string &what) {
        out_file_ << what;
    }

    void destroyOutputFile() {
        deinitializeOutputFile();
        remove(filename_.c_str());
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
    CompilerOutput() = default;

    std::vector<std::string> error_msgs_;

    std::ofstream out_file_;
    std::string filename_;
    std::string output_;

};

#endif
