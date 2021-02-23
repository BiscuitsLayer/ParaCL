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
        public:
            //  METHODS
            parser::token_type yylex (parser::semantic_type* yylval, parser::location_type* location);
            bool parse ();
            void execute () {
                ScopeNodeInterface* scope = globalCurrentScope;
                //  Outro to external scope
                globalCurrentScope->Outro ();
                try {
                    scope->Execute ();
                }
                catch (ReturnPerformer &performer) {}
            }

            //  ERROR HANDLING METHODS
            void PrintErrorAndExit (yy::location location, const std::string& message) const;
            std::string GetCurrentString () const { return lexer_->GetCurrentString (); }

            //  CTOR
            LangDriver (std::ifstream& infile):
                lexer_ (new SyntaxCheck)
                {
                    //  External scope
                    globalCurrentScope = ScopeNodeInterface::CreateScopeNode ();
                    //  The main scope with code
                    ScopeNodeInterface* mainScope = ScopeNodeInterface::CreateScopeNode ();
                    globalCurrentScope->AddNode (mainScope);
                    globalCurrentScope->Entry (mainScope);
                    globalFunctionSymTable = new FunctionSymTable ();
                    lexer_->switch_streams (infile, OUTSTREAM);
                }

            //  DTOR
            ~LangDriver () {
                delete globalFunctionSymTable;
                delete lexer_;
            }
    };

}