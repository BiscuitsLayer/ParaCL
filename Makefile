all:	fb b r
fb:
		$(MAKE) -C Build
b:
		g++ main.cpp Language/lang.cpp Build/lex.yy.cc Build/lang.tab.cc -ggdb3 -o main
r:
		./main
