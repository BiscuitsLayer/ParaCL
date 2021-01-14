// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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


// First part of user declarations.

#line 37 "lang.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "lang.tab.hh"

// User implementation prologue.

#line 51 "lang.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 24 "../Language/lang.y" // lalr1.cc:413

	//	BISON AND FLEX
	#include "../Language/driver.hpp"

	//	LANGUAGE
	#include "../Language/Lang.hpp"

	namespace yy {

		parser::token_type yylex (parser::semantic_type* yylval, LangDriver* driver);

	}

	extern ScopeNodeInterface* globalCurrentScope;


#line 70 "lang.tab.cc" // lalr1.cc:413


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



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 137 "lang.tab.cc" // lalr1.cc:479

  /// Build a parser object.
  parser::parser (LangDriver* driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
      switch (other.type_get ())
    {
      case 31: // exprLvl1
      case 32: // exprLvl2
      case 33: // exprLvl3
      case 34: // assignment
      case 35: // syscall
      case 36: // condition
      case 37: // if_while
      case 38: // scope
      case 39: // inside_scope
        value.copy< NodeInterface* > (other.value);
        break;

      case 24: // NUMBER
        value.copy< double > (other.value);
        break;

      case 25: // VARIABLE
        value.copy< std::string* > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value ()
  {
    (void) v;
      switch (this->type_get ())
    {
      case 31: // exprLvl1
      case 32: // exprLvl2
      case 33: // exprLvl3
      case 34: // assignment
      case 35: // syscall
      case 36: // condition
      case 37: // if_while
      case 38: // scope
      case 39: // inside_scope
        value.copy< NodeInterface* > (v);
        break;

      case 24: // NUMBER
        value.copy< double > (v);
        break;

      case 25: // VARIABLE
        value.copy< std::string* > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const NodeInterface* v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const double v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string* v)
    : Base (t)
    , value (v)
  {}


  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 31: // exprLvl1
      case 32: // exprLvl2
      case 33: // exprLvl3
      case 34: // assignment
      case 35: // syscall
      case 36: // condition
      case 37: // if_while
      case 38: // scope
      case 39: // inside_scope
        value.template destroy< NodeInterface* > ();
        break;

      case 24: // NUMBER
        value.template destroy< double > ();
        break;

      case 25: // VARIABLE
        value.template destroy< std::string* > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 31: // exprLvl1
      case 32: // exprLvl2
      case 33: // exprLvl3
      case 34: // assignment
      case 35: // syscall
      case 36: // condition
      case 37: // if_while
      case 38: // scope
      case 39: // inside_scope
        value.move< NodeInterface* > (s.value);
        break;

      case 24: // NUMBER
        value.move< double > (s.value);
        break;

      case 25: // VARIABLE
        value.move< std::string* > (s.value);
        break;

      default:
        break;
    }

  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }
  // Implementation of make_symbol for each symbol type.
  parser::symbol_type
  parser::make_ADD ()
  {
    return symbol_type (token::ADD);
  }

  parser::symbol_type
  parser::make_SUB ()
  {
    return symbol_type (token::SUB);
  }

  parser::symbol_type
  parser::make_MUL ()
  {
    return symbol_type (token::MUL);
  }

  parser::symbol_type
  parser::make_DIV ()
  {
    return symbol_type (token::DIV);
  }

  parser::symbol_type
  parser::make_ASSIGN ()
  {
    return symbol_type (token::ASSIGN);
  }

  parser::symbol_type
  parser::make_SCOLON ()
  {
    return symbol_type (token::SCOLON);
  }

  parser::symbol_type
  parser::make_LPARENTHESES ()
  {
    return symbol_type (token::LPARENTHESES);
  }

  parser::symbol_type
  parser::make_RPARENTHESES ()
  {
    return symbol_type (token::RPARENTHESES);
  }

  parser::symbol_type
  parser::make_LBRACE ()
  {
    return symbol_type (token::LBRACE);
  }

  parser::symbol_type
  parser::make_RBRACE ()
  {
    return symbol_type (token::RBRACE);
  }

  parser::symbol_type
  parser::make_GREATER ()
  {
    return symbol_type (token::GREATER);
  }

  parser::symbol_type
  parser::make_GREATER_OR_EQ ()
  {
    return symbol_type (token::GREATER_OR_EQ);
  }

  parser::symbol_type
  parser::make_LESS ()
  {
    return symbol_type (token::LESS);
  }

  parser::symbol_type
  parser::make_LESS_OR_EQ ()
  {
    return symbol_type (token::LESS_OR_EQ);
  }

  parser::symbol_type
  parser::make_EQ ()
  {
    return symbol_type (token::EQ);
  }

  parser::symbol_type
  parser::make_NOT_EQ ()
  {
    return symbol_type (token::NOT_EQ);
  }

  parser::symbol_type
  parser::make_QMARK ()
  {
    return symbol_type (token::QMARK);
  }

  parser::symbol_type
  parser::make_IF ()
  {
    return symbol_type (token::IF);
  }

  parser::symbol_type
  parser::make_WHILE ()
  {
    return symbol_type (token::WHILE);
  }

  parser::symbol_type
  parser::make_PRINT ()
  {
    return symbol_type (token::PRINT);
  }

  parser::symbol_type
  parser::make_ERROR ()
  {
    return symbol_type (token::ERROR);
  }

  parser::symbol_type
  parser::make_NUMBER (const double& v)
  {
    return symbol_type (token::NUMBER, v);
  }

  parser::symbol_type
  parser::make_VARIABLE (const std::string*& v)
  {
    return symbol_type (token::VARIABLE, v);
  }



  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
      switch (that.type_get ())
    {
      case 31: // exprLvl1
      case 32: // exprLvl2
      case 33: // exprLvl3
      case 34: // assignment
      case 35: // syscall
      case 36: // condition
      case 37: // if_while
      case 38: // scope
      case 39: // inside_scope
        value.move< NodeInterface* > (that.value);
        break;

      case 24: // NUMBER
        value.move< double > (that.value);
        break;

      case 25: // VARIABLE
        value.move< std::string* > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 31: // exprLvl1
      case 32: // exprLvl2
      case 33: // exprLvl3
      case 34: // assignment
      case 35: // syscall
      case 36: // condition
      case 37: // if_while
      case 38: // scope
      case 39: // inside_scope
        value.copy< NodeInterface* > (that.value);
        break;

      case 24: // NUMBER
        value.copy< double > (that.value);
        break;

      case 25: // VARIABLE
        value.copy< std::string* > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
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

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, driver));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 31: // exprLvl1
      case 32: // exprLvl2
      case 33: // exprLvl3
      case 34: // assignment
      case 35: // syscall
      case 36: // condition
      case 37: // if_while
      case 38: // scope
      case 39: // inside_scope
        yylhs.value.build< NodeInterface* > ();
        break;

      case 24: // NUMBER
        yylhs.value.build< double > ();
        break;

      case 25: // VARIABLE
        yylhs.value.build< std::string* > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 89 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = globalCurrentScope; globalCurrentScope->Return (); }
