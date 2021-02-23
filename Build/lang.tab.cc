// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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
	extern int codePass;

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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
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
      case symbol_kind::S_action: // action
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl3: // exprLvl3
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
      case symbol_kind::S_action: // action
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl3: // exprLvl3
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
  parser::by_kind::clear ()
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
      case symbol_kind::S_action: // action
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl3: // exprLvl3
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
      case symbol_kind::S_action: // action
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl3: // exprLvl3
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
      case symbol_kind::S_action: // action
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl3: // exprLvl3
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
      case symbol_kind::S_action: // action
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl3: // exprLvl3
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
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
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
      case symbol_kind::S_action: // action
      case symbol_kind::S_if: // if
      case symbol_kind::S_if_condition: // if_condition
      case symbol_kind::S_while: // while
      case symbol_kind::S_while_condition: // while_condition
      case symbol_kind::S_condition: // condition
      case symbol_kind::S_assignment: // assignment
      case symbol_kind::S_function_assignment: // function_assignment
      case symbol_kind::S_function_assignment_entry: // function_assignment_entry
      case symbol_kind::S_return: // return
      case symbol_kind::S_syscall: // syscall
      case symbol_kind::S_exprLvl1: // exprLvl1
      case symbol_kind::S_exprLvl2: // exprLvl2
      case symbol_kind::S_exprLvl3: // exprLvl3
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
#line 109 "Language/lang.y"
                                                                        { yylhs.value.as < ScopeNodeInterface* > () = globalCurrentScope; globalCurrentScope->Outro (); }
#line 895 "Build/lang.tab.cc"
    break;

  case 3: // scope: scope_entry inside_scope scope_outro ";"
#line 110 "Language/lang.y"
                                                                        { yylhs.value.as < ScopeNodeInterface* > () = globalCurrentScope; globalCurrentScope->Outro (); }
#line 901 "Build/lang.tab.cc"
    break;

  case 4: // scope_entry: "{"
#line 114 "Language/lang.y"
                                                                                                        { 
															globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
														}
#line 909 "Build/lang.tab.cc"
    break;

  case 5: // inside_scope: inside_scope action
#line 120 "Language/lang.y"
                                                                                                { globalCurrentScope->AddNode (yystack_[0].value.as < NodeInterface* > ()); }
#line 915 "Build/lang.tab.cc"
    break;

  case 6: // inside_scope: %empty
#line 121 "Language/lang.y"
                                                                                                                { /* empty */ }
#line 921 "Build/lang.tab.cc"
    break;

  case 7: // action: assignment
#line 125 "Language/lang.y"
                                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 927 "Build/lang.tab.cc"
    break;

  case 8: // action: function_assignment
