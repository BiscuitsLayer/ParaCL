#pragma once

#include <FlexLexer.h>
#include "../Build/lang.tab.hh"

namespace yy {

    class LangDriver {
        private:
            FlexLexer* lexer_;
        public:
            LangDriver (FlexLexer* lexer):
                lexer_ (lexer)
                {}
            parser::token_type yylex (parser::semantic_type* yylval) {
                parser::token_type tokenType = static_cast <parser::token_type> (lexer_->yylex ());
                //  Здесь switch для разные типов token-ов
                if (tokenType == yy::parser::token_type::NUMBER) {
                    //  Получаем численное значение token-а, если это число
                    yylval->as <int> () = std::stoi (lexer_->YYText ());
                }
                return tokenType;
            }
            bool parse () {
                parser parser (this);
                bool result = parser.parse ();
                return !result;
            }
            void insert (std::vector<std::vector<std::vector<int>>> v) {

            }
    };

}