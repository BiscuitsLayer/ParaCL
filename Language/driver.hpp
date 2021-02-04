#pragma once

//  SYSTEM
#include <cstring>
#include <fstream>

//	BISON AND FLEX
#include "../Build/lang.tab.hh"
#include "../Language/SyntaxCheck.hpp"

extern ScopeNodeInterface* globalCurrentScope;

namespace yy {

    class LangDriver {
        private:
            //  LEXER
            SyntaxCheck* lexer_ {};
        public:
            //  METHODS
            parser::token_type yylex (parser::semantic_type* yylval, parser::location_type* location);
            bool parse ();
            void execute () { globalCurrentScope->Execute (); }

            //  ERROR HANDLING METHODS
            void PrintErrorAndExit (yy::location location, const std::string& message) const;
            std::string GetCurrentString () const { return lexer_->GetCurrentString (); }

            //  CTOR
            LangDriver (std::ifstream& infile):
                lexer_ (new SyntaxCheck)
                {
                    globalCurrentScope = ScopeNodeInterface::CreateScopeNode (nullptr);
                    lexer_->switch_streams (infile, OUTSTREAM);
                }

            //  DTOR
            ~LangDriver () {
                delete globalCurrentScope;
                delete lexer_;
            }
    };

}