CCC = clang++
LEX = flex
YACC = bison
CFLAGS = -Wall --coverage -g
LEXFLAGS = -Wno-unused

LEXDEBUG = -d
YACCDEBUG = -vtd

OBJS = main.o parse.tab.o lex.yy.o ast.o

all: run

test: run
	python runtests.py


report:
	lcov --capture --directory . --output-file cov.info
	genhtml cov.info --output-directory report
	echo Coverage report in report/index.html

run: $(OBJS)
	$(CCC) $(CFLAGS) -o run $(OBJS)

main.o: main.cpp
	$(CCC) $(CFLAGS) -c main.cpp

ast.o: ast.cpp
	$(CCC) $(CFLAGS) -c ast.cpp

parse.tab.c: parse.y
	$(YACC) $(YACCDEBUG) parse.y

parse.tab.o: parse.tab.c
	$(CCC) $(CFLAGS) -c parse.tab.c

lex.yy.c: scan.l parse.tab.o
	$(LEX) scan.l

lex.yy.o: lex.yy.c
	$(CCC) $(CFLAGS) $(LEXFLAGS) -c lex.yy.c
	
clean:
	rm -f run *.o parse.tab.c lex.yy.c
	rm -f parse.tab.h
	rm -f graph.gv graph.png
	rm -f *.gcda *.gcno *.bb *.bbg *.da *.gcov
	rm -rf report cov.info

graph:
	make test
	dot -Tpng graph.gv -o graph.png
	see *.png