CC = g++
LDFLAGS = -std=c++2a
CXXFLAGS = -MMD -ggdb3 -std=c++2a
TEST = Functions/10

all: main run

main: main.o Language/driver.o Build/lex.yy.cc Build/lang.tab.cc \
	Language/Lang.o Language/LangInterface.o Language/SyntaxCheck.o

run:
	./main Test/$(TEST)

Build/lang.tab.cc: Language/lang.y
	bison --debug -o Build/lang.tab.cc Language/lang.y

Build/lex.yy.cc: Language/lang.l
	flex -o Build/lex.yy.cc Language/lang.l

.PHONY = all clean

include *.d Language/*.d