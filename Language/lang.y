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
	extern int codePass;
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

%nterm <NodeInterface*> function_assignment_entry
%nterm <NodeInterface*> function_assignment

%nterm <NodeInterface*> return
%nterm <NodeInterface*> syscall
%nterm <NodeInterface*> condition
%nterm <NodeInterface*> if_while

%nterm <ScopeNodeInterface*> scope
%nterm <NodeInterface*> inside_scope
%nterm <NodeInterface*> action

%nterm <ArgumentsListElement*> arg_list
%nterm <ArgumentsListElement*> arg_list_inside
%nterm <ArgumentsListElement*> call_arg_list
%nterm <ArgumentsListElement*> call_arg_list_inside

/* Левоассоциативные и правоассоциативные лексемы */
%left '+' '-'
%left '*' '/'

%start inside_scope

%%

scope:
	scope_entry inside_scope scope_outro				{ $$ = globalCurrentScope; globalCurrentScope->Outro (); }
|	scope_entry inside_scope scope_outro SCOLON			{ $$ = globalCurrentScope; globalCurrentScope->Outro (); }
;

scope_entry:
	LBRACE												{ 
															globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode (globalCurrentScope));
														}
;

inside_scope:
	inside_scope action									{ globalCurrentScope->AddNode ($2); }
|														{ /* empty */ }
;

action:
	assignment 											{ $$ = $1; }
|	function_assignment									{ $$ = $1; }
|	return												{ $$ = $1; }
|	exprLvl1 SCOLON										{ $$ = $1; }
|	syscall 											{ $$ = $1; }
|	if_while											{ $$ = $1; }
|	scope												{ $$ = $1; }
;

scope_outro:
	RBRACE												{ /* empty */ }
;

if_while:
	IF LPARENTHESES condition RPARENTHESES action 		{ 
															ScopeNodeInterface* scope = ScopeNodeInterface::CreateScopeNode (globalCurrentScope);
															globalCurrentScope->Entry (scope);
															globalCurrentScope->AddNode ($5);
															globalCurrentScope->Outro ();
															$$ = NodeInterface::CreateIfNode ($3, scope);
														}
|	WHILE LPARENTHESES condition RPARENTHESES action	{ 
															ScopeNodeInterface* scope = ScopeNodeInterface::CreateScopeNode (globalCurrentScope);
															globalCurrentScope->Entry (scope);
															globalCurrentScope->AddNode ($5);
															globalCurrentScope->Outro ();
															$$ = NodeInterface::CreateWhileNode ($3, scope);
														}
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
	function_assignment_entry inside_scope scope_outro 	{	
															ScopeNodeInterface* scope = globalCurrentScope; globalCurrentScope->Outro ();
															$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_FUNCTION_ASSIGN, $1, scope);
														}
;

function_assignment_entry:
	TEXT ASSIGN FUNC arg_list LBRACE			{
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode (globalCurrentScope));
													globalCurrentScope->Previous ()->SetFunctionVariable (*($1), $4, globalCurrentScope);
													$$ = NodeInterface::CreateFunctionVariableNode (*($1), $4);
													delete $1;
												}
|	TEXT ASSIGN FUNC arg_list COLON	TEXT LBRACE	{ 
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode (globalCurrentScope));
													globalCurrentScope->Previous ()->SetFunctionVariable (*($1), $4, globalCurrentScope, true, *($6));
													$$ = NodeInterface::CreateFunctionVariableNode (*($1), $4);
													delete $1;
													delete $6;
												}
;

arg_list:
	LPARENTHESES arg_list_inside RPARENTHESES	{ $$ = $2; }
|	LPARENTHESES RPARENTHESES					{ /* empty */ }
;

arg_list_inside:
	TEXT 								{ 	
											NodeInterface* temp = NodeInterface::CreateVariableNode (*($1));
											$$ = new ArgumentsListElement (temp, nullptr);
											delete $1;
										}
|	TEXT COMMA arg_list_inside			{ 	
											NodeInterface* temp = NodeInterface::CreateVariableNode (*($1));
											$$ = new ArgumentsListElement (temp, $3);
											delete $1;
										}
;

return:
	RETURN exprLvl1 SCOLON				{ $$ = NodeInterface::CreateReturnNode ($2); }
;

syscall:
	PRINT exprLvl1 SCOLON				{ $$ = NodeInterface::CreatePrintNode ($2); }
;

exprLvl1:
	exprLvl2 ADD exprLvl1  				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ADD, $1, $3); }
| 	exprLvl2 SUB exprLvl1 				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, $1, $3); }
| 	exprLvl2							{ $$ = $1; }
;

exprLvl2:
	exprLvl3 MUL exprLvl2  				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_MUL, $1, $3); }
| 	exprLvl3 DIV exprLvl2 				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_DIV, $1, $3); }
| 	exprLvl3							{ $$ = $1; }
;

exprLvl3:
	LPARENTHESES exprLvl1 RPARENTHESES  { $$ = $2; }
| 	NUMBER				  				{ $$ = NodeInterface::CreateValueNode ($1); }
|	TEXT								{ 	
											try {
												globalCurrentScope->GetVariable (*($1));
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
												globalCurrentScope->GetFunctionVariable (*($1), $2);
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