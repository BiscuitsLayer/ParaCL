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

class ParaCLTest : public ::testing::Test {
	public:
		void DoTest (int testLevel, int testIdx) {
			std::stringstream path {};
			path << "Test/Level_" << testLevel << "/Correct/";
    	    std::stringstream filename {};
    	    filename << path.str () << testIdx << ".cl";
	
    	    std::ifstream programStream { filename.str () };
		    ASSERT_TRUE (programStream);
	
		    yy::LangDriver driver { programStream };

			bool parserResult = driver.parse ();
			ASSERT_TRUE (parserResult);

			filename.clear ();
			filename.str (std::string {});
			filename << path.str () << testIdx << ".in";

			std::ifstream inputStream { filename.str () };
			ASSERT_TRUE (inputStream);

			filename.clear ();
			filename.str (std::string {});
			filename << path.str () << testIdx << ".out";

			std::ifstream outputStream { filename.str () };
			ASSERT_TRUE (outputStream);

			std::stringstream outputStreamTrue {};
			outputStreamTrue << outputStream.rdbuf ();
			std::stringstream outputStreamGot {};

			INSTREAM = &inputStream;
			OUTSTREAM = &outputStreamGot;
			ERRSTREAM = &outputStreamGot;

			driver.execute ();

			ASSERT_STREQ (outputStreamGot.str ().c_str (), outputStreamTrue.str ().c_str ());
		}
};

TEST_F(ParaCLTest, Correct_1) { DoTest (1, 1); }
TEST_F(ParaCLTest, Correct_2) { DoTest (1, 2); }
TEST_F(ParaCLTest, Correct_3) { DoTest (1, 3); }
TEST_F(ParaCLTest, Correct_4) { DoTest (1, 4); }
TEST_F(ParaCLTest, Correct_5) { DoTest (1, 5); }
TEST_F(ParaCLTest, Correct_6) { DoTest (1, 6); }


int main (int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
