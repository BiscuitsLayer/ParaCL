#include <iostream>

#include <FlexLexer.h>
#include "Language/lang.hpp"

int main () {
	FlexLexer *lexer = new yyFlexLexer;
	yy::LangDriver driver { lexer };
	driver.parse ();
	return 0;
}
