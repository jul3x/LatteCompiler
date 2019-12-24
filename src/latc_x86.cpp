#include <cstdio>
#include <string>

#include "Parser.h"
#include "Printer.h"
#include "Absyn.h"
#include "SemAnalysisVisitor.h"
#include "GlobalSymbolsCollector.h"
#include "GlobalSymbols.h"
#include "ControlFlow.h"


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

    Program *parse_tree = pProgram(input);
    if (parse_tree)
    {
        printf("\nParse Succesful!\n");
        if (!quiet)
        {
            printf("\n[Abstract Syntax]\n");
            ShowAbsyn *s = new ShowAbsyn();
            printf("%s\n\n", s->show(parse_tree));
            printf("[Linearized Tree]\n");
            delete s;

            PrintAbsyn *p = new PrintAbsyn();
            printf("%s\n\n", p->print(parse_tree));
            delete p;

            try
            {
                GlobalSymbolsCollector *symbols_collector = new GlobalSymbolsCollector();
                GlobalSymbols::getInstance().addLibFunctions();
                symbols_collector->visitProgram(parse_tree);
                delete symbols_collector;

                if (GlobalSymbols::getInstance().areCorrect())
                {
                    fprintf(stderr, "GlobalSymbols are correct!\n");
                    SemAnalysisVisitor *sem_analysis = new SemAnalysisVisitor();
                    sem_analysis->visitProgram(parse_tree);
                    delete sem_analysis;
                }

                ControlFlow::getInstance().prettyPrint();
            }
            catch (const std::invalid_argument& e)
            {
                fprintf(stderr, "ERROR\n");
                fprintf(stderr, "%s\n", e.what());
                return 1;
            }
        }

        return 0;
    }
    return 1;
}
