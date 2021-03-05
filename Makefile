CC = g++
LDFLAGS = -std=c++2a
CXXFLAGS = -MMD -ggdb3 -std=c++2a
Level = 2
Test = 4

all: main run

main: main.o Language/driver.o Settings/Settings.o Build/lex.yy.cc Build/lang.tab.cc \
	Language/Lang.o Language/LangInterface.o Language/SyntaxCheck.o

check: test
	./test

test: test.o Language/driver.o Settings/Settings.o Build/lex.yy.cc Build/lang.tab.cc \
	Language/Lang.o Language/LangInterface.o Language/SyntaxCheck.o -lgtest -lpthread

run:
	./main Test/Level_$(Level)/Correct/$(Test).cl

Build/lang.tab.cc: Language/lang.y
	bison --debug -o Build/lang.tab.cc Language/lang.y

Build/lex.yy.cc: Language/lang.l
	flex -o Build/lex.yy.cc Language/lang.l

.PHONY = all clean

-include *.d Language/*.d