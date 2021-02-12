//	SYSTEM
#include <fstream>

//	BISON AND FLEX
#include <FlexLexer.h>
#include "Language/driver.hpp"

//	LANGUAGE
#include "Language/Lang.hpp"

ScopeNodeInterface* globalCurrentScope = nullptr;
FunctionSymTable* globalFunctionSymTable = nullptr;
int codePass = 0;

int main (int argc, char** argv) {
	std::ifstream infile { argv[1] };
	if (!infile) {
		ERRSTREAM << "Error opening file!" << std::endl;
		return 0;
	}
	
	yy::LangDriver driver { infile };
	if (driver.parse ()) {
		driver.execute ();
	}
	
	return 0;
}
