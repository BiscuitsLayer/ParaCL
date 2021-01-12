
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
";"                         return yy::parser::token_type::SCOLON;
"("                         return yy::parser::token_type::LPARENTHESES;
")"                         return yy::parser::token_type::RPARENTHESES;
{DOUBLE}                    return yy::parser::token_type::NUMBER;
{VARIABLE}                  return yy::parser::token_type::VARIABLE;
.			                return yy::parser::token_type::ERROR;

%%