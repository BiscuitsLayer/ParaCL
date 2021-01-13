all:	fb b r
fb:
		$(MAKE) -C Build
b:
		g++ main.cpp 														\
		Language/driver.cpp Language/LangInterface.cpp Language/Lang.cpp 	\
		Build/lex.yy.cc Build/lang.tab.cc -ggdb3 -o main
r:
		./main Test/test2.input