#line 126 "Language/lang.y"
                                                                                                { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 933 "Build/lang.tab.cc"
    break;

  case 9: // action: return
#line 127 "Language/lang.y"
                                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 939 "Build/lang.tab.cc"
    break;

  case 10: // action: exprLvl1 ";"
#line 128 "Language/lang.y"
                                                                                                { yylhs.value.as < NodeInterface* > () = yystack_[1].value.as < NodeInterface* > (); }
#line 945 "Build/lang.tab.cc"
    break;

  case 11: // action: syscall
#line 129 "Language/lang.y"
                                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 951 "Build/lang.tab.cc"
    break;

  case 12: // action: if
#line 130 "Language/lang.y"
                                                                                                                { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 957 "Build/lang.tab.cc"
    break;

  case 13: // action: while
#line 131 "Language/lang.y"
                                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 963 "Build/lang.tab.cc"
    break;

  case 14: // action: scope
#line 132 "Language/lang.y"
                                                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < ScopeNodeInterface* > (); }
#line 969 "Build/lang.tab.cc"
    break;

  case 15: // scope_outro: "}"
#line 136 "Language/lang.y"
                                                                                                        { /* empty */ }
#line 975 "Build/lang.tab.cc"
    break;

  case 16: // if: if_condition action
#line 140 "Language/lang.y"
                                                                                                {
															globalCurrentScope->AddNode (yystack_[0].value.as < NodeInterface* > ());
															ScopeNodeInterface* scope = globalCurrentScope;
															globalCurrentScope->Outro ();
															yylhs.value.as < NodeInterface* > () = NodeInterface::CreateIfNode (yystack_[1].value.as < NodeInterface* > (), scope);
														}
#line 986 "Build/lang.tab.cc"
    break;

  case 17: // if_condition: "if" "(" condition ")"
#line 149 "Language/lang.y"
                                                                        {
															globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
															yylhs.value.as < NodeInterface* > () = yystack_[1].value.as < NodeInterface* > ();
														}
#line 995 "Build/lang.tab.cc"
    break;

  case 18: // while: while_condition action
#line 156 "Language/lang.y"
                                                                                        {
															globalCurrentScope->AddNode (yystack_[0].value.as < NodeInterface* > ());
															ScopeNodeInterface* scope = globalCurrentScope;
															globalCurrentScope->Outro ();
															yylhs.value.as < NodeInterface* > () = NodeInterface::CreateWhileNode (yystack_[1].value.as < NodeInterface* > (), scope);
														}
#line 1006 "Build/lang.tab.cc"
    break;

  case 19: // while_condition: "while" "(" condition ")"
#line 165 "Language/lang.y"
                                                                        {
															globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
															yylhs.value.as < NodeInterface* > () = yystack_[1].value.as < NodeInterface* > ();
														}
#line 1015 "Build/lang.tab.cc"
    break;

  case 20: // condition: exprLvl1 ">" exprLvl1
#line 172 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_GREATER, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1021 "Build/lang.tab.cc"
    break;

  case 21: // condition: exprLvl1 ">=" exprLvl1
#line 173 "Language/lang.y"
                                                { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_GREATER_OR_EQ, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1027 "Build/lang.tab.cc"
    break;

  case 22: // condition: exprLvl1 "<" exprLvl1
#line 174 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_LESS, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1033 "Build/lang.tab.cc"
    break;

  case 23: // condition: exprLvl1 "<=" exprLvl1
#line 175 "Language/lang.y"
                                                { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_LESS_OR_EQ, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1039 "Build/lang.tab.cc"
    break;

  case 24: // condition: exprLvl1 "==" exprLvl1
#line 176 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_EQ, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1045 "Build/lang.tab.cc"
    break;

  case 25: // condition: exprLvl1 "!=" exprLvl1
#line 177 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_NOT_EQ, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1051 "Build/lang.tab.cc"
    break;

  case 26: // condition: exprLvl1
#line 178 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1057 "Build/lang.tab.cc"
    break;

  case 27: // assignment: TEXT "=" exprLvl1 ";"
#line 182 "Language/lang.y"
                                                        { 	
											globalCurrentScope->SetVariable (*(yystack_[3].value.as < std::string* > ()), 0);
											NodeInterface* left = NodeInterface::CreateVariableNode (*(yystack_[3].value.as < std::string* > ()));
											delete yystack_[3].value.as < std::string* > ();
								  			yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, yystack_[1].value.as < NodeInterface* > ());
										}
#line 1068 "Build/lang.tab.cc"
    break;

  case 28: // assignment: TEXT "=" scope
#line 188 "Language/lang.y"
                                                                { 
											globalCurrentScope->SetVariable (*(yystack_[2].value.as < std::string* > ()), 0);
											NodeInterface* left = NodeInterface::CreateVariableNode (*(yystack_[2].value.as < std::string* > ()));
											delete yystack_[2].value.as < std::string* > ();
								  			yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, yystack_[0].value.as < ScopeNodeInterface* > ());
										}
#line 1079 "Build/lang.tab.cc"
    break;

  case 29: // function_assignment: function_assignment_entry inside_scope scope_outro
#line 197 "Language/lang.y"
                                                                {	
															ScopeNodeInterface* scope = globalCurrentScope; globalCurrentScope->Outro ();
															yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_FUNCTION_ASSIGN, yystack_[2].value.as < NodeInterface* > (), scope);
														}
#line 1088 "Build/lang.tab.cc"
    break;

  case 30: // function_assignment_entry: TEXT "=" "func" arg_list "{"
#line 204 "Language/lang.y"
                                                                {
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													globalCurrentScope->Previous ()->SetFunctionVariable (*(yystack_[4].value.as < std::string* > ()), yystack_[1].value.as < ArgumentsListElement* > (), globalCurrentScope);
													yylhs.value.as < NodeInterface* > () = NodeInterface::CreateFunctionVariableNode (*(yystack_[4].value.as < std::string* > ()), yystack_[1].value.as < ArgumentsListElement* > ());
													delete yystack_[4].value.as < std::string* > ();
												}
#line 1099 "Build/lang.tab.cc"
    break;

  case 31: // function_assignment_entry: TEXT "=" "func" arg_list ":" TEXT "{"
