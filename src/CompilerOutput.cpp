#include "CompilerOutput.h"

CompilerOutput& CompilerOutput::getInstance() {
    static CompilerOutput instance;
    return instance;
}

void CompilerOutput::initializeOutputFile(const std::string &filename) {
    filename_ = filename;
    out_file_.open(filename);
}

void CompilerOutput::deinitializeOutputFile() {
    out_file_.close();
    output_.clear();
}

void CompilerOutput::appendOutput(const std::string &new_line) {
    output_ = output_ + new_line;
}

void CompilerOutput::saveOutput() {
    out_file_ << output_;
    output_.clear();
}

void CompilerOutput::printOutput(const std::string &what, bool format) {
    if (!format)
        out_file_ << what;
    else
    {
        const char *s = what.c_str();
        char formatted[10];
        while (*s) {
            if (isalnum((unsigned char) *s))
                sprintf(formatted, "%c", *s);
            else
                sprintf(formatted, "\\%03hho", *s);
            out_file_ << formatted;
            s++;
        }
    }
}

void CompilerOutput::destroyOutputFile() {
    deinitializeOutputFile();
    remove(filename_.c_str());
}

void CompilerOutput::error(int line, const std::string &msg) {
    if (line != -1)
        error_msgs_.emplace_back("Error line " + std::to_string(line) + ": " + msg + "\n");
    else
        error_msgs_.emplace_back("Error detected: " + msg + "\n");
}

bool CompilerOutput::printErrorMsgs() const {
    if (error_msgs_.empty())
        return 0;

    fprintf(stderr, "ERROR!\n");
    for (const auto &msg : error_msgs_)
    {
        fprintf(stderr, "%s", msg.c_str());
    }

    return 1;
}

void CompilerOutput::printOk() const {
    fprintf(stderr, "OK!\n");
}



