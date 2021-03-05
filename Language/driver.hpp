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
            SyntaxCheck* lexer_ {};
        public:
            //  METHODS
            parser::token_type yylex (parser::semantic_type* yylval, parser::location_type* location);
            bool parse ();
            void execute () {
                ScopeNodeInterface* scope = globalCurrentScope;
                //  Outro to external scope
                globalCurrentScope->Outro ();
                scope->Execute ();
            }

            //  ERROR HANDLING METHODS
            void PrintErrorAndExit (yy::location location, const std::string& message) const;
            std::string GetCurrentString () const { return lexer_->GetCurrentString (); }

            //  CTORS
            LangDriver (std::ifstream& programStream):
                lexer_ (new SyntaxCheck)
                {
                    //  External scope
                    globalCurrentScope = ScopeNodeInterface::CreateScopeNode ();
                    //  The main scope with code
                    ScopeNodeInterface* mainScope = ScopeNodeInterface::CreateScopeNode ();
                    globalCurrentScope->AddBranch (mainScope);
                    globalCurrentScope->Entry (mainScope);
                    globalFunctionSymTable = new FunctionSymTable ();
                    lexer_->switch_streams (programStream, *OUTSTREAM);
                }
            LangDriver (const LangDriver& driver) = delete;

            //  DTOR
            ~LangDriver () {
                delete globalFunctionSymTable;
                delete lexer_;
            }

            //  OPERATORS
            LangDriver& operator = (LangDriver& driver) = delete;
    };

}