#line 210 "Language/lang.y"
                                                        { 
													globalCurrentScope->Entry (ScopeNodeInterface::CreateScopeNode ());
													globalCurrentScope->Previous ()->SetFunctionVariable (*(yystack_[6].value.as < std::string* > ()), yystack_[3].value.as < ArgumentsListElement* > (), globalCurrentScope, true, *(yystack_[1].value.as < std::string* > ()));
													yylhs.value.as < NodeInterface* > () = NodeInterface::CreateFunctionVariableNode (*(yystack_[6].value.as < std::string* > ()), yystack_[3].value.as < ArgumentsListElement* > ());
													delete yystack_[6].value.as < std::string* > ();
													delete yystack_[1].value.as < std::string* > ();
												}
#line 1111 "Build/lang.tab.cc"
    break;

  case 32: // arg_list: "(" arg_list_inside ")"
#line 220 "Language/lang.y"
                                                        { yylhs.value.as < ArgumentsListElement* > () = yystack_[1].value.as < ArgumentsListElement* > (); }
#line 1117 "Build/lang.tab.cc"
    break;

  case 33: // arg_list: "(" ")"
#line 221 "Language/lang.y"
                                                                        { /* empty */ }
#line 1123 "Build/lang.tab.cc"
    break;

  case 34: // arg_list_inside: TEXT
#line 225 "Language/lang.y"
                                                                        { 	
											NodeInterface* temp = NodeInterface::CreateVariableNode (*(yystack_[0].value.as < std::string* > ()));
											yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (temp, nullptr);
											delete yystack_[0].value.as < std::string* > ();
										}
#line 1133 "Build/lang.tab.cc"
    break;

  case 35: // arg_list_inside: TEXT "," arg_list_inside
#line 230 "Language/lang.y"
                                                        { 	
											NodeInterface* temp = NodeInterface::CreateVariableNode (*(yystack_[2].value.as < std::string* > ()));
											yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (temp, yystack_[0].value.as < ArgumentsListElement* > ());
											delete yystack_[2].value.as < std::string* > ();
										}
#line 1143 "Build/lang.tab.cc"
    break;

  case 36: // return: "return" exprLvl1 ";"
#line 238 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateReturnNode (yystack_[1].value.as < NodeInterface* > ()); }
#line 1149 "Build/lang.tab.cc"
    break;

  case 37: // syscall: "print" exprLvl1 ";"
#line 242 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreatePrintNode (yystack_[1].value.as < NodeInterface* > ()); }
#line 1155 "Build/lang.tab.cc"
    break;

  case 38: // exprLvl1: exprLvl2 "+" exprLvl1
#line 246 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ADD, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1161 "Build/lang.tab.cc"
    break;

  case 39: // exprLvl1: exprLvl2 "-" exprLvl1
#line 247 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1167 "Build/lang.tab.cc"
    break;

  case 40: // exprLvl1: exprLvl2
#line 248 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1173 "Build/lang.tab.cc"
    break;

  case 41: // exprLvl2: exprLvl3 "*" exprLvl2
#line 252 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_MUL, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1179 "Build/lang.tab.cc"
    break;

  case 42: // exprLvl2: exprLvl3 "/" exprLvl2
#line 253 "Language/lang.y"
                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_DIV, yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < NodeInterface* > ()); }
#line 1185 "Build/lang.tab.cc"
    break;

  case 43: // exprLvl2: exprLvl3
#line 254 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = yystack_[0].value.as < NodeInterface* > (); }
#line 1191 "Build/lang.tab.cc"
    break;

  case 44: // exprLvl3: "(" exprLvl1 ")"
#line 258 "Language/lang.y"
                                            { yylhs.value.as < NodeInterface* > () = yystack_[1].value.as < NodeInterface* > (); }
#line 1197 "Build/lang.tab.cc"
    break;

  case 45: // exprLvl3: NUMBER
#line 259 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateValueNode (yystack_[0].value.as < NumberType > ()); }
#line 1203 "Build/lang.tab.cc"
    break;

  case 46: // exprLvl3: TEXT
#line 260 "Language/lang.y"
                                                                        { 	
											try {
												globalCurrentScope->GetVariable (*(yystack_[0].value.as < std::string* > ()));
											}
											catch (std::invalid_argument& ex) {
												driver->PrintErrorAndExit (yystack_[0].location, "Undefined variable!");
											}
											yylhs.value.as < NodeInterface* > () = NodeInterface::CreateVariableNode (*(yystack_[0].value.as < std::string* > ()));
											delete yystack_[0].value.as < std::string* > (); 
										}
