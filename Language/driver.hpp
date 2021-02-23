#pragma once

//  SYSTEM
#include <cstring>
#include <fstream>

//	BISON AND FLEX
#include "../Build/lang.tab.hh"
#include "../Language/SyntaxCheck.hpp"

extern ScopeNodeInterface* globalCurrentScope;
extern FunctionSymTable* globalFunctionSymTable;

namespace yy {

    class LangDriver {
        private:
            //  LEXER
            SyntaxCheck* lexer_ {};
            ScopeNodeInterface* executableScope_ = nullptr;
        public:
            //  METHODS
            parser::token_type yylex (parser::semantic_type* yylval, parser::location_type* location);
            bool parse ();
            void execute () {
                executableScope_ = ScopeNodeInterface::CreateScopeNode ();
                executableScope_->AddNode (globalCurrentScope);
                executableScope_->Execute ();
            }

            //  ERROR HANDLING METHODS
            void PrintErrorAndExit (yy::location location, const std::string& message) const;
            std::string GetCurrentString () const { return lexer_->GetCurrentString (); }

            //  CTOR
            LangDriver (std::ifstream& infile):
                lexer_ (new SyntaxCheck),
                executableScope_ (nullptr)
                {
                    globalCurrentScope = ScopeNodeInterface::CreateScopeNode ();
                    globalFunctionSymTable = new FunctionSymTable ();
                    lexer_->switch_streams (infile, OUTSTREAM);
                }

            //  DTOR
            ~LangDriver () {
                delete globalFunctionSymTable;
                delete executableScope_;
                delete lexer_;
            }
    };

}