#line 902 "lang.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 93 "../Language/lang.y" // lalr1.cc:859
    { 
											ScopeNodeInterface* next = ScopeNodeInterface::CreateScopeNode (globalCurrentScope);
											globalCurrentScope->Entry (next);
										}
#line 911 "lang.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 100 "../Language/lang.y" // lalr1.cc:859
    { globalCurrentScope->AddNode (yystack_[1].value.as< NodeInterface* > ()); }
#line 917 "lang.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 101 "../Language/lang.y" // lalr1.cc:859
    { globalCurrentScope->AddNode (yystack_[1].value.as< NodeInterface* > ()); }
#line 923 "lang.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 102 "../Language/lang.y" // lalr1.cc:859
    { globalCurrentScope->AddNode (yystack_[0].value.as< NodeInterface* > ()); }
#line 929 "lang.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 103 "../Language/lang.y" // lalr1.cc:859
    { /* empty */ }
#line 935 "lang.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 107 "../Language/lang.y" // lalr1.cc:859
    { /* empty */ }
#line 941 "lang.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 111 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateIfNode (yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 947 "lang.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 112 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateWhileNode (yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 953 "lang.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 116 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_GREATER, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 959 "lang.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 117 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_GREATER_OR_EQ, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 965 "lang.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 118 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_LESS, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 971 "lang.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 119 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_LESS_OR_EQ, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 977 "lang.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 120 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_EQ, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 983 "lang.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 121 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_NOT_EQ, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 989 "lang.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 125 "../Language/lang.y" // lalr1.cc:859
    { 	
									//	ADD VARIABLE
									globalCurrentScope->SetVariable (*(yystack_[2].value.as< std::string* > ()), 0.0);

									NodeInterface* left = NodeInterface::CreateVariableNode (*(yystack_[2].value.as< std::string* > ()));
									delete yystack_[2].value.as< std::string* > ();
								  	yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, yystack_[0].value.as< NodeInterface* > ());
								}
#line 1002 "lang.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 136 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreatePrintNode (yystack_[0].value.as< NodeInterface* > ()); }
#line 1008 "lang.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 137 "../Language/lang.y" // lalr1.cc:859
    { 	
									//	ADD VARIABLE
									globalCurrentScope->SetVariable (*(yystack_[2].value.as< std::string* > ()), 0.0);

									NodeInterface* left = NodeInterface::CreateVariableNode (*(yystack_[2].value.as< std::string* > ()));
									delete yystack_[2].value.as< std::string* > ();
									NodeInterface* right = NodeInterface::CreateScanNode (); 
								  	yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ASSIGN, left, right);
								}
#line 1022 "lang.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 149 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_ADD, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 1028 "lang.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 150 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_SUB, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 1034 "lang.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 151 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = yystack_[0].value.as< NodeInterface* > (); }
#line 1040 "lang.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 155 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_MUL, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 1046 "lang.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 156 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateBinaryOpNode (NodeType::BINARY_OP_DIV, yystack_[2].value.as< NodeInterface* > (), yystack_[0].value.as< NodeInterface* > ()); }
#line 1052 "lang.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 157 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = yystack_[0].value.as< NodeInterface* > (); }
#line 1058 "lang.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 161 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = yystack_[1].value.as< NodeInterface* > (); }
#line 1064 "lang.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 162 "../Language/lang.y" // lalr1.cc:859
    { yylhs.value.as< NodeInterface* > () = NodeInterface::CreateValueNode (yystack_[0].value.as< double > ()); }