#line 1218 "Build/lang.tab.cc"
    break;

  case 47: // exprLvl3: "?"
#line 270 "Language/lang.y"
                                                                        { yylhs.value.as < NodeInterface* > () = NodeInterface::CreateScanNode (); }
#line 1224 "Build/lang.tab.cc"
    break;

  case 48: // exprLvl3: TEXT call_arg_list
#line 271 "Language/lang.y"
                                                                { 
											try {
												globalCurrentScope->GetFunctionVariable (*(yystack_[1].value.as < std::string* > ()), yystack_[0].value.as < ArgumentsListElement* > ());
											}
											catch (std::invalid_argument& ex) {
												driver->PrintErrorAndExit (yystack_[1].location, "Undefined function variable!");
											}
											yylhs.value.as < NodeInterface* > () = NodeInterface::CreateFunctionVariableNode (*(yystack_[1].value.as < std::string* > ()), yystack_[0].value.as < ArgumentsListElement* > ());
											delete yystack_[1].value.as < std::string* > (); 
										}
#line 1239 "Build/lang.tab.cc"
    break;

  case 49: // call_arg_list: "(" call_arg_list_inside ")"
#line 284 "Language/lang.y"
                                                        { yylhs.value.as < ArgumentsListElement* > () = yystack_[1].value.as < ArgumentsListElement* > (); }
#line 1245 "Build/lang.tab.cc"
    break;

  case 50: // call_arg_list: "(" ")"
#line 285 "Language/lang.y"
                                                                                { /* empty */ }
#line 1251 "Build/lang.tab.cc"
    break;

  case 51: // call_arg_list_inside: exprLvl1
#line 289 "Language/lang.y"
                                                                                                { yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (yystack_[0].value.as < NodeInterface* > (), nullptr); }
#line 1257 "Build/lang.tab.cc"
    break;

  case 52: // call_arg_list_inside: exprLvl1 "," call_arg_list_inside
#line 290 "Language/lang.y"
                                                                        { yylhs.value.as < ArgumentsListElement* > () = new ArgumentsListElement (yystack_[2].value.as < NodeInterface* > (), yystack_[0].value.as < ArgumentsListElement* > ()); }
#line 1263 "Build/lang.tab.cc"
    break;


