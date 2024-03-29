#include "driver.hpp"

yy::parser::token_type yy::LangDriver::yylex (yy::parser::semantic_type* yylval, parser::location_type* location) {
    yy::parser::token_type tokenType = static_cast <yy::parser::token_type> (lexer_->yylex ());
    switch (tokenType) {
        case yy::parser::token_type::NUMBER: {
            //  Getting the number itself
            yylval->as <NumberType> () = std::stod (lexer_->YYText ());
            break;
        }
        case yy::parser::token_type::TEXT: {
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
    bool failure = true;
    failure = parser.parse ();
    bool success = !failure&& globalFunctionSymTable->CheckMissingFunctions ();
    return success;
}

void yy::LangDriver::PrintErrorAndExit (yy::location location, const std::string& message) const {
    std::string wholeString {};
    if (location.begin.line == lexer_->lineno () - 1) {
        wholeString = lexer_->GetPreviousString ();
    }
    else {
        wholeString = lexer_->GetCurrentString ();
    }

    std::string trueString = wholeString.substr (0, location.begin.column - 1);
    std::string falseString = wholeString.substr (location.begin.column - 1, location.end.column - location.begin.column);

    *ERRSTREAM << message << std::endl;
    *OUTSTREAM << "Line: " << location.begin.line << ", Columns: " << location.begin.column << " - " << location.end.column << ":" << std::endl;
    *OUTSTREAM << trueString;
    *ERRSTREAM << falseString;
    *OUTSTREAM << " ..." << std::endl;

    exit (ErrorCodes::ERROR_SYNTAX);
}