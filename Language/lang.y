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
	//	BISON AND FLEX
	#include "../Language/driver.hpp"

	//	LANGUAGE
	#include "../Language/Lang.hpp"

	namespace yy {

		parser::token_type yylex (parser::semantic_type* yylval, LangDriver* driver);

	}

	extern Scope* globalCurrentScope;

}

%token
/* Список токенов */
  ADD 			"+"
  SUB			"-"
  MUL			"*"
  DIV			"/"
  SCOLON  		";"
  LPARENTHESES	"("
  RPARENTHESES	")"
  ERROR
;

%token <double> NUMBER
%token <double> VARIABLE
/* Объявление нетерминалов */
%nterm <double> exprLvl1 exprLvl2 exprLvl3

/* Левоассоциативные и правоассоциативные лексемы */
%left '+' '-'
%left '*' '/'

%start program

%%

program: 
	program exprLvl1 SCOLON	{ std::cout << "expression found: " << $2 << std::endl; globalCurrentScope->Dump (); }
|
;

exprLvl1:
	exprLvl2 ADD exprLvl1  	{ $$ = $1 + $3; std::cout << "ADD: " << $$ << std::endl; }
| 	exprLvl2 SUB exprLvl1 	{ $$ = $1 - $3; std::cout << "SUB: " << $$ << std::endl; }
| 	exprLvl2				{ $$ = $1; }
;

exprLvl2:
	exprLvl3 MUL exprLvl2  	{ $$ = $1 * $3; std::cout << "MUL: " << $$ << std::endl; }
| 	exprLvl3 DIV exprLvl2 	{ $$ = $1 / $3; std::cout << "DIV: " << $$ << std::endl; }
| 	exprLvl3				{ $$ = $1; }
;

exprLvl3:
	LPARENTHESES exprLvl1 RPARENTHESES  { $$ = $2; std::cout << "PARENTHESES: " << $$ << std::endl; }
| 	NUMBER				  				{ $$ = $1; }
|	VARIABLE							{ $$ = $1; }
;

%%

namespace yy {

	parser::token_type yylex (parser::semantic_type* yylval, LangDriver* driver) {
		return driver->yylex (yylval);
	}

	void parser::error (const std::string&) {}

}