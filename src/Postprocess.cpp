#include "Postprocess.h"


void Postprocess::initialize(const std::string &in, const std::string &out) {
    in_filename_ = in;
    out_filename_ = out;

    in_file_.open(in_filename_);
    out_file_.open(out_filename_);
}

void Postprocess::deinitialize() {
    in_file_.close();
    out_file_.close();
    remove(in_filename_.c_str());
}

void Postprocess::execute() {
    std::string line;

    while (std::getline(in_file_, line))
    {
        out_file_ << line << "\n";
    }
}
