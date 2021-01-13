
%option c++
/* TODO */
%option noyywrap

%{

#include "../Build/lang.tab.hh"

%}

WS              [ \t\n\v]+
DOT             [.]
DIGIT           [0-9]
DIGIT_NON_ZERO  [1-9]
DOUBLE          {DIGIT}+{DOT}?{DIGIT}*
INTEGER         {DIGIT_NON_ZERO}{DIGIT}*
LETTER          [a-zA-Z_]
LETTER_OR_DIGIT [a-zA-Z0-9_]
VARIABLE        {LETTER}{LETTER_OR_DIGIT}*

%%
                            /* Сопоставляем каждой лексеме её константу для парсера */
{WS}                        /* skip blanks and tabs */
"+"                         return yy::parser::token_type::ADD;
"-"                         return yy::parser::token_type::SUB;
"*"                         return yy::parser::token_type::MUL;
"/"                         return yy::parser::token_type::DIV;
"="                         return yy::parser::token_type::ASSIGN;
";"                         return yy::parser::token_type::SCOLON;
"("                         return yy::parser::token_type::LPARENTHESES;
")"                         return yy::parser::token_type::RPARENTHESES;
"{"                         return yy::parser::token_type::LBRACE;
"}"                         return yy::parser::token_type::RBRACE;

">"                         return yy::parser::token_type::GREATER;
">="                        return yy::parser::token_type::GREATER_OR_EQ;
"<"                         return yy::parser::token_type::LESS;
"<="                        return yy::parser::token_type::LESS_OR_EQ;
"=="                        return yy::parser::token_type::EQ;
"!="                        return yy::parser::token_type::NOT_EQ;

"?"                         return yy::parser::token_type::QMARK;
"if"                        return yy::parser::token_type::IF;
"while"                     return yy::parser::token_type::WHILE;
"print"                     return yy::parser::token_type::PRINT;
{DOUBLE}                    return yy::parser::token_type::NUMBER;
{VARIABLE}                  return yy::parser::token_type::VARIABLE;
.			                return yy::parser::token_type::ERROR;

%%