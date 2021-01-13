#include "driver.hpp"

yy::LangDriver::LangDriver (FlexLexer* lexer):
    lexer_ (lexer)
    {}

yy::parser::token_type yy::LangDriver::yylex (yy::parser::semantic_type* yylval) {
    yy::parser::token_type tokenType = static_cast <yy::parser::token_type> (lexer_->yylex ());
    switch (tokenType) {
        case yy::parser::token_type::NUMBER: {
            //  Получаем численное значение token-а, если это число
            yylval->as <double> () = std::stod (lexer_->YYText ());
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
    return tokenType;
}

bool yy::LangDriver::parse () {
    yy::parser parser (this);
    bool result = parser.parse ();
    return !result;
}