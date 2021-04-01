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
	extern FunctionSymTable* globalFunctionSymTable;
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
  ELSE			"else"
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
%nterm <NodeInterface*> exprLvl1 exprLvl1_no_unary exprLvl2 exprLvl2_no_unary exprLvl3 exprLvl4
%nterm <NodeInterface*> assignment assignment_scope

%nterm <NodeInterface*> function_assignment_entry
%nterm <NodeInterface*> function_assignment

%nterm <NodeInterface*> return
%nterm <NodeInterface*> syscall
%nterm <NodeInterface*> condition
%nterm <NodeInterface*> if
%nterm <NodeInterface*> if_condition
%nterm <NodeInterface*> while
%nterm <NodeInterface*> while_condition

%nterm <ScopeNodeInterface*> scope
%nterm <NodeInterface*> inside_scope_left inside_scope
%nterm <NodeInterface*> action_no_unary action

%nterm <ArgumentsListElement*> arg_list
%nterm <ArgumentsListElement*> arg_list_inside
%nterm <ArgumentsListElement*> call_arg_list
%nterm <ArgumentsListElement*> call_arg_list_inside

/* Левоассоциативные и правоассоциативные лексемы */
%left '+' '-'
%left '*' '/'
%nonassoc "then"
%nonassoc "else"
%left UNARY_MINUS

%start inside_scope

%%

scope:
	scope_entry inside_scope scope_outro				{ $$ = globalCurrentScope; globalCurrentScope->Outro (); }
;

scope_entry:
	LBRACE												{ 
															globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
														}
;

inside_scope:
	inside_scope_left									{ /* empty */ }
|	inside_scope_left assignment_scope					{ globalCurrentScope->AddBranch ($2); }
;

inside_scope_left:
	inside_scope_left action							{ globalCurrentScope->AddBranch ($2); }
/* Next one is special - there must be an action without unary operators after it */
|	inside_scope_left assignment_scope action_no_unary	{ 
															globalCurrentScope->AddBranch ($2);
															globalCurrentScope->AddBranch ($3);
														}
|														{ /* empty */ }
;

action:
	assignment 									{ $$ = $1; }
|	function_assignment							{ $$ = $1; }
|	return										{ $$ = $1; }
|	exprLvl1 SCOLON								{ $$ = $1; }
|	syscall 									{ $$ = $1; }
|	if											{ $$ = $1; }
|	while										{ $$ = $1; }
|	scope 										{ $$ = $1; }
;

action_no_unary:
	assignment 									{ $$ = $1; }
|	function_assignment							{ $$ = $1; }
|	return										{ $$ = $1; }
|	exprLvl1_no_unary SCOLON					{ $$ = $1; }
|	syscall 									{ $$ = $1; }
|	if											{ $$ = $1; }
|	while										{ $$ = $1; }
|	scope										{ $$ = $1; }
;

scope_outro:
	RBRACE										{ /* empty */ }
;

if:
	if_condition action			%prec "then"	{
													globalCurrentScope->AddBranch ($2);
													ScopeNodeInterface* scopeTrue = globalCurrentScope;
													globalCurrentScope->Outro ();
													$$ = NodeInterface::CreateIfNode ($1, scopeTrue, nullptr);
												}
|	if_condition action	ELSE action				{
													globalCurrentScope->AddBranch ($2);
													ScopeNodeInterface* scopeTrue = globalCurrentScope;
													globalCurrentScope->Outro ();
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													globalCurrentScope->AddBranch ($4);
													ScopeNodeInterface* scopeFalse = globalCurrentScope;
													globalCurrentScope->Outro ();
													$$ = NodeInterface::CreateIfNode ($1, scopeTrue, scopeFalse);
												}
;

if_condition:
	IF LPARENTHESES condition RPARENTHESES		{
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													$$ = $3;
												}
;

while:
	while_condition action						{
													globalCurrentScope->AddBranch ($2);
													ScopeNodeInterface* scope = globalCurrentScope;
													globalCurrentScope->Outro ();
													$$ = NodeInterface::CreateWhileNode ($1, scope);
												}
;

