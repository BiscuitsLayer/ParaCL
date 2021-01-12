
%option c++
/* TODO */
%option noyywrap

%{

#include "../Build/lang.tab.hh"

%}

WS              [ \t\n\v]+
DIGIT           [0-9]
DIGIT_NON_ZERO  [1-9]

%%
                  /* Сопоставляем каждой лексеме её константу для парсера */
{WS}              /* skip blanks and tabs */
"+"               return yy::parser::token_type::PLUS;
"-"               return yy::parser::token_type::MINUS;
{DIGIT1}{DIGIT}*  return yy::parser::token_type::NUMBER;
.			      return yy::parser::token_type::ERROR;

%%