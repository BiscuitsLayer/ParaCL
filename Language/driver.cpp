#include "driver.hpp"

extern ScopeNodeInterface* globalCurrentScope;

yy::LangDriver::LangDriver (std::ifstream& infile):
    lexer_ (new SyntaxCheck)
    {
        globalCurrentScope = ScopeNodeInterface::CreateScopeNode (nullptr);
        lexer_->switch_streams (infile, std::cout);
    }

yy::LangDriver::~LangDriver () {
    delete globalCurrentScope;
    delete lexer_;
}

yy::parser::token_type yy::LangDriver::yylex (yy::parser::semantic_type* yylval, parser::location_type* location) {
    yy::parser::token_type tokenType = static_cast <yy::parser::token_type> (lexer_->yylex ());
    switch (tokenType) {
        case yy::parser::token_type::NUMBER: {
            //  Получаем численное значение token-а, если это число
            yylval->as <NumberType> () = std::stod (lexer_->YYText ());
            break;
        }
        case yy::parser::token_type::VARIABLE: {
            //  Я бы хотел использовать тут просто std::string, но после 2х часов дебага 
            //  так и не понял, почему sig segv при присваивании :(
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
        std::cerr << "Compiled successfully!" << std::endl;
        globalCurrentScope->Execute ();
    }
    return !failure;
}

void yy::LangDriver::error (parser::context const& context) const {
    std::string wholeString = lexer_->GetCurrentString (), 
    trueString = wholeString.substr (0, context.location ().begin.column - 1),
    falseString = wholeString.substr (context.location ().begin.column - 1, context.location ().end.column - 1);
    std::cerr << "Syntax error!" << std::endl;
    std::cout << "Line: " << context.location ().begin.line << std::endl;
    std::cout << "Columns: " << context.location ().begin.column << " - " << context.location ().end.column << std::endl;
    std::cout << trueString;
    std::cerr << falseString;
    std::cout << " ..." << std::endl;
    exit (ErrorCodes::ERROR_SYNTAX);
}