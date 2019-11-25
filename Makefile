CC=g++
CCFLAGS=-g -W -Wall

FLEX=flex
FLEX_OPTS=-PLatte

BISON=bison
BISON_OPTS=-t -pLatte

OBJS=Absyn.o Lexer.o Parser.o Printer.o SemAnalysisVisitor.o GlobalSymbolsCollector.o 

.PHONY: clean distclean

all: latc_x86

clean:
	cd src/
	rm -f *.o latc_x86 Latte.aux Latte.log Latte.pdf Latte.dvi Latte.ps Latte

latc_x86: ${OBJS} latc_x86.o
	@echo "Linking latc_x86..."
	${CC} ${CCFLAGS} ${OBJS} latc_x86.o -o latc_x86

Absyn.o: src/Absyn.cpp src/Absyn.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/Absyn.cpp

src/Lexer.cpp: src/Latte.l
	${FLEX} -o src/Lexer.cpp src/Latte.l

src/Parser.cpp: src/Latte.y
	${BISON} src/Latte.y -o src/Parser.cpp

Lexer.o: src/Lexer.cpp src/Parser.h
	${CC} ${CCFLAGS} -c src/Lexer.cpp 

Parser.o: src/Parser.cpp src/Absyn.h
	${CC} ${CCFLAGS} -c src/Parser.cpp

Printer.o: src/Printer.cpp src/Printer.h src/Absyn.h
	${CC} ${CCFLAGS} -c src/Printer.cpp

SemAnalysisVisitor.o: src/SemAnalysisVisitor.cpp src/SemAnalysisVisitor.h src/Absyn.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/SemAnalysisVisitor.cpp

GlobalSymbolsCollector.o: src/GlobalSymbolsCollector.cpp src/GlobalSymbolsCollector.h src/Absyn.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/GlobalSymbolsCollector.cpp

latc_x86.o: src/latc_x86.cpp src/Parser.h src/Printer.h src/Absyn.h src/SemAnalysisVisitor.h
	${CC} ${CCFLAGS} -c src/latc_x86.cpp
