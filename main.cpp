#include <iostream>

//	BISON AND FLEX
#include <FlexLexer.h>
#include "Language/driver.hpp"

//	LANGUAGE
#include "Language/Lang.hpp"

Scope* globalCurrentScope = nullptr;

int main () {
	FlexLexer *lexer = new yyFlexLexer;
	yy::LangDriver driver { lexer };

	globalCurrentScope = new Scope (nullptr, nullptr);
	driver.parse ();
	globalCurrentScope->Execute ();

	return 0;
}
