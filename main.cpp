//	SYSTEM
#include <fstream>

//	BISON AND FLEX
#include <FlexLexer.h>
#include "Language/driver.hpp"

//	LANGUAGE
#include "Language/Lang.hpp"

ScopeNodeInterface* globalCurrentScope = nullptr;

int main (int argc, char** argv) {
	FlexLexer *lexer = new yyFlexLexer;
	yy::LangDriver driver { lexer };

	std::ifstream infile { argv[1] };
	if (!infile) {
		std::cerr << "Error opening file!" << std::endl;
		return 0;
	}

	lexer->switch_streams (infile, std::cout);

	globalCurrentScope = ScopeNodeInterface::CreateScopeNode (nullptr);
	driver.parse ();
	globalCurrentScope->Execute ();

	return 0;
}
