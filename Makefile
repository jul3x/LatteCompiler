CC=g++
CCFLAGS=-g -W -Wall

FLEX=flex
FLEX_OPTS=-PLatte

BISON=bison
BISON_OPTS=-t -pLatte

OBJS=Absyn.o Lexer.o Parser.o \
	 SemAnalysisVisitor.o GlobalSymbolsCollector.o CodeGenVisitor.o \
	 CompilerOutput.o ControlFlow.o MemoryFrames.o GlobalSymbols.o \
	 LabelGenerator.o LocalSymbols.o Postprocess.o
.PHONY: clean distclean

all: latc_x86

clean:
	cd src/
	rm -f *.o latc_x86 Latte.aux Latte.log Latte.pdf Latte.dvi Latte.ps Latte

latc_x86: ${OBJS} latc_x86.o
	@echo "Linking latc_x86..."
	${CC} ${CCFLAGS} ${OBJS} -Wno-unused-parameter latc_x86.o -o latc_x86

Absyn.o: src/Absyn.cpp src/Absyn.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/Absyn.cpp

src/Lexer.cpp: src/Latte.l
	${FLEX} -o src/Lexer.cpp src/Latte.l

src/Parser.cpp: src/Latte.y
	${BISON} src/Latte.y -o src/Parser.cpp

Lexer.o: src/Lexer.cpp src/Parser.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/Lexer.cpp

Parser.o: src/Parser.cpp src/Absyn.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/Parser.cpp

SemAnalysisVisitor.o: src/SemAnalysisVisitor.cpp src/SemAnalysisVisitor.h src/Absyn.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/SemAnalysisVisitor.cpp

CodeGenVisitor.o: src/CodeGenVisitor.cpp src/CodeGenVisitor.h src/Absyn.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/CodeGenVisitor.cpp

GlobalSymbolsCollector.o: src/GlobalSymbolsCollector.cpp src/GlobalSymbolsCollector.h src/Absyn.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/GlobalSymbolsCollector.cpp

CompilerOutput.o: src/CompilerOutput.cpp src/CompilerOutput.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/CompilerOutput.cpp

ControlFlow.o: src/ControlFlow.cpp src/ControlFlow.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/ControlFlow.cpp

MemoryFrames.o: src/MemoryFrames.cpp src/MemoryFrames.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/MemoryFrames.cpp

GlobalSymbols.o: src/GlobalSymbols.cpp src/GlobalSymbols.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/GlobalSymbols.cpp

LabelGenerator.o: src/LabelGenerator.cpp src/LabelGenerator.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/LabelGenerator.cpp

LocalSymbols.o: src/LocalSymbols.cpp src/LocalSymbols.h src/Absyn.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/LocalSymbols.cpp

Postprocess.o: src/Postprocess.cpp src/Postprocess.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/Postprocess.cpp

latc_x86.o: src/latc_x86.cpp src/Parser.h src/Absyn.h \
	src/SemAnalysisVisitor.h src/CodeGenVisitor.h \
	src/GlobalSymbolsCollector.h src/GlobalSymbols.h \
	src/ControlFlow.h src/CompilerOutput.h \
	src/MemoryFrames.h src/Utils.h src/Postprocess.h
	${CC} ${CCFLAGS} -Wno-unused-parameter -c src/latc_x86.cpp