#line 1267 "Build/lang.tab.cc"

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
  "(", ")", "{", "}", ">", ">=", "<", "<=", "==", "!=", "?", "if", "while",
  "print", "func", "return", ":", ",", "ERROR", "NUMBER", "TEXT", "'+'",
  "'-'", "'*'", "'/'", "$accept", "scope", "scope_entry", "inside_scope",
  "action", "scope_outro", "if", "if_condition", "while",
  "while_condition", "condition", "assignment", "function_assignment",
  "function_assignment_entry", "arg_list", "arg_list_inside", "return",
  "syscall", "exprLvl1", "exprLvl2", "exprLvl3", "call_arg_list",
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




  const signed char parser::yypact_ninf_ = -10;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
     -10,    13,   -10,    27,   -10,   -10,     9,    31,    27,    27,
     -10,     5,   -10,   -10,   -10,   -10,    65,   -10,    65,   -10,
     -10,   -10,   -10,   -10,    37,    40,     2,    66,    69,    27,
      27,    72,    73,    -8,     0,   -10,    49,   -10,   -10,    49,
     -10,    27,    27,    27,    27,   -10,    78,    34,    80,   -10,
     -10,    74,   -10,    83,   -10,    56,    82,   -10,    87,   -10,
     -10,   -10,   -10,   -10,   -10,    27,    27,    27,    27,    27,
      27,   -10,    -6,    -9,   -10,    27,   -10,   -10,   -10,   -10,
     -10,   -10,   -10,   -10,   -10,    70,    88,   -10,    68,   -10,
      71,   -10,    90,   -10,   -10
  };

  const signed char
  parser::yydefact_[] =
  {
       6,     0,     1,     0,     4,    47,     0,     0,     0,     0,
      45,    46,    14,     6,     5,    12,     0,    13,     0,     7,
       8,     6,     9,    11,     0,    40,    43,    46,     0,     0,
       0,     0,     0,     0,     0,    48,     0,    16,    18,     0,
      10,     0,     0,     0,     0,    44,     0,    26,     0,    37,
      36,     0,    28,     0,    50,    51,     0,    15,     2,    29,
      38,    39,    41,    42,    17,     0,     0,     0,     0,     0,
       0,    19,     0,     0,    27,     0,    49,     3,    20,    21,
      22,    23,    24,    25,    33,    34,     0,    30,     0,    52,
       0,    32,     0,    35,    31
  };

  const signed char
  parser::yypgoto_[] =
  {
     -10,    75,   -10,     4,    41,    60,   -10,   -10,   -10,   -10,
      76,   -10,   -10,   -10,   -10,    12,   -10,   -10,    -3,    10,
     -10,   -10,    28
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    12,    13,     1,    14,    58,    15,    16,    17,    18,
      46,    19,    20,    21,    73,    86,    22,    23,    24,    25,
      26,    35,    56
  };

  const signed char
  parser::yytable_[] =
  {
      28,     3,    87,     4,    84,    31,    32,    43,    44,     3,
      54,     5,    33,     2,    34,    51,    88,    36,    29,     5,
      10,    27,     3,    85,     4,    39,    47,    47,    10,    27,
      53,    55,     5,     6,     7,     8,     3,     9,    60,    61,
      30,    10,    11,    41,    42,    40,     5,    65,    66,    67,
      68,    69,    70,    62,    63,    10,    27,    37,     3,    38,
       4,    57,    78,    79,    80,    81,    82,    83,     5,     6,
       7,     8,    55,     9,     3,    34,     4,    10,    11,    45,
      49,    50,    75,    72,     5,     6,     7,     8,    64,     9,
      71,    74,    76,    10,    11,    77,    90,    92,    91,    59,
      85,    94,    93,    89,     0,     0,    48,     0,    52
  };

  const signed char
  parser::yycheck_[] =
  {
       3,     9,    11,    11,    10,     8,     9,     5,     6,     9,
      10,    19,     7,     0,     9,    23,    25,    13,     9,    19,
      28,    29,     9,    29,    11,    21,    29,    30,    28,    29,
      33,    34,    19,    20,    21,    22,     9,    24,    41,    42,
       9,    28,    29,     3,     4,     8,    19,    13,    14,    15,
      16,    17,    18,    43,    44,    28,    29,    16,     9,    18,
      11,    12,    65,    66,    67,    68,    69,    70,    19,    20,
      21,    22,    75,    24,     9,     9,    11,    28,    29,    10,
       8,     8,    26,     9,    19,    20,    21,    22,    10,    24,
      10,     8,    10,    28,    29,     8,    26,    29,    10,    39,
      29,    11,    90,    75,    -1,    -1,    30,    -1,    33
  };

  const signed char
  parser::yystos_[] =
  {
       0,    37,     0,     9,    11,    19,    20,    21,    22,    24,
      28,    29,    35,    36,    38,    40,    41,    42,    43,    45,
      46,    47,    50,    51,    52,    53,    54,    29,    52,     9,
       9,    52,    52,     7,     9,    55,    37,    38,    38,    37,
       8,     3,     4,     5,     6,    10,    44,    52,    44,     8,
       8,    23,    35,    52,    10,    52,    56,    12,    39,    39,
      52,    52,    53,    53,    10,    13,    14,    15,    16,    17,
      18,    10,     9,    48,     8,    26,    10,     8,    52,    52,
      52,    52,    52,    52,    10,    29,    49,    11,    25,    56,
      26,    10,    29,    49,    11
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    34,    35,    35,    36,    37,    37,    38,    38,    38,
      38,    38,    38,    38,    38,    39,    40,    41,    42,    43,
      44,    44,    44,    44,    44,    44,    44,    45,    45,    46,
      47,    47,    48,    48,    49,    49,    50,    51,    52,    52,
      52,    53,    53,    53,    54,    54,    54,    54,    54,    55,
      55,    56,    56
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     3,     4,     1,     2,     0,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     2,     4,     2,     4,
       3,     3,     3,     3,     3,     3,     1,     4,     3,     3,
       5,     7,     3,     2,     1,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     1,     1,     2,     3,
       2,     1,     3
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   109,   109,   110,   114,   120,   121,   125,   126,   127,
     128,   129,   130,   131,   132,   136,   140,   149,   156,   165,
     172,   173,   174,   175,   176,   177,   178,   182,   188,   197,
     204,   210,   220,   221,   225,   230,   238,   242,   246,   247,
     248,   252,   253,   254,   258,   259,   260,   270,   271,   284,
     285,   289,   290
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
       2,     2,    32,    30,     2,    31,     2,    33,     2,     2,
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
      25,    26,    27,    28,    29
    };
    // Last valid token kind.
    const int code_max = 284;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 1719 "Build/lang.tab.cc"

#line 293 "Language/lang.y"


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
