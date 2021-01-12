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
  ASSIGN		"="
  SCOLON  		";"
  LPARENTHESES	"("
  RPARENTHESES	")"
  LBRACE		"{"
  RBRACE		"}"

  GREATER	  	">"   
  GREATER_OR_EQ	">="  
  LESS  		"<"   
  LESS_OR_EQ  	"<="  
  EQ  			"=="  
  NOT_EQ  		"!="  

  IF			"if"
  WHILE			"while"
  PRINT			"print"
  ERROR
;

%token <double> NUMBER
%token <std::string> VARIABLE
/* Объявление нетерминалов */
%nterm <double> exprLvl1 exprLvl2 exprLvl3

/* Левоассоциативные и правоассоциативные лексемы */
%left '+' '-'
%left '*' '/'

%start inside_scope

%%

scope:
	LBRACE inside_scope RBRACE			{ std::cout << "Scope success" << std::endl; }
;

inside_scope:
	inside_scope assignment SCOLON 		{ std::cout << "AssignInsideScope" << std::endl; }
|	inside_scope syscall SCOLON 		{ std::cout << "SyscallInsideScope" << std::endl; }
|	inside_scope IF LPARENTHESES condition RPARENTHESES scope 		{ std::cout << "If + Scope" << std::endl; }
|	inside_scope WHILE LPARENTHESES condition RPARENTHESES scope 	{ std::cout << "While + Scope" << std::endl; }
|	
;

condition:
	exprLvl1 GREATER exprLvl1			{ std::cout << "Greater" << std::endl; }
|	exprLvl1 GREATER_OR_EQ exprLvl1		{ std::cout << "GreaterOrEq" << std::endl; }
|	exprLvl1 LESS exprLvl1				{ std::cout << "Less" << std::endl; }
|	exprLvl1 LESS_OR_EQ exprLvl1		{ std::cout << "LessOrEq" << std::endl; }
|	exprLvl1 EQ exprLvl1				{ std::cout << "Eq" << std::endl; }
|	exprLvl1 NOT_EQ exprLvl1			{ std::cout << "NotEq" << std::endl; }
;

assignment:
	VARIABLE ASSIGN exprLvl1	{ std::cout << "Assign" << std::endl; }
;

syscall:
	PRINT exprLvl1	{ std::cout << "Print" << std::endl; }
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
|	VARIABLE							{ $$ = 0; }
;

%%

namespace yy {

	parser::token_type yylex (parser::semantic_type* yylval, LangDriver* driver) {
		return driver->yylex (yylval);
	}

	void parser::error (const std::string&) {}

}