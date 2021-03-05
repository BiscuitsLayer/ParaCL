CC = g++
LDFLAGS = -std=c++2a
CXXFLAGS = -MMD -ggdb3 -std=c++2a
TEST = Level_2/Correct/6.cl

all: main run

main: main.o Language/driver.o Settings/Settings.o Build/lex.yy.cc Build/lang.tab.cc \
	Language/Lang.o Language/LangInterface.o Language/SyntaxCheck.o

check: test
	./test

test: test.o Language/driver.o Settings/Settings.o Build/lex.yy.cc Build/lang.tab.cc \
	Language/Lang.o Language/LangInterface.o Language/SyntaxCheck.o -lgtest -lpthread

run:
	./main Test/$(TEST)

Build/lang.tab.cc: Language/lang.y
	bison --debug -o Build/lang.tab.cc Language/lang.y

Build/lex.yy.cc: Language/lang.l
	flex -o Build/lex.yy.cc Language/lang.l

.PHONY = all clean

-include *.d Language/*.d