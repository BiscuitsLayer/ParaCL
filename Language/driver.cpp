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
            // TODO
            yylval->as <double> () = 0;
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