// A Bison parser, made by GNU Bison 3.7.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "lang.tab.hh"


// Unqualified %code blocks.
#line 26 "Language/lang.y"

	//	BISON AND FLEX
	#include "../Language/driver.hpp"

	//	LANGUAGE
	#include "../Language/Lang.hpp"

	namespace yy {
		parser::token_type yylex (parser::semantic_type* yylval, parser::location_type* location, LangDriver* driver);
	}

	extern ScopeNodeInterface* globalCurrentScope;
	extern FunctionSymTable* globalFunctionSymTable;

#line 61 "Build/lang.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 153 "Build/lang.tab.cc"

  /// Build a parser object.
  parser::parser (LangDriver* driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg_list_inside: // arg_list_inside
      case symbol_kind::S_call_arg_list: // call_arg_list
      case symbol_kind::S_call_arg_list_inside: // call_arg_list_inside
        value.copy< ArgumentsListElement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_inside_scope: // inside_scope
      case symbol_kind::S_inside_scope_left: // inside_scope_left
      case symbol_kind::S_action: // action
      case symbol_kind::S_action_no_unary: // action_no_unary
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_assignment_scope: // assignment_scope
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl1_no_unary: // exprLvl1_no_unary
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl2_no_unary: // exprLvl2_no_unary
      case symbol_kind::S_exprLvl3: // exprLvl3
      case symbol_kind::S_exprLvl4: // exprLvl4
        value.copy< NodeInterface* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.copy< NumberType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scope: // scope
        value.copy< ScopeNodeInterface* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TEXT: // TEXT
        value.copy< std::string* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg_list_inside: // arg_list_inside
      case symbol_kind::S_call_arg_list: // call_arg_list
      case symbol_kind::S_call_arg_list_inside: // call_arg_list_inside
        value.move< ArgumentsListElement* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_inside_scope: // inside_scope
      case symbol_kind::S_inside_scope_left: // inside_scope_left
      case symbol_kind::S_action: // action
      case symbol_kind::S_action_no_unary: // action_no_unary
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_assignment_scope: // assignment_scope
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl1_no_unary: // exprLvl1_no_unary
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl2_no_unary: // exprLvl2_no_unary
      case symbol_kind::S_exprLvl3: // exprLvl3
      case symbol_kind::S_exprLvl4: // exprLvl4
        value.move< NodeInterface* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< NumberType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_scope: // scope
        value.move< ScopeNodeInterface* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TEXT: // TEXT
        value.move< std::string* > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg_list_inside: // arg_list_inside
      case symbol_kind::S_call_arg_list: // call_arg_list
      case symbol_kind::S_call_arg_list_inside: // call_arg_list_inside
        value.YY_MOVE_OR_COPY< ArgumentsListElement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_inside_scope: // inside_scope
      case symbol_kind::S_inside_scope_left: // inside_scope_left
      case symbol_kind::S_action: // action
      case symbol_kind::S_action_no_unary: // action_no_unary
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_assignment_scope: // assignment_scope
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl1_no_unary: // exprLvl1_no_unary
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl2_no_unary: // exprLvl2_no_unary
      case symbol_kind::S_exprLvl3: // exprLvl3
      case symbol_kind::S_exprLvl4: // exprLvl4
        value.YY_MOVE_OR_COPY< NodeInterface* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.YY_MOVE_OR_COPY< NumberType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scope: // scope
        value.YY_MOVE_OR_COPY< ScopeNodeInterface* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TEXT: // TEXT
        value.YY_MOVE_OR_COPY< std::string* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg_list_inside: // arg_list_inside
      case symbol_kind::S_call_arg_list: // call_arg_list
      case symbol_kind::S_call_arg_list_inside: // call_arg_list_inside
        value.move< ArgumentsListElement* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_inside_scope: // inside_scope
      case symbol_kind::S_inside_scope_left: // inside_scope_left
      case symbol_kind::S_action: // action
      case symbol_kind::S_action_no_unary: // action_no_unary
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_assignment_scope: // assignment_scope
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl1_no_unary: // exprLvl1_no_unary
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl2_no_unary: // exprLvl2_no_unary
      case symbol_kind::S_exprLvl3: // exprLvl3
      case symbol_kind::S_exprLvl4: // exprLvl4
        value.move< NodeInterface* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< NumberType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_scope: // scope
        value.move< ScopeNodeInterface* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TEXT: // TEXT
        value.move< std::string* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg_list_inside: // arg_list_inside
      case symbol_kind::S_call_arg_list: // call_arg_list
      case symbol_kind::S_call_arg_list_inside: // call_arg_list_inside
        value.copy< ArgumentsListElement* > (that.value);
        break;

      case symbol_kind::S_inside_scope: // inside_scope
      case symbol_kind::S_inside_scope_left: // inside_scope_left
      case symbol_kind::S_action: // action
      case symbol_kind::S_action_no_unary: // action_no_unary
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_assignment_scope: // assignment_scope
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl1_no_unary: // exprLvl1_no_unary
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl2_no_unary: // exprLvl2_no_unary
      case symbol_kind::S_exprLvl3: // exprLvl3
      case symbol_kind::S_exprLvl4: // exprLvl4
        value.copy< NodeInterface* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.copy< NumberType > (that.value);
        break;

      case symbol_kind::S_scope: // scope
        value.copy< ScopeNodeInterface* > (that.value);
        break;

      case symbol_kind::S_TEXT: // TEXT
        value.copy< std::string* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg_list_inside: // arg_list_inside
      case symbol_kind::S_call_arg_list: // call_arg_list
      case symbol_kind::S_call_arg_list_inside: // call_arg_list_inside
        value.move< ArgumentsListElement* > (that.value);
        break;

      case symbol_kind::S_inside_scope: // inside_scope
      case symbol_kind::S_inside_scope_left: // inside_scope_left
      case symbol_kind::S_action: // action
      case symbol_kind::S_action_no_unary: // action_no_unary
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_assignment_scope: // assignment_scope
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl1_no_unary: // exprLvl1_no_unary
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl2_no_unary: // exprLvl2_no_unary
      case symbol_kind::S_exprLvl3: // exprLvl3
      case symbol_kind::S_exprLvl4: // exprLvl4
        value.move< NodeInterface* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< NumberType > (that.value);
        break;

      case symbol_kind::S_scope: // scope
        value.move< ScopeNodeInterface* > (that.value);
        break;

      case symbol_kind::S_TEXT: // TEXT
        value.move< std::string* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_arg_list: // arg_list
      case symbol_kind::S_arg_list_inside: // arg_list_inside
      case symbol_kind::S_call_arg_list: // call_arg_list
      case symbol_kind::S_call_arg_list_inside: // call_arg_list_inside
        yylhs.value.emplace< ArgumentsListElement* > ();
        break;

      case symbol_kind::S_inside_scope: // inside_scope
      case symbol_kind::S_inside_scope_left: // inside_scope_left
      case symbol_kind::S_action: // action
      case symbol_kind::S_action_no_unary: // action_no_unary
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_assignment_scope: // assignment_scope
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl1_no_unary: // exprLvl1_no_unary
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl2_no_unary: // exprLvl2_no_unary
      case symbol_kind::S_exprLvl3: // exprLvl3
      case symbol_kind::S_exprLvl4: // exprLvl4
        yylhs.value.emplace< NodeInterface* > ();
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        yylhs.value.emplace< NumberType > ();
        break;

      case symbol_kind::S_scope: // scope
        yylhs.value.emplace< ScopeNodeInterface* > ();
        break;

      case symbol_kind::S_TEXT: // TEXT
        yylhs.value.emplace< std::string* > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // scope: scope_entry inside_scope scope_outro
#line 113 "Language/lang.y"
                                                                        { yylhs.value.as < ScopeNodeInterface* > () = globalCurrentScope; globalCurrentScope->Outro (); }
#line 937 "Build/lang.tab.cc"
    break;

  case 3: // scope_entry: "{"
#line 117 "Language/lang.y"
                                                                                                        { 
															globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
														}
#line 945 "Build/lang.tab.cc"
    break;

  case 4: // inside_scope: inside_scope_left
#line 123 "Language/lang.y"
                                                                                                { /* empty */ }
#line 951 "Build/lang.tab.cc"
    break;

  case 5: // inside_scope: inside_scope_left assignment_scope
#line 124 "Language/lang.y"
                                                                                { globalCurrentScope->AddBranch (yystack_[0].value.as < NodeInterface* > ()); }
#line 957 "Build/lang.tab.cc"
    break;

  case 6: // inside_scope_left: inside_scope_left action
#line 128 "Language/lang.y"
                                                                                        { globalCurrentScope->AddBranch (yystack_[0].value.as < NodeInterface* > ()); }
#line 963 "Build/lang.tab.cc"
    break;

  case 7: // inside_scope_left: inside_scope_left assignment_scope action_no_unary
#line 130 "Language/lang.y"
                                                                { 
															globalCurrentScope->AddBranch (yystack_[1].value.as < NodeInterface* > ());
															globalCurrentScope->AddBranch (yystack_[0].value.as < NodeInterface* > ());
														}
#line 972 "Build/lang.tab.cc"
    break;

  case 8: // inside_scope_left: %empty
#line 134 "Language/lang.y"
                                                                                                                { /* empty */ }
#line 978 "Build/lang.tab.cc"
    break;

  case 9: // action: assignment
#line 138 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 984 "Build/lang.tab.cc"
    break;

  case 10: // action: function_assignment
#line 139 "Language/lang.y"
                                                                                { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 990 "Build/lang.tab.cc"
    break;

  case 11: // action: return
#line 140 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 996 "Build/lang.tab.cc"
    break;

  case 12: // action: exprLvl1 ";"
#line 141 "Language/lang.y"
                                                                                { yylhs.value.as < NodeInterface* > () = yystack_[1].value.as < NodeInterface* > (); }
#line 1002 "Build/lang.tab.cc"
    break;

  case 13: // action: syscall
#line 142 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1008 "Build/lang.tab.cc"
    break;

  case 14: // action: if
#line 143 "Language/lang.y"
                                                                                                { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1014 "Build/lang.tab.cc"
    break;

  case 15: // action: while
#line 144 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1020 "Build/lang.tab.cc"
    break;

  case 16: // action: scope
#line 145 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < ScopeNodeInterface* > (); }
#line 1026 "Build/lang.tab.cc"
    break;

  case 17: // action_no_unary: assignment
#line 149 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1032 "Build/lang.tab.cc"
    break;

  case 18: // action_no_unary: function_assignment
#line 150 "Language/lang.y"
                                                                                { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1038 "Build/lang.tab.cc"
    break;

  case 19: // action_no_unary: return
#line 151 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1044 "Build/lang.tab.cc"
    break;

  case 20: // action_no_unary: exprLvl1_no_unary ";"
#line 152 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[1].value.as < NodeInterface* > (); }
#line 1050 "Build/lang.tab.cc"
    break;

  case 21: // action_no_unary: syscall
#line 153 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1056 "Build/lang.tab.cc"
    break;

  case 22: // action_no_unary: if
#line 154 "Language/lang.y"
                                                                                                { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1062 "Build/lang.tab.cc"
    break;

  case 23: // action_no_unary: while
#line 155 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1068 "Build/lang.tab.cc"
    break;

  case 24: // action_no_unary: scope
#line 156 "Language/lang.y"
                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < ScopeNodeInterface* > (); }
#line 1074 "Build/lang.tab.cc"
    break;

  case 25: // scope_outro: "}"
#line 160 "Language/lang.y"
                                                                                        { /* empty */ }
#line 1080 "Build/lang.tab.cc"
    break;

  case 26: // if: if_condition action
#line 164 "Language/lang.y"
                                                                {
													globalCurrentScope->AddBranch (yystack_[0].value.as < NodeInterface* > ());
													ScopeNodeInterface* scopeTrue = globalCurrentScope;
													globalCurrentScope->Outro ();
													yylhs.value.as < NodeInterface* > () = NodeInterface::CreateIfNode (yystack_[1].value.as < NodeInterface* > (), scopeTrue, nullptr);
												}
#line 1091 "Build/lang.tab.cc"
    break;

  case 27: // if: if_condition action "else" action
#line 170 "Language/lang.y"
                                                                        {
													globalCurrentScope->AddBranch (yystack_[2].value.as < NodeInterface* > ());
													ScopeNodeInterface* scopeTrue = globalCurrentScope;
													globalCurrentScope->Outro ();
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													globalCurrentScope->AddBranch (yystack_[0].value.as < NodeInterface* > ());
													ScopeNodeInterface* scopeFalse = globalCurrentScope;
													globalCurrentScope->Outro ();
													yylhs.value.as < NodeInterface* > () = NodeInterface::CreateIfNode (yystack_[3].value.as < NodeInterface* > (), scopeTrue, scopeFalse);
												}
#line 1106 "Build/lang.tab.cc"
    break;

  case 28: // if_condition: "if" "(" condition ")"
#line 183 "Language/lang.y"
                                                        {
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													yylhs.value.as < NodeInterface* > () = yystack_[1].value.as < NodeInterface* > ();
												}
#line 1115 "Build/lang.tab.cc"
    break;

  case 29: // while: while_condition action
#line 190 "Language/lang.y"
                                                                        {
													globalCurrentScope->AddBranch (yystack_[0].value.as < NodeInterface* > ());
													ScopeNodeInterface* scope = globalCurrentScope;
													globalCurrentScope->Outro ();
													yylhs.value.as < NodeInterface* > () = NodeInterface::CreateWhileNode (yystack_[1].value.as < NodeInterface* > (), scope);
												}
#line 1126 "Build/lang.tab.cc"
    break;

  case 30: // while_condition: "while" "(" condition ")"
#line 199 "Language/lang.y"
                                                        {
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													yylhs.value.as < NodeInterface* > () = yystack_[1].value.as < NodeInterface* > ();
												}
#line 1135 "Build/lang.tab.cc"
    break;

  case 31: // condition: exprLvl1 ">" exprLvl1
#line 206 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_GREATER, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1141 "Build/lang.tab.cc"
    break;

  case 32: // condition: exprLvl1 ">=" exprLvl1
#line 207 "Language/lang.y"
                                                { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_GREATER_OR_EQ, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1147 "Build/lang.tab.cc"
    break;

  case 33: // condition: exprLvl1 "<" exprLvl1
#line 208 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_LESS, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1153 "Build/lang.tab.cc"
    break;

  case 34: // condition: exprLvl1 "<=" exprLvl1
#line 209 "Language/lang.y"
                                                { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_LESS_OR_EQ, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1159 "Build/lang.tab.cc"
    break;

  case 35: // condition: exprLvl1 "==" exprLvl1
#line 210 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_EQ, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1165 "Build/lang.tab.cc"
    break;

  case 36: // condition: exprLvl1 "!=" exprLvl1
#line 211 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_NOT_EQ, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1171 "Build/lang.tab.cc"
    break;

  case 37: // condition: exprLvl1
#line 212 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1177 "Build/lang.tab.cc"
    break;

  case 38: // assignment: TEXT "=" exprLvl1 ";"
#line 216 "Language/lang.y"
                                                        { 	
											globalCurrentScope->SetVariableValue (*(yystack_[3].value.as < std::string* > ()), 0);
											NodeInterface* left = NodeInterface::CreateVariableNode (*(yystack_[3].value.as < std::string* > ()));
											delete yystack_[3].value.as < std::string* > ();
								  			yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, yystack_[1].value.as < NodeInterface* > ());
										}
#line 1188 "Build/lang.tab.cc"
    break;

  case 39: // assignment_scope: TEXT "=" scope
#line 225 "Language/lang.y"
                                                                { 
											globalCurrentScope->SetVariableValue (*(yystack_[2].value.as < std::string* > ()), 0);
											NodeInterface* left = NodeInterface::CreateVariableNode (*(yystack_[2].value.as < std::string* > ()));
											delete yystack_[2].value.as < std::string* > ();
								  			yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, yystack_[0].value.as < ScopeNodeInterface* > ());
										}
#line 1199 "Build/lang.tab.cc"
    break;

  case 40: // function_assignment: function_assignment_entry inside_scope scope_outro
#line 234 "Language/lang.y"
                                                                                {	
																	ScopeNodeInterface* scope = globalCurrentScope; globalCurrentScope->Outro ();
																	yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_FUNCTION_ASSIGN, yystack_[2].value.as < NodeInterface* > (), scope);
																}
#line 1208 "Build/lang.tab.cc"
    break;

  case 41: // function_assignment: function_assignment_entry inside_scope scope_outro ";"
#line 238 "Language/lang.y"
                                                                        {	
																	ScopeNodeInterface* scope = globalCurrentScope; globalCurrentScope->Outro ();
																	yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_FUNCTION_ASSIGN, yystack_[3].value.as < NodeInterface* > (), scope);
																}
#line 1217 "Build/lang.tab.cc"
    break;

  case 42: // function_assignment_entry: TEXT "=" "func" arg_list "{"
#line 245 "Language/lang.y"
                                                                {
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													globalCurrentScope->Previous ()->SetFunctionVariableScope (*(yystack_[4].value.as < std::string* > ()), yystack_[1].value.as < ArgumentsListElement* > (), globalCurrentScope);
													yylhs.value.as < NodeInterface* > () = NodeInterface::CreateFunctionVariableNode (*(yystack_[4].value.as < std::string* > ()), yystack_[1].value.as < ArgumentsListElement* > ());
													delete yystack_[4].value.as < std::string* > ();
												}
#line 1228 "Build/lang.tab.cc"
    break;

  case 43: // function_assignment_entry: TEXT "=" "func" arg_list ":" TEXT "{"
#line 251 "Language/lang.y"
                                                        { 
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													globalCurrentScope->Previous ()->SetFunctionVariableScope (*(yystack_[6].value.as < std::string* > ()), yystack_[3].value.as < ArgumentsListElement* > (), globalCurrentScope, true, *(yystack_[1].value.as < std::string* > ()));
													yylhs.value.as < NodeInterface* > () = NodeInterface::CreateFunctionVariableNode (*(yystack_[6].value.as < std::string* > ()), yystack_[3].value.as < ArgumentsListElement* > ());
													delete yystack_[6].value.as < std::string* > ();
													delete yystack_[1].value.as < std::string* > ();
												}
#line 1240 "Build/lang.tab.cc"
    break;

  case 44: // arg_list: "(" arg_list_inside ")"
#line 261 "Language/lang.y"
                                                        { yylhs.value.as < ArgumentsListElement* > () = yystack_[1].value.as < ArgumentsListElement* > (); }
#line 1246 "Build/lang.tab.cc"
    break;

  case 45: // arg_list: "(" ")"
#line 262 "Language/lang.y"
                                                                        { /* empty */ }
#line 1252 "Build/lang.tab.cc"
    break;

  case 46: // arg_list_inside: TEXT
#line 266 "Language/lang.y"
                                                                        { 	
											NodeInterface* temp = NodeInterface::CreateVariableNode (*(yystack_[0].value.as < std::string* > ()));
											yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (temp, nullptr);
											delete yystack_[0].value.as < std::string* > ();
										}
#line 1262 "Build/lang.tab.cc"
    break;

  case 47: // arg_list_inside: TEXT "," arg_list_inside
#line 271 "Language/lang.y"
                                                        { 	
											NodeInterface* temp = NodeInterface::CreateVariableNode (*(yystack_[2].value.as < std::string* > ()));
											yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (temp, yystack_[0].value.as < ArgumentsListElement* > ());
											delete yystack_[2].value.as < std::string* > ();
										}
#line 1272 "Build/lang.tab.cc"
    break;

  case 48: // return: "return" exprLvl1 ";"
#line 279 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateReturnNode (static_cast <ScopeNode*> (globalCurrentScope), yystack_[1].value.as < NodeInterface* > ()); }
#line 1278 "Build/lang.tab.cc"
    break;

  case 49: // syscall: "print" exprLvl1 ";"
#line 283 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreatePrintNode (yystack_[1].value.as < NodeInterface* > ()); }
#line 1284 "Build/lang.tab.cc"
    break;

  case 50: // exprLvl1: exprLvl2 "+" exprLvl1
#line 287 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ADD, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1290 "Build/lang.tab.cc"
    break;

  case 51: // exprLvl1: exprLvl2 "-" exprLvl1
#line 288 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1296 "Build/lang.tab.cc"
    break;

  case 52: // exprLvl1: exprLvl2
#line 289 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1302 "Build/lang.tab.cc"
    break;

  case 53: // exprLvl1_no_unary: exprLvl2_no_unary "+" exprLvl1
#line 293 "Language/lang.y"
                                                { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ADD, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1308 "Build/lang.tab.cc"
    break;

  case 54: // exprLvl1_no_unary: exprLvl2_no_unary "-" exprLvl1
#line 294 "Language/lang.y"
                                                { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1314 "Build/lang.tab.cc"
    break;

  case 55: // exprLvl1_no_unary: exprLvl2_no_unary
#line 295 "Language/lang.y"
                                                                { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1320 "Build/lang.tab.cc"
    break;

  case 56: // exprLvl2: exprLvl3 "*" exprLvl2
#line 299 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_MUL, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1326 "Build/lang.tab.cc"
    break;

  case 57: // exprLvl2: exprLvl3 "/" exprLvl2
#line 300 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_DIV, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1332 "Build/lang.tab.cc"
    break;

  case 58: // exprLvl2: exprLvl3
#line 301 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1338 "Build/lang.tab.cc"
    break;

  case 59: // exprLvl2_no_unary: exprLvl4 "*" exprLvl2
#line 305 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_MUL, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1344 "Build/lang.tab.cc"
    break;

  case 60: // exprLvl2_no_unary: exprLvl4 "/" exprLvl2
#line 306 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_DIV, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1350 "Build/lang.tab.cc"
    break;

  case 61: // exprLvl2_no_unary: exprLvl4
#line 307 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1356 "Build/lang.tab.cc"
    break;

  case 62: // exprLvl3: "-" exprLvl4
#line 311 "Language/lang.y"
                                                                { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, NodeInterface::CreateValueNode (0), yystack_[0].value.as < NodeInterface* > ()); }
#line 1362 "Build/lang.tab.cc"
    break;

  case 63: // exprLvl3: "+" exprLvl4
#line 312 "Language/lang.y"
                                                                { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1368 "Build/lang.tab.cc"
    break;

  case 64: // exprLvl3: exprLvl4
#line 313 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1374 "Build/lang.tab.cc"
    break;

  case 65: // exprLvl4: "(" exprLvl1 ")"
#line 317 "Language/lang.y"
                                            { yylhs.value.as < NodeInterface* > () = yystack_[1].value.as < NodeInterface* > (); }
#line 1380 "Build/lang.tab.cc"
    break;

  case 66: // exprLvl4: NUMBER
#line 318 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateValueNode (yystack_[0].value.as < NumberType > ()); }
#line 1386 "Build/lang.tab.cc"
    break;

  case 67: // exprLvl4: TEXT
#line 319 "Language/lang.y"
                                                                        { 	
											try {
												globalCurrentScope->GetVariableValue (*(yystack_[0].value.as < std::string* > ()));
											}
											catch (std::invalid_argument& ex) {
												driver->PrintErrorAndExit (yystack_[0].location, "Undefined variable!");
											}
											yylhs.value.as < NodeInterface* > () = NodeInterface::CreateVariableNode (*(yystack_[0].value.as < std::string* > ()));
											delete yystack_[0].value.as < std::string* > (); 
										}
#line 1401 "Build/lang.tab.cc"
    break;

  case 68: // exprLvl4: "?"
#line 329 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateScanNode (); }
#line 1407 "Build/lang.tab.cc"
    break;

  case 69: // exprLvl4: TEXT call_arg_list
#line 330 "Language/lang.y"
                                                                { 
											
											if (!globalCurrentScope->GetFunctionVariableScope (*(yystack_[1].value.as < std::string* > ()), yystack_[0].value.as < ArgumentsListElement* > ())) {
												globalFunctionSymTable->AddMissingFunction (*(yystack_[1].value.as < std::string* > ()), yystack_[0].value.as < ArgumentsListElement* > ());
											}
											yylhs.value.as < NodeInterface* > () = NodeInterface::CreateFunctionVariableNode (*(yystack_[1].value.as < std::string* > ()), yystack_[0].value.as < ArgumentsListElement* > ());
											delete yystack_[1].value.as < std::string* > (); 
										}
#line 1420 "Build/lang.tab.cc"
    break;

  case 70: // call_arg_list: "(" call_arg_list_inside ")"
#line 341 "Language/lang.y"
                                                        { yylhs.value.as < ArgumentsListElement* > () = yystack_[1].value.as < ArgumentsListElement* > (); }
#line 1426 "Build/lang.tab.cc"
    break;

  case 71: // call_arg_list: "(" ")"
#line 342 "Language/lang.y"
                                                                                { /* empty */ }
#line 1432 "Build/lang.tab.cc"
    break;

  case 72: // call_arg_list_inside: exprLvl1
#line 346 "Language/lang.y"
                                                                                                { yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (yystack_[0].value.as < NodeInterface* > (), nullptr); }
#line 1438 "Build/lang.tab.cc"
    break;

  case 73: // call_arg_list_inside: exprLvl1 "," call_arg_list_inside
#line 347 "Language/lang.y"
                                                                        { yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < ArgumentsListElement* > ()); }
#line 1444 "Build/lang.tab.cc"
    break;

  case 74: // call_arg_list_inside: scope
#line 348 "Language/lang.y"
                                                                                                { yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (yystack_[0].value.as < ScopeNodeInterface* > (), nullptr); }
#line 1450 "Build/lang.tab.cc"
    break;

  case 75: // call_arg_list_inside: scope "," call_arg_list_inside
#line 349 "Language/lang.y"
                                                                        { yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (yystack_[2].value.as < ScopeNodeInterface* > (), yystack_[0].value.as < ArgumentsListElement* > ()); }
#line 1456 "Build/lang.tab.cc"
    break;


#line 1460 "Build/lang.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        report_syntax_error (yyctx);
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "+", "-", "*", "/", "=", ";",
  "(", ")", "{", "}", ">", ">=", "<", "<=", "==", "!=", "?", "if", "else",
  "while", "print", "func", "return", ":", ",", "ERROR", "NUMBER", "TEXT",
  "'+'", "'-'", "'*'", "'/'", "then", "UNARY_MINUS", "$accept", "scope",
  "scope_entry", "inside_scope", "inside_scope_left", "action",
  "action_no_unary", "scope_outro", "if", "if_condition", "while",
  "while_condition", "condition", "assignment", "assignment_scope",
  "function_assignment", "function_assignment_entry", "arg_list",
  "arg_list_inside", "return", "syscall", "exprLvl1", "exprLvl1_no_unary",
  "exprLvl2", "exprLvl2_no_unary", "exprLvl3", "exprLvl4", "call_arg_list",
  "call_arg_list_inside", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }




  const signed char parser::yypact_ninf_ = -53;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
     -53,    25,    17,   -53,    32,    32,   120,   -53,   -53,    20,
      29,   120,   120,   -53,     5,   -53,   -53,   -53,   -53,    49,
     -53,    49,   -53,   132,   -53,   -53,   -53,   -53,    42,    13,
      43,   -53,    35,   -53,   -53,     3,   120,   120,    51,    62,
      89,   101,   -53,    63,    36,    61,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,    75,    53,    59,    63,   -53,
     120,   120,   120,   120,   -53,    74,   150,    84,   -53,   -53,
      76,   -53,    87,   -53,    72,    79,    93,   -53,   -53,    98,
      49,   -53,   120,   120,   120,   120,   106,   -53,   -53,   -53,
     -53,   -53,   120,   120,   120,   120,   120,   120,   -53,    -7,
      -4,   -53,   129,   129,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,    82,   105,
     -53,    86,   -53,   -53,    91,   -53,   114,   -53,   -53
  };

  const signed char
  parser::yydefact_[] =
  {
       8,     0,     4,     1,     0,     0,     0,     3,    68,     0,
       0,     0,     0,    66,    67,    16,     8,     6,    14,     0,
      15,     0,     9,     5,    10,     8,    11,    13,     0,    52,
      58,    64,    67,    63,    62,     0,     0,     0,     0,     0,
       0,     0,    69,     0,    67,    26,    29,    24,     7,    22,
      23,    17,    18,    19,    21,     0,    55,    61,     0,    12,
       0,     0,     0,     0,    65,     0,    37,     0,    49,    48,
       0,    39,     0,    71,    74,    72,     0,    25,     2,     0,
       0,    20,     0,     0,     0,     0,    40,    50,    51,    56,
      57,    28,     0,     0,     0,     0,     0,     0,    30,     0,
       0,    38,     0,     0,    70,    27,    53,    54,    59,    60,
      41,    31,    32,    33,    34,    35,    36,    45,    46,     0,
      42,     0,    75,    73,     0,    44,     0,    47,    43
  };

  const signed char
  parser::yypgoto_[] =
  {
     -53,   -22,   -53,    -1,   -53,   -17,   -53,    68,   111,   -53,
     112,   -53,    99,   119,   -53,   121,   -53,   -53,    21,   123,
     124,    -6,   -53,   -52,   -53,   -53,     4,   -53,   -36
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,    15,    16,     1,     2,    17,    48,    78,    18,    19,
      20,    21,    65,    22,    23,    24,    25,   100,   119,    26,
      27,    28,    55,    29,    56,    30,    31,    42,    76
  };

  const unsigned char
  parser::yytable_[] =
  {
      35,    47,    45,   117,    46,    38,    39,   120,    33,    34,
      89,    90,    40,    64,    41,    43,    60,    61,    71,    74,
       4,     5,   121,   118,    58,     3,     6,    57,     7,    36,
      66,    66,   108,   109,    72,    75,     8,     9,    37,    10,
      11,     6,    12,    79,    41,    41,    13,    14,    62,    63,
      59,     8,     4,     5,    87,    88,    82,    83,     6,    68,
       7,    13,    32,   105,    84,    85,   122,   123,     8,     9,
      69,    10,    11,    72,    12,    77,   106,   107,    13,    44,
      74,    74,    80,    81,    91,    99,   111,   112,   113,   114,
     115,   116,     4,     5,    98,   101,    75,    75,     6,   102,
       7,     4,     5,   104,     4,     5,   103,     6,     8,   124,
       6,    73,     7,    70,   110,   125,   126,     8,    13,    32,
       8,   118,    70,     4,     5,   128,    86,    13,    32,     6,
      13,    32,     4,     5,    49,    50,    67,     0,     6,     8,
       7,     6,    51,     7,    52,   127,    53,    54,     8,    13,
      32,     8,     9,     0,    10,    11,     0,    12,    13,    32,
       0,    13,    44,    92,    93,    94,    95,    96,    97
  };

  const signed char
  parser::yycheck_[] =
  {
       6,    23,    19,    10,    21,    11,    12,    11,     4,     5,
      62,    63,     7,    10,     9,    16,     3,     4,    40,    41,
       3,     4,    26,    30,    25,     0,     9,    23,    11,     9,
      36,    37,    84,    85,    40,    41,    19,    20,     9,    22,
      23,     9,    25,     7,     9,     9,    29,    30,     5,     6,
       8,    19,     3,     4,    60,    61,     3,     4,     9,     8,
      11,    29,    30,    80,     5,     6,   102,   103,    19,    20,
       8,    22,    23,    79,    25,    12,    82,    83,    29,    30,
     102,   103,    21,     8,    10,     9,    92,    93,    94,    95,
      96,    97,     3,     4,    10,     8,   102,   103,     9,    27,
      11,     3,     4,    10,     3,     4,    27,     9,    19,    27,
       9,    10,    11,    24,     8,    10,    30,    19,    29,    30,
      19,    30,    24,     3,     4,    11,    58,    29,    30,     9,
      29,    30,     3,     4,    23,    23,    37,    -1,     9,    19,
      11,     9,    23,    11,    23,   124,    23,    23,    19,    29,
      30,    19,    20,    -1,    22,    23,    -1,    25,    29,    30,
      -1,    29,    30,    13,    14,    15,    16,    17,    18
  };

  const signed char
  parser::yystos_[] =
  {
       0,    40,    41,     0,     3,     4,     9,    11,    19,    20,
      22,    23,    25,    29,    30,    38,    39,    42,    45,    46,
      47,    48,    50,    51,    52,    53,    56,    57,    58,    60,
      62,    63,    30,    63,    63,    58,     9,     9,    58,    58,
       7,     9,    64,    40,    30,    42,    42,    38,    43,    45,
      47,    50,    52,    56,    57,    59,    61,    63,    40,     8,
       3,     4,     5,     6,    10,    49,    58,    49,     8,     8,
      24,    38,    58,    10,    38,    58,    65,    12,    44,     7,
      21,     8,     3,     4,     5,     6,    44,    58,    58,    60,
      60,    10,    13,    14,    15,    16,    17,    18,    10,     9,
      54,     8,    27,    27,    10,    42,    58,    58,    60,    60,
       8,    58,    58,    58,    58,    58,    58,    10,    30,    55,
      11,    26,    65,    65,    27,    10,    30,    55,    11
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    37,    38,    39,    40,    40,    41,    41,    41,    42,
      42,    42,    42,    42,    42,    42,    42,    43,    43,    43,
      43,    43,    43,    43,    43,    44,    45,    45,    46,    47,
      48,    49,    49,    49,    49,    49,    49,    49,    50,    51,
      52,    52,    53,    53,    54,    54,    55,    55,    56,    57,
      58,    58,    58,    59,    59,    59,    60,    60,    60,    61,
      61,    61,    62,    62,    62,    63,    63,    63,    63,    63,
      64,    64,    65,    65,    65,    65
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     1,     1,     2,     2,     3,     0,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     2,     4,     4,     2,
       4,     3,     3,     3,     3,     3,     3,     1,     4,     3,
       3,     4,     5,     7,     3,     2,     1,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     3,     1,     1,     1,     2,
       3,     2,     1,     3,     1,     3
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   113,   113,   117,   123,   124,   128,   130,   134,   138,
     139,   140,   141,   142,   143,   144,   145,   149,   150,   151,
     152,   153,   154,   155,   156,   160,   164,   170,   183,   190,
     199,   206,   207,   208,   209,   210,   211,   212,   216,   225,
     234,   238,   245,   251,   261,   262,   266,   271,   279,   283,
     287,   288,   289,   293,   294,   295,   299,   300,   301,   305,
     306,   307,   311,   312,   313,   317,   318,   319,   329,   330,
     341,   342,   346,   347,   348,   349
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    33,    31,     2,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    35,    36
    };
    // Last valid token kind.
    const int code_max = 287;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 1941 "Build/lang.tab.cc"

#line 352 "Language/lang.y"


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
