#pragma once

//  SYSTEM
#include <cstring>
#include <fstream>

//	BISON AND FLEX
#include "../Build/lang.tab.hh"
#include "../Language/SyntaxCheck.hpp"

extern ScopeNode* globalCurrentScope;
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
                ScopeNode* scope = globalCurrentScope;
                //  Outro to external scope
                globalCurrentScope->Outro ();
                scope->Execute ();
            }

            //  ERROR HANDLING METHODS
            void PrintErrorAndExit (yy::location location, const std::string& message) const;
            std::string GetCurrentString () const { return lexer_->GetCurrentString (); }

            //  CTORS
            LangDriver (std::ifstream& programStream, SyntaxCheck* lexer):
                lexer_ (lexer)
                {   
                    //  External scope
                    globalCurrentScope = CurrentScopeNode::GetInstance ();
                    //?
                    /*
                    //  The main scope with code
                    ScopeNode* mainScope = ScopeNodeInterface::CreateScopeNode ();
                    globalCurrentScope->AddBranch (mainScope);
                    globalCurrentScope->Entry (mainScope);
                    */
                    globalFunctionSymTable = new FunctionSymTable ();
                    lexer_->switch_streams (programStream, *OUTSTREAM);
                }
            LangDriver (const LangDriver& driver) = delete;

            //  DTOR
            ~LangDriver () {
                delete globalCurrentScope;
                delete globalFunctionSymTable;
            }

            //  OPERATORS
            LangDriver& operator = (LangDriver& driver) = delete;
    };

}