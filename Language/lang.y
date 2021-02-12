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
	int codePass = 0;
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

  FUNC			"func"
  RETURN		"return"
  COLON			":"
  COMMA			","
  ERROR
;

%token <NumberType> NUMBER
%token <std::string*> TEXT

/* Объявление нетерминалов */
%nterm <NodeInterface*> exprLvl1 exprLvl2 exprLvl3
%nterm <NodeInterface*> assignment
%nterm <NodeInterface*> function_assignment
%nterm <NodeInterface*> return
%nterm <NodeInterface*> syscall
%nterm <NodeInterface*> condition
%nterm <NodeInterface*> if_while

%nterm <ScopeNodeInterface*> scope
%nterm <NodeInterface*> inside_scope

%nterm <ArgumentsListElement*> arg_list
%nterm <ArgumentsListElement*> arg_list_inside
%nterm <ArgumentsListElement*> call_arg_list
%nterm <ArgumentsListElement*> call_arg_list_inside

/* Левоассоциативные и правоассоциативные лексемы */
%left '+' '-'
%left '*' '/'

%start program

%%

program:
	inside_scope									{ codePass++; }
;

scope:
	scope_entry inside_scope scope_outro			{ $$ = globalCurrentScope; globalCurrentScope->Return (); }
|	scope_entry inside_scope scope_outro SCOLON		{ $$ = globalCurrentScope; globalCurrentScope->Return (); }
;

scope_entry:
	LBRACE											{ 
														globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode (globalCurrentScope));
													}
;

inside_scope:
	inside_scope assignment 						{ globalCurrentScope->AddNode ($2); }
|	inside_scope function_assignment				{ globalCurrentScope->AddNode ($2); }
|	inside_scope return								{ globalCurrentScope->AddNode ($2); }
|	inside_scope exprLvl1 SCOLON					{ globalCurrentScope->AddNode ($2); }
|	inside_scope syscall 							{ globalCurrentScope->AddNode ($2); }
|	inside_scope if_while							{ globalCurrentScope->AddNode ($2); }
|	inside_scope scope								{ globalCurrentScope->AddNode ($2); }
|													{ /* empty */ }
;

scope_outro:
	RBRACE											{ /* empty */ }
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
	TEXT ASSIGN exprLvl1 SCOLON			{ 	
											globalCurrentScope->SetVariable (*($1), 0);
											NodeInterface* left = NodeInterface::CreateVariableNode (*($1));
											delete $1;
								  			$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, $3);
										}
|	TEXT ASSIGN scope					{ 
											globalCurrentScope->SetVariable (*($1), 0);
											NodeInterface* left = NodeInterface::CreateVariableNode (*($1));
											delete $1;
								  			$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, $3);
										}
;

function_assignment:
	TEXT ASSIGN FUNC arg_list scope				{ 
													globalCurrentScope->SetFunctionVariable (*($1), $4, nullptr);
													NodeInterface* left = NodeInterface::CreateFunctionVariableNode (*($1), $4);
													delete $1;
													$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_FUNCTION_ASSIGN, left, $5);
												}
|	TEXT ASSIGN FUNC arg_list COLON	TEXT scope	{ 
													globalCurrentScope->SetFunctionVariable (*($1), $4, nullptr, true, *($6));
													NodeInterface* left = NodeInterface::CreateFunctionVariableNode (*($1), $4);
													delete $1;
													delete $6;
													$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_FUNCTION_ASSIGN, left, $7);
												}
;

arg_list:
	LPARENTHESES arg_list_inside RPARENTHESES		{ $$ = $2; }
|	LPARENTHESES RPARENTHESES						{ /* empty */ }
;

arg_list_inside:
	TEXT 											{ 	
														globalCurrentScope->SetVariable (*($1), 0);
														NodeInterface* temp = NodeInterface::CreateVariableNode (*($1));
														$$ = new ArgumentsListElement (temp, nullptr);
														delete $1;
													}
|	TEXT COMMA arg_list_inside						{ 	
														globalCurrentScope->SetVariable (*($1), 0);
														NodeInterface* temp = NodeInterface::CreateVariableNode (*($1));
														$$ = new ArgumentsListElement (temp, $3);
														delete $1;
													}
;

return:
	RETURN exprLvl1 SCOLON							{ $$ = NodeInterface::CreateReturnNode ($2); }
;

syscall:
	PRINT exprLvl1 SCOLON							{ $$ = NodeInterface::CreatePrintNode ($2); }
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
|	TEXT								{ 	
											try {
												if (codePass != 0) { 
													globalCurrentScope->GetVariable (*($1));
												}
											}
											catch (std::invalid_argument& ex) {
												driver->PrintErrorAndExit (@1, "Undefined variable!");
											}
											$$ = NodeInterface::CreateVariableNode (*($1));
											delete $1; 
										}
|	QMARK								{ $$ = NodeInterface::CreateScanNode (); }
|	TEXT call_arg_list					{ 
											try {
												if (codePass != 0) { 
													globalCurrentScope->GetFunctionVariable (*($1), $2);
												}
											}
											catch (std::invalid_argument& ex) {
												driver->PrintErrorAndExit (@1, "Undefined function variable!");
											}
											$$ = NodeInterface::CreateFunctionVariableNode (*($1), $2);
											delete $1; 
										}
;

call_arg_list:
	LPARENTHESES call_arg_list_inside RPARENTHESES	{ $$ = $2; }
|	LPARENTHESES RPARENTHESES						{ /* empty */ }
;

call_arg_list_inside:
	exprLvl1 										{ $$ = new ArgumentsListElement ($1, nullptr); }
|	exprLvl1 COMMA call_arg_list_inside				{ $$ = new ArgumentsListElement ($1, $3); }
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