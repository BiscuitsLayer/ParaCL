%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {LangDriver* driver}

%code requires
{

	#include <algorithm>
	#include <string>
	#include <vector>

	// forward declaration of argument to parser
	namespace yy { class LangDriver; }

}

%code
{

	#include "../Language/lang.hpp"

	namespace yy {

		parser::token_type yylex (parser::semantic_type* yylval, LangDriver* driver);

	}

}

%token
/* Список токенов */
  MINUS   "-"
  PLUS    "+"
  SCOLON  ";"
  ERROR
;

%token <int> NUMBER
/* Объявление нетерминалов */
%nterm <std::vector<int>> expr
%nterm <std::vector<std::vector<int>>> equals
%nterm <std::vector<std::vector<std::vector<int>>>> eqlist

/* Левоассоциативные и правоассоциативные лексемы */
%left '+' '-'

%start program

%%

program: eqlist               { driver->insert($1); }
;

eqlist: equals SCOLON eqlist  { $$ = $3; $$.push_back($1); }
| equals SCOLON               { $$.push_back($1);          }
;

equals: expr EQUAL expr       { $$.push_back($1); $$.push_back($3); }
;

expr: NUMBER                  { $$.push_back($1); }
| expr PLUS expr              { 
                                $$ = $1;
                                $$.insert($$.end(), $3.begin(), $3.end());
                              }
| expr MINUS expr             { 
                                $$ = $1; 
                                std::transform($3.begin(), $3.end(), $3.begin(),
                                               [](auto x) { return -x; });
                                $$.insert($$.end(), $3.begin(), $3.end());
                              }
;

%%

namespace yy {

	parser::token_type yylex (parser::semantic_type* yylval, LangDriver* driver) {
		return driver->yylex (yylval);
	}

	void parser::error (const std::string&) {}

}