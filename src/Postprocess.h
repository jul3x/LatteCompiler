#ifndef POSTPROCESS_HEADER
#define POSTPROCESS_HEADER

#include <string>
#include <fstream>


class Postprocess
{
    enum class State {
        None,
        WasPush,
        WasPop,
        WasRet,
        WasLabel
    };

public:
    Postprocess();

    void initialize(const std::string &in, const std::string &out);

    void deinitialize();

    void execute();

private:
    State state_;
    std::string previous_name_;

    std::ifstream in_file_;
    std::ofstream out_file_;
    std::string in_filename_, out_filename_;

};

#endif
