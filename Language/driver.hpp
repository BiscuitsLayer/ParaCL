#pragma once

#include <FlexLexer.h>
#include "../Build/lang.tab.hh"

namespace yy {

    class LangDriver {
        private:
            FlexLexer* lexer_;
        public:
            LangDriver (FlexLexer* lexer);
            parser::token_type yylex (parser::semantic_type* yylval);
            bool parse ();
    };

}