all:	fb b r
fb:
		$(MAKE) -C Build
b:
		g++ main.cpp -std=c++2a Language/driver.cpp Build/lex.yy.cc Build/lang.tab.cc \
		Language/Lang.cpp Language/LangInterface.cpp Language/SyntaxCheck.cpp -ggdb3 -o main
r:
		./main Test/Functions/5