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

    std::string directory, class_name, out_file;
    std::tie(directory, class_name, out_file) = generateOutNames(argv[1], "s");

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
            CompilerOutput::getInstance().initializeOutputFile(out_file);

            CompilerOutput::getInstance().printOutput(".data\n\n");
            CompilerOutput::getInstance().printOutput(".text\n\n");

            for (const auto &fun : GlobalSymbols::getInstance().getFunctions())
                CompilerOutput::getInstance().printOutput("globl " + fun.first + "\n");

            CodeGenVisitor *code_gen = new CodeGenVisitor();
            code_gen->visitProgram(parse_tree);
            delete code_gen;

            CompilerOutput::getInstance().deinitializeOutputFile();

            CompilerOutput::getInstance().printOk();

            return 0;
        }
    }

    return 1;
}
