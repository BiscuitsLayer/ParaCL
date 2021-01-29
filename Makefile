all:	fb b r
fb:
		$(MAKE) -C Build
b:
		g++ main.cpp Language/driver.cpp Build/lex.yy.cc Build/lang.tab.cc \
		Language/Lang.cpp -ggdb3 -o main
r:
		./main Test/Input/Correct/6