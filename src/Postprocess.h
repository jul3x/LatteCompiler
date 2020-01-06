#ifndef POSTPROCESS_HEADER
#define POSTPROCESS_HEADER

#include <string>
#include <fstream>


class Postprocess
{
public:
    Postprocess() = default;

    void initialize(const std::string &in, const std::string &out);

    void deinitialize();

    void execute();

private:
    std::ifstream in_file_;
    std::ofstream out_file_;
    std::string in_filename_, out_filename_;

};

#endif
