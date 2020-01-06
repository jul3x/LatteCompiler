#include "Postprocess.h"


Postprocess::Postprocess() : state_(State::None), previous_name_("") {}

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
    bool start = false;
    bool text = false;
    while (std::getline(in_file_, line))
    {
        if (!start && !text && !line.empty() && line == ".text")
            text = true;

        if (!start && text && !line.empty() && line.at(0) != '.')
            start = true;
        else if (!start)
            out_file_ << line << "\n";

        if (!start)
            continue;

        switch (state_)
        {
            case State::None:
            {
                if (line.substr(0, 8) == "  pushl ")
                {
                    state_ = State::WasPush;
                    previous_name_ = line.substr(8);
                }
                else if (line.substr(0, 7) == "  popl ")
                {
                    state_ = State::WasPop;
                    previous_name_ = line.substr(7);
                }
                else if (line == "  ret")
                {
                    state_ = State::WasRet;
                    out_file_ << line << "\n";
                }
                else if (!line.empty() && line.at(0) == '.')
                {
                    state_ = State::WasLabel;
                    previous_name_ = line.substr(1);
                }
                else
                {
                    out_file_ << line << "\n";
                }

                break;
            }
            case State::WasPop:
            {
                if (line.substr(0, 8) == "  pushl ")
                {
                    auto new_name = line.substr(8);

                    if (previous_name_ != new_name)
                    {
                        out_file_ << "  popl " + previous_name_ << "\n";
                        state_ = State::WasPush;
                        previous_name_ = line.substr(8);
                    }
                    else
                    {
                        state_ = State::None;
                    }
                }
                else if (line.substr(0, 7) == "  popl ")
                {
                    out_file_ << "  popl " + previous_name_ << "\n";
                    state_ = State::WasPop;
                    previous_name_ = line.substr(7);
                }
                else if (line == "  ret")
                {
                    state_ = State::WasRet;
                    out_file_ << line << "\n";
                }
                else if (!line.empty() && line.at(0) == '.')
                {
                    out_file_ << "  popl " + previous_name_ << "\n";
                    state_ = State::WasLabel;
                    previous_name_ = line.substr(1);
                }
                else
                {
                    out_file_ << "  popl " + previous_name_ << "\n";
                    out_file_ << line << "\n";
                    state_ = State::None;
                }
                break;
            }
            case State::WasPush:
            {
                if (line.substr(0, 8) == "  pushl ")
                {
                    out_file_ << "  pushl " + previous_name_ << "\n";
                    state_ = State::WasPush;
                    previous_name_ = line.substr(8);
                }
                else if (line.substr(0, 7) == "  popl ")
                {
                    auto new_name = line.substr(7);

                    if (previous_name_ != new_name)
                    {
                        out_file_ << "  movl " + previous_name_ + ", " + new_name + "\n";
                        state_ = State::None;
                        previous_name_ = "";
                    }
                    else
                    {
                        state_ = State::None;
                    }
                }
                else if (line == "  ret")
                {
                    state_ = State::WasRet;
                    out_file_ << line << "\n";
                }
                else if (!line.empty() && line.at(0) == '.')
                {
                    out_file_ << "  pushl " + previous_name_ << "\n";
                    state_ = State::WasLabel;
                    previous_name_ = line.substr(1);
                }
                else
                {
                    out_file_ << "  pushl " + previous_name_ << "\n";
                    out_file_ << line << "\n";
                    state_ = State::None;
                }
                break;
            }
            case State::WasRet:
            {
                if (!line.empty() && line.at(0) == '.')
                {
                    state_ = State::WasLabel;
                    previous_name_ = line.substr(1);
                }
                else if (!line.empty() && line.at(0) != ' ')
                {
                    out_file_ << line << "\n";
                    state_ = State::None;
                }

                break;
            }
            case State::WasLabel:
            {
                if (line.empty())
                {
                    state_ = State::None;
                    previous_name_ = "";
                    break;
                }

                if (line.substr(0, 8) == "  pushl ")
                {
                    out_file_ << "." << previous_name_ << "\n";
                    state_ = State::WasPush;
                    previous_name_ = line.substr(8);
                }
                else if (line.substr(0, 7) == "  popl ")
                {
                    out_file_ << "." << previous_name_ << "\n";
                    state_ = State::WasPop;
                    previous_name_ = line.substr(7);
                }
                else if (line == "  ret")
                {
                    out_file_ << "." << previous_name_ << "\n";
                    state_ = State::WasRet;
                    out_file_ << line << "\n";
                }
                else if (!line.empty() && line.at(0) == '.')
                {
                    out_file_ << "." << previous_name_ << "\n";
                    state_ = State::WasLabel;
                    previous_name_ = line.substr(1);
                }
                else
                {
                    out_file_ << "." << previous_name_ << "\n";
                    out_file_ << line << "\n";
                    state_ = State::None;
                }

                break;
            }
        }
    }
}
