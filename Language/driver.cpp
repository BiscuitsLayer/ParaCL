#include "driver.hpp"

extern ScopeNodeInterface* globalCurrentScope;

yy::LangDriver::LangDriver (std::ifstream& infile):
    lexer_ (new SyntaxCheck)
    {
        globalCurrentScope = ScopeNodeInterface::CreateScopeNode (nullptr);
        lexer_->switch_streams (infile, OUTSTREAM);
    }

yy::LangDriver::~LangDriver () {
    delete globalCurrentScope;
    delete lexer_;
}

yy::parser::token_type yy::LangDriver::yylex (yy::parser::semantic_type* yylval, parser::location_type* location) {
    yy::parser::token_type tokenType = static_cast <yy::parser::token_type> (lexer_->yylex ());
    switch (tokenType) {
        case yy::parser::token_type::NUMBER: {
            //  Getting the number itself
            yylval->as <NumberType> () = std::stod (lexer_->YYText ());
            break;
        }
        case yy::parser::token_type::VARIABLE: {
            //  I would really like to use std::string there, but after debugging for 2 hours
            //  I still failed with sig segv in the assignment :(
            std::string* temp = new std::string (lexer_->YYText ());
            yylval->as <std::string*> () = temp;
            break;
        }
        default: {
            break;
        }
    }
    *location = lexer_->GetLocation ();
    return tokenType;
}

bool yy::LangDriver::parse () {
    yy::parser parser (this);
    bool failure = parser.parse ();   
    if (!failure) {
        OUTSTREAM << "Compiled successfully!" << std::endl;
        globalCurrentScope->Execute ();
    }
    return !failure;
}

void yy::LangDriver::PrintErrorAndExit (yy::location location, const std::string& message) const {
    std::string wholeString = lexer_->GetCurrentString (), 
    trueString = wholeString.substr (0, location.begin.column - 1),
    falseString = wholeString.substr (location.begin.column - 1, location.end.column - 1);
    
    ERRSTREAM << message << std::endl;
    OUTSTREAM << "Line: " << location.begin.line << ", Columns: " << location.begin.column << " - " << location.end.column << ":" << std::endl;
    OUTSTREAM << trueString;
    ERRSTREAM << falseString;
    OUTSTREAM << " ..." << std::endl;

    exit (ErrorCodes::ERROR_SYNTAX);
}
std::string yy::LangDriver::GetCurrentString () const {
    return lexer_->GetCurrentString ();
}