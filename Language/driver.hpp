#pragma once

//  SYSTEM
#include <cstring>
#include <fstream>

//	BISON AND FLEX
#include "../Build/lang.tab.hh"
#include "../Language/SyntaxCheck.hpp"

namespace yy {

    class LangDriver {
        private:
            SyntaxCheck* lexer_ {};
        public:
            //  METHODS
            parser::token_type yylex (parser::semantic_type* yylval, parser::location_type* location);
            bool parse ();
            void error (parser::context const& context) const;

            //  CTOR AND DTOR
            LangDriver (std::ifstream& infile);
            ~LangDriver ();
    };

}