while_condition:
	WHILE LPARENTHESES condition RPARENTHESES	{
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													$$ = $3;
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
											globalCurrentScope->SetVariableValue (*($1), 0);
											NodeInterface* left = NodeInterface::CreateVariableNode (*($1));
											delete $1;
								  			$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, $3);
										}
;

assignment_scope:
	TEXT ASSIGN scope 					{ 
											globalCurrentScope->SetVariableValue (*($1), 0);
											NodeInterface* left = NodeInterface::CreateVariableNode (*($1));
											delete $1;
								  			$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, $3);
										}
;

function_assignment:
	function_assignment_entry inside_scope scope_outro 			{	
																	ScopeNode* scope = globalCurrentScope; globalCurrentScope->Outro ();
																	$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_FUNCTION_ASSIGN, $1, scope);
																}
|	function_assignment_entry inside_scope scope_outro SCOLON	{	
																	ScopeNode* scope = globalCurrentScope; globalCurrentScope->Outro ();
																	$$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_FUNCTION_ASSIGN, $1, scope);
																}
;

function_assignment_entry:
	TEXT ASSIGN FUNC arg_list LBRACE			{
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													globalCurrentScope->Previous ()->SetFunctionVariableScope (*($1), $4, globalCurrentScope);
													$$ = NodeInterface::CreateFunctionVariableNode (*($1), $4);
													delete $1;
												}
|	TEXT ASSIGN FUNC arg_list COLON	TEXT LBRACE	{ 
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													globalCurrentScope->Previous ()->SetFunctionVariableScope (*($1), $4, globalCurrentScope, true, *($6));
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
	RETURN exprLvl1 SCOLON				{ $$ = NodeInterface::CreateReturnNode (static_cast <ScopeNode*> (globalCurrentScope), $2); }
;

syscall:
	PRINT exprLvl1 SCOLON				{ $$ = NodeInterface::CreatePrintNode ($2); }
;

exprLvl1:
	exprLvl2 ADD exprLvl1  				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ADD, $1, $3); }
| 	exprLvl2 SUB exprLvl1 				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, $1, $3); }
| 	exprLvl2							{ $$ = $1; }
;

exprLvl1_no_unary:
	exprLvl2_no_unary ADD exprLvl1  	{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ADD, $1, $3); }
| 	exprLvl2_no_unary SUB exprLvl1 		{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, $1, $3); }
| 	exprLvl2_no_unary					{ $$ = $1; }
;

exprLvl2:
	exprLvl3 MUL exprLvl2  				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_MUL, $1, $3); }
| 	exprLvl3 DIV exprLvl2 				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_DIV, $1, $3); }
| 	exprLvl3							{ $$ = $1; }
;

exprLvl2_no_unary:
	exprLvl4 MUL exprLvl2  				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_MUL, $1, $3); }
| 	exprLvl4 DIV exprLvl2 				{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_DIV, $1, $3); }
| 	exprLvl4							{ $$ = $1; }
;

exprLvl3:
	SUB exprLvl4						{ $$ = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, NodeInterface::CreateValueNode (0), $2); }
|	ADD exprLvl4						{ $$ = $2; }
|	exprLvl4							{ $$ = $1; }
;

exprLvl4:
	LPARENTHESES exprLvl1 RPARENTHESES  { $$ = $2; }
| 	NUMBER				  				{ $$ = NodeInterface::CreateValueNode ($1); }
|	TEXT								{ 	
											try {
												globalCurrentScope->GetVariableValue (*($1));
											}
											catch (std::invalid_argument& ex) {
												driver->PrintErrorAndExit (@1, "Undefined variable!");
											}
											$$ = NodeInterface::CreateVariableNode (*($1));
											delete $1; 
										}
|	QMARK								{ $$ = NodeInterface::CreateScanNode (); }
|	TEXT call_arg_list					{ 
											
											if (!globalCurrentScope->GetFunctionVariableScope (*($1), $2)) {
												globalFunctionSymTable->AddMissingFunction (*($1), $2);
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
|	scope 											{ $$ = new ArgumentsListElement ($1, nullptr); }
|	scope COMMA call_arg_list_inside				{ $$ = new ArgumentsListElement ($1, $3); }
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