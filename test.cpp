//	SYSTEM
#include <fstream>

//	BISON AND FLEX
#include <FlexLexer.h>
#include "Language/driver.hpp"

//	LANGUAGE
#include "Language/Lang.hpp"

//	GOOGLE TEST
#include <gtest/gtest.h>

const int level1Correct = 6;
const int level2Correct = 13;

ScopeNodeInterface* globalCurrentScope = nullptr;
FunctionSymTable* globalFunctionSymTable = nullptr;

class Level1 : public ::testing::Test {
	
};

TEST_F(Level1, Correct_All) 
{
    std::string path = "Test/Level_1/Correct/";
    for (int i = 0; i < level1Correct; ++i) {
        std::stringstream filename {};
        filename << path << i + 1 << ".cl";

        std::cerr << filename.str () << std::endl;

        std::ifstream infile { filename.str () };
	    if (!infile) {
	    	*ERRSTREAM << "Error opening file!" << std::endl;
	    	return;
	    }
    
	    yy::LangDriver driver { infile };
	    if (driver.parse ()) {
	    	driver.execute ();
	    }
    }
}

int main (int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	/*
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
	*/
}
