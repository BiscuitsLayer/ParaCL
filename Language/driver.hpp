#pragma once

//  SYSTEM
#include <cstring>
#include <fstream>

//	BISON AND FLEX
#include <FlexLexer.h>
#include "../Build/lang.tab.hh"

namespace yy {

    class LangDriver {
        private:
            FlexLexer* lexer_;
        public:
            //  METHODS
            parser::token_type yylex (parser::semantic_type* yylval);
            bool parse ();

            //  CTOR AND DTOR
            LangDriver (std::ifstream& infile);
            ~LangDriver ();
    };

}