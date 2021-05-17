//	SYSTEM
#include <fstream>

//	BISON AND FLEX
#include <FlexLexer.h>
#include "Language/driver.hpp"

//	LANGUAGE
#include "Language/Lang.hpp"

//	GOOGLE TEST
#include <gtest/gtest.h>

ScopeNodeInterface* globalCurrentScope = nullptr;
FunctionSymTable* globalFunctionSymTable = nullptr;

class ParaCLTest : public ::testing::Test {
	public:
		virtual int GetLevel () = 0;
		void DoTest (int testIdx) {
			std::stringstream path {};
			path << "Test/Level_" << GetLevel () << "/Correct/";
    	    std::stringstream filename {};
    	    filename << path.str () << testIdx << ".cl";
	
    	    std::ifstream programStream { filename.str () };
		    ASSERT_TRUE (programStream) << "Error opening file: " << filename.str ();
	
		    yy::LangDriver driver { programStream };
			bool parserResult = driver.parse ();
			ASSERT_TRUE (parserResult) << "Parser failed";

			filename.clear ();
			filename.str (std::string {});
			filename << path.str () << testIdx << ".in";

			std::ifstream inputStream { filename.str () };
			ASSERT_TRUE (inputStream) << "Error opening file: " << filename.str ();

			filename.clear ();
			filename.str (std::string {});
			filename << path.str () << testIdx << ".out";

			std::ifstream outputStream { filename.str () };
			ASSERT_TRUE (outputStream) << "Error opening file: " << filename.str ();
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

class Level_1 : public ParaCLTest { virtual int GetLevel () override { return 1; } };
class Level_2 : public ParaCLTest { virtual int GetLevel () override { return 2; } };

TEST_F (Level_1, Correct_1)  { DoTest (1);  }
TEST_F (Level_1, Correct_2)  { DoTest (2);  }
TEST_F (Level_1, Correct_3)  { DoTest (3);  }
TEST_F (Level_1, Correct_4)  { DoTest (4);  }
TEST_F (Level_1, Correct_5)  { DoTest (5);  }
TEST_F (Level_1, Correct_6)  { DoTest (6);  }

TEST_F (Level_2, Correct_1)  { DoTest (1);  }
TEST_F (Level_2, Correct_2)  { DoTest (2);  }
TEST_F (Level_2, Correct_3)  { DoTest (3);  }
TEST_F (Level_2, Correct_4)  { DoTest (4);  }
TEST_F (Level_2, Correct_5)  { DoTest (5);  }
TEST_F (Level_2, Correct_6)  { DoTest (6);  }
TEST_F (Level_2, Correct_7)  { DoTest (7);  }
TEST_F (Level_2, Correct_8)  { DoTest (8);  }
TEST_F (Level_2, Correct_9)  { DoTest (9);  }
TEST_F (Level_2, Correct_10) { DoTest (10); }
TEST_F (Level_2, Correct_11) { DoTest (11); }
TEST_F (Level_2, Correct_12) { DoTest (12); }
TEST_F (Level_2, Correct_13) { DoTest (13); }


int main (int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
