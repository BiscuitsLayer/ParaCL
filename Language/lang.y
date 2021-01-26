%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define parse.error custom

%param {LangDriver* driver}
%locations

%code requires
{
	//	SYSTEM
	#include <algorithm>
	#include <string>
	#include <vector>

	//	LANGUAGE
	#include "../Language/Lang.hpp"

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
		parser::token_type yylex (parser::semantic_type* yylval, parser::location_type* location, LangDriver* driver);
	}

	extern ScopeNodeInterface* globalCurrentScope;
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

  QMARK			"?"
  IF			"if"
  WHILE			"while"
  PRINT			"print"
  ERROR
;

%token <NumberType> NUMBER
%token <std::string*> VARIABLE

/* Объявление нетерминалов */
%nterm <NodeInterface*> exprLvl1 exprLvl2 exprLvl3
%nterm <NodeInterface*> assignment
%nterm <NodeInterface*> func_call
%nterm <NodeInterface*> condition
%nterm <NodeInterface*> if_while
%nterm <NodeInterface*> scope
%nterm <NodeInterface*> inside_scope

/* Левоассоциативные и правоассоциативные лексемы */
%left '+' '-'
%left '*' '/'

%start inside_scope

%%

scope:
	scope_entry inside_scope scope_outro			{ $$ = globalCurrentScope; globalCurrentScope->Return (); }
;

scope_entry:
	LBRACE								{ 
											globalCurrentScope->next_ = ScopeNodeInterface::CreateScopeNode (globalCurrentScope, nullptr);
											globalCurrentScope->Entry ();
										}
;

inside_scope:
	inside_scope assignment SCOLON 		{ globalCurrentScope->AddNode ($2); }
|	inside_scope func_call SCOLON 		{ globalCurrentScope->AddNode ($2); }
|	inside_scope if_while				{ globalCurrentScope->AddNode ($2); }
|	inside_scope scope					{ globalCurrentScope->AddNode ($2); }
|										{ /* empty */ }
;

scope_outro:
	RBRACE								{ /* empty */ }
;

if_while:
	IF LPARENTHESES condition RPARENTHESES scope	{ $$ = NodeInterface::CreateIfNode ($3, $5); }
|	WHILE LPARENTHESES condition RPARENTHESES scope	{ $$ = NodeInterface::CreateWhileNode ($3, $5); }
;

condition:
	exprLvl1 GREATER exprLvl1			{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_GREATER, $1, $3); }
|	exprLvl1 GREATER_OR_EQ exprLvl1		{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_GREATER_OR_EQ, $1, $3); }
|	exprLvl1 LESS exprLvl1				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_LESS, $1, $3); }
|	exprLvl1 LESS_OR_EQ exprLvl1		{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_LESS_OR_EQ, $1, $3); }
|	exprLvl1 EQ exprLvl1				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_EQ, $1, $3); }
|	exprLvl1 NOT_EQ exprLvl1			{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_NOT_EQ, $1, $3); }
|	exprLvl1							{ $$ = $1; }
;

assignment:
	VARIABLE ASSIGN exprLvl1	{ 	
									//	ADD VARIABLE
									globalCurrentScope->SetVariable (*($1), 0);

									NodeInterface* left = NodeInterface::CreateVariableNode (*($1));
									delete $1;
								  	$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, $3);
								}
;

func_call:
	PRINT exprLvl1				{ $$ = NodeInterface::CreatePrintNode ($2); }
;

exprLvl1:
	exprLvl2 ADD exprLvl1  	{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ADD, $1, $3); }
| 	exprLvl2 SUB exprLvl1 	{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, $1, $3); }
| 	exprLvl2				{ $$ = $1; }
;

exprLvl2:
	exprLvl3 MUL exprLvl2  	{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_MUL, $1, $3); }
| 	exprLvl3 DIV exprLvl2 	{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_DIV, $1, $3); }
| 	exprLvl3				{ $$ = $1; }
;

exprLvl3:
	LPARENTHESES exprLvl1 RPARENTHESES  { $$ = $2; }
| 	NUMBER				  				{ $$ = NodeInterface::CreateValueNode ($1); }
|	VARIABLE							{ 	
											try {
												globalCurrentScope->GetVariable (*($1));
											}
											catch (std::invalid_argument& ex) {
												driver->PrintErrorAndExit (@1, "Undefined variable!");
											}
											$$ = NodeInterface::CreateVariableNode (*($1));
											delete $1; 
										}
|	QMARK								{ 	$$ = NodeInterface::CreateScanNode ();	}
;

%%

namespace yy {
	parser::token_type yylex (parser::semantic_type* yylval, parser::location_type* location, LangDriver* driver) {
		return driver->yylex (yylval, location);
	}

	void parser::error (const parser::location_type& location, const std::string& what) {
		/* empty */
	}

	void parser::report_syntax_error (parser::context const& context) const {
		driver->PrintErrorAndExit (context.location (), "Syntax error!");
	}
}