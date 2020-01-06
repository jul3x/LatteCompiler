#include <cstdio>
#include <string>

#include "Parser.h"
#include "Printer.h"
#include "Absyn.h"
#include "SemAnalysisVisitor.h"
#include "CodeGenVisitor.h"
#include "GlobalSymbolsCollector.h"
#include "GlobalSymbols.h"
#include "ControlFlow.h"
#include "CompilerOutput.h"
#include "FunctionFrame.h"
#include "Utils.h"


void usage()
{
    printf("usage: Call with one of the following argument combinations:\n");
    printf("\t--help\t\tDisplay this help message.\n");
    printf("\t(no arguments)	Parse stdin verbosely.\n");
    printf("\t(files)\t\tParse content of files verbosely.\n");
    printf("\t-s (files)\tSilent mode. Parse content of files silently.\n");
}

int main(int argc, char **argv)
{
    FILE *input;
    int quiet = 0;
    char *filename = NULL;

    if (argc > 1)
    {
        if (strcmp(argv[1], "-s") == 0)
        {
            quiet = 1;
            if (argc > 2)
            {
                filename = argv[2];
            }
            else
            {
                input = stdin;
            }
        }
        else
        {
            filename = argv[1];
        }
    }

    if (filename)
    {
        input = fopen(filename, "r");
        if (!input)
        {
            usage();
            exit(1);
        }
    }
    else
        input = stdin;

    std::string directory, program_name, out_file;
    std::tie(directory, program_name, out_file) = generateOutNames(argv[1], "s");

    Program *parse_tree;

    try
    {
        parse_tree = pProgram(input);
    }
    catch (std::out_of_range &e)
    {
        CompilerOutput::getInstance().error(std::stoi(e.what()),
              "Integer value should be greater or equal"
              " -2147483648 and less or equal 2147483647!");

        CompilerOutput::getInstance().printErrorMsgs();
        return 1;
    }

    if (parse_tree)
    {
        GlobalSymbolsCollector *symbols_collector = new GlobalSymbolsCollector();
        GlobalSymbols::getInstance().addLibFunctions();
        symbols_collector->visitProgram(parse_tree);
        delete symbols_collector;

        try
        {
            if (GlobalSymbols::getInstance().areCorrect())
            {
                SemAnalysisVisitor *sem_analysis = new SemAnalysisVisitor();
                sem_analysis->visitProgram(parse_tree);
                delete sem_analysis;
            }

            ControlFlow::getInstance().checkFlow();
        }
        catch (const std::invalid_argument &e)
        {
            CompilerOutput::getInstance().error(-1, e.what());
        }

        if (!CompilerOutput::getInstance().printErrorMsgs())
        {
            FunctionFrame::getInstance().generatePointers();

            CompilerOutput::getInstance().initializeOutputFile(out_file);

            CompilerOutput::getInstance().printOutput(".data\n\n");

            for (const auto &str : GlobalSymbols::getInstance().getStrings())
            {
                CompilerOutput::getInstance().printOutput(str.second + ": .string \"");
                CompilerOutput::getInstance().printOutput(str.first, true);
                CompilerOutput::getInstance().printOutput("\"\n");
            }

            CompilerOutput::getInstance().printOutput(".text\n\n");

            for (const auto &fun : GlobalSymbols::getInstance().getFunctions())
            {
                if (!GlobalSymbols::getInstance().isLibFunction(fun.first))
                    CompilerOutput::getInstance().printOutput(".globl " + fun.first + "\n");
            }

            CodeGenVisitor *code_gen = new CodeGenVisitor(false);
            code_gen->visitProgram(parse_tree);
            delete code_gen;

            CompilerOutput::getInstance().deinitializeOutputFile();

            std::string exec_param = argv[0];
            auto last_slash_iter = exec_param.find_last_of('/');
            std::string relative_directory_exec =
                last_slash_iter == std::string::npos ? exec_param : exec_param.substr(0, last_slash_iter);
            std::string asm_command =
                "gcc -c -o " + directory + "/" + program_name + ".o -m32 " + directory + "/" + program_name + ".s";
            std::string linker_command =
                "gcc -o " + directory + "/" + program_name + " -m32 "
                + directory + "/" + program_name + ".o " + relative_directory_exec + "/lib/runtime.o";

            std::system(asm_command.c_str());
            std::system(linker_command.c_str());

            printf("Generated: %s/%s\n",
                directory.c_str(), program_name.c_str());

            CompilerOutput::getInstance().printOk();

            return 0;
        }
    }

    return 1;
}
