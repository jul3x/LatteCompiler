CC=g++
CCFLAGS=-g -W -Wall

FLEX=flex
FLEX_OPTS=-PLatte

BISON=bison
BISON_OPTS=-t -pLatte

OBJS=Absyn.o Lexer.o Parser.o Printer.o

.PHONY: clean distclean

all: TestLatte

clean:
	rm -f *.o TestLatte Latte.aux Latte.log Latte.pdf Latte.dvi Latte.ps Latte

distclean: clean
	rm -f Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H Makefile Latte.l Latte.y Latte.tex 

TestLatte: ${OBJS} Test.o
	@echo "Linking TestLatte..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o TestLatte

Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: Latte.l
	${FLEX} -oLexer.C Latte.l

Parser.C: Latte.y
	${BISON} Latte.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C 

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -Wno-unused-parameter -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C
