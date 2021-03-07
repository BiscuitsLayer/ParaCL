//	SYSTEM
#include <fstream>

//	BISON AND FLEX
#include <FlexLexer.h>
#include "Language/driver.hpp"

//	LANGUAGE
#include "Language/Lang.hpp"

ScopeNodeInterface* globalCurrentScope = nullptr;
FunctionSymTable* globalFunctionSymTable = nullptr;

int main (int argc, char** argv) {
	std::ifstream programStream { argv[1] };
	if (!programStream) {
		std::cerr << "Error opening file!" << std::endl;
		return 0;
	}
	
	SyntaxCheck lexer {};
	yy::LangDriver driver { programStream, &lexer };
	if (driver.parse ()) {
		driver.execute ();
	}
	return 0;
}
