//	SYSTEM
#include <fstream>

//	BISON AND FLEX
#include <FlexLexer.h>
#include "Language/driver.hpp"

//	LANGUAGE
#include "Language/Lang.hpp"

ScopeNodeInterface* globalCurrentScope = nullptr;

int main (int argc, char** argv) {
	std::ifstream infile { argv[1] };
	if (!infile) {
		std::cerr << "Error opening file!" << std::endl;
		return 0;
	}
	
	yy::LangDriver driver { infile };
	driver.parse ();
	
	return 0;
}