#line 1070 "lang.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 163 "../Language/lang.y" // lalr1.cc:859
    { 	
											//	CHECK IF VARIABLE IS VISIBLE
											globalCurrentScope->GetVariable (*(yystack_[0].value.as< std::string* > ()));

											yylhs.value.as< NodeInterface* > () = NodeInterface::CreateVariableNode (*(yystack_[0].value.as< std::string* > ()));
											delete yystack_[0].value.as< std::string* > (); 
										}
#line 1082 "lang.tab.cc" // lalr1.cc:859
    break;


#line 1086 "lang.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -14;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
     -14,    12,   -14,    -7,    -3,    -6,    15,     2,    16,   -14,
      -6,    -6,    -6,   -14,   -14,   -14,     1,     3,    -8,   -14,
     -14,    36,    13,    26,    28,    -6,    -6,    -6,    -6,   -14,
     -14,    -6,    -6,    -6,    -6,    -6,    -6,    14,    14,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,    23,   -14,   -14
  };

  const unsigned char
  parser::yydefact_[] =
  {
       7,     0,     1,     0,     0,     0,     0,     0,     0,     6,
       0,     0,     0,    27,    28,    18,    22,    25,     0,     4,
       5,     0,     0,     0,     0,     0,     0,     0,     0,    19,
      17,     0,     0,     0,     0,     0,     0,     0,     0,    26,
      20,    21,    23,    24,    11,    12,    13,    14,    15,    16,
       3,     9,     7,    10,     0,     8,     2
  };

  const signed char
  parser::yypgoto_[] =
  {
     -14,    -5,   -13,   -14,   -14,   -14,    29,   -14,     4,   -11,
     -14,   -14
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    21,    16,    17,     7,     8,    22,     9,    51,     1,
      52,    56
  };

  const unsigned char
  parser::yytable_[] =
  {
      15,    12,    10,    12,    25,    26,    11,    24,    27,    28,
      19,    29,     2,    30,    42,    43,    13,    14,    13,    14,
      40,    41,    18,    37,    20,    50,    44,    45,    46,    47,
      48,    49,     3,     4,     5,    55,    38,     6,    39,     0,
      23,    54,    53,     3,     4,     5,     0,     0,     6,    31,
      32,    33,    34,    35,    36
  };

  const signed char
  parser::yycheck_[] =
  {
       5,     9,     9,     9,     3,     4,     9,    12,     5,     6,
       8,    19,     0,    18,    27,    28,    24,    25,    24,    25,
      25,    26,     7,    10,     8,    11,    31,    32,    33,    34,
      35,    36,    20,    21,    22,    12,    10,    25,    10,    -1,
      11,    52,    38,    20,    21,    22,    -1,    -1,    25,    13,
      14,    15,    16,    17,    18
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    39,     0,    20,    21,    22,    25,    34,    35,    37,
       9,     9,     9,    24,    25,    31,    32,    33,     7,     8,
       8,    31,    36,    36,    31,     3,     4,     5,     6,    19,
      31,    13,    14,    15,    16,    17,    18,    10,    10,    10,
      31,    31,    32,    32,    31,    31,    31,    31,    31,    31,
      11,    38,    40,    38,    39,    12,    41
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    30,    38,    40,    39,    39,    39,    39,    41,    37,
      37,    36,    36,    36,    36,    36,    36,    34,    35,    35,
      31,    31,    31,    32,    32,    32,    33,    33,    33
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     3,     1,     3,     3,     2,     0,     1,     5,
       5,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "\"+\"", "\"-\"", "\"*\"", "\"/\"",
  "\"=\"", "\";\"", "\"(\"", "\")\"", "\"{\"", "\"}\"", "\">\"", "\">=\"",
  "\"<\"", "\"<=\"", "\"==\"", "\"!=\"", "\"?\"", "\"if\"", "\"while\"",
  "\"print\"", "ERROR", "NUMBER", "VARIABLE", "'+'", "'-'", "'*'", "'/'",
  "$accept", "exprLvl1", "exprLvl2", "exprLvl3", "assignment", "syscall",
  "condition", "if_while", "scope", "inside_scope", "scope_entry",
  "scope_outro", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    89,    89,    93,   100,   101,   102,   103,   107,   111,
     112,   116,   117,   118,   119,   120,   121,   125,   136,   137,
     149,   150,   151,   155,   156,   157,   161,   162,   163
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    28,    26,     2,    27,     2,    29,     2,     2,
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
      25
    };
    const unsigned int user_token_number_max_ = 280;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1442 "lang.tab.cc" // lalr1.cc:1167
#line 172 "../Language/lang.y" // lalr1.cc:1168


namespace yy {

	parser::token_type yylex (parser::semantic_type* yylval, LangDriver* driver) {
		return driver->yylex (yylval);
	}

	void parser::error (const std::string&) {}

}
