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
    static CompilerOutput& getInstance();
    
    void initializeOutputFile(const std::string &filename);

    void deinitializeOutputFile();

    void appendOutput(const std::string &new_line);

    void saveOutput();

    void printOutput(const std::string &what, bool format = false);

    void destroyOutputFile();

    void error(int line, const std::string &msg);

    bool printErrorMsgs() const;

    void printOk() const;

private:
    CompilerOutput() = default;

    std::vector<std::string> error_msgs_;

    std::ofstream out_file_;
    std::string filename_;
    std::string output_;

};

#endif
