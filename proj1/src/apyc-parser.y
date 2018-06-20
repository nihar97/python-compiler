/* -*- mode: fundamental; c-file-style: "stroustrup"; indent-tabs-mode: nil -*- */

/* apyc: Bison Parser */

/* Authors: YOUR NAMES HERE */

%{
  #include <iostream>
  #include <string>
  #include "apyc.h"
  #include "ast.h"

  using namespace std;

  static AST_Ptr theTree;

  /* Utilities */

  /** Type used for locations (@1, @2, etc.). */
  #define YYLTYPE Location

  #define YYLLOC_DEFAULT(Current, Rhs, N)                                    \
      do  {                                                                  \
         if (N) {                                                            \
             Current = YYRHSLOC(Rhs, 1);                                     \
         } else {                                                            \
             Current = YYRHSLOC(Rhs, 0);                                     \
         }                                                                   \
      } while (0)                                                            \

  static void yyerror (const char* s);

  static int yylex ();

%}

%locations
%debug

/* A token declaration such as
 *   %token INDENT
 * declares a new integer constant INDENT, which serves as a syntactic category
 * (suitable for output by the lexer) identifying a kind of token, which we
 * also often refer to as INDENT. A declaration such as
 *   %token IF "if"
 * defines a constant IF and makes it the syntactic category for the token
 * "if".  The built-in function yyexternal_token_name(...) maps between 
 * syntactic categories (like IF) and the token strings defined in these 
 * %token declarations (like "if").  
 *
 */

/* Lexer tokens and nonterminal instances that are referred to by $$, $1,
 * $2, etc. have a semantic value, whose type is declared by the <...>
 * notations in %token and %type declarations.  The names in
 * the <...> brackets refer to members of the %union declaration (see below).
 * Symbols whose semantic value is never referenced do not need types.
 */ 
%token<str> ID STRING INT

%token NEWLINE INDENT DEDENT
%token EXP

%token PRINT "print"
%token AND "and"
%token BREAK "break"
%token CLASS "class"
%token CONTINUE "continue"
%token DEF "def"
%token ELIF "elif"
%token ELSE "else"
%token FOR "for"
%token IF "if"
%token IN "in"
%token IS "is"
%token NOT "not"
%token OR "or"
%token PASS "pass"
%token RETURN "return"
%token WHILE "while"


%type<ast> print_stmt expression string_literal atom pair
%type<astVect> expression_list expression_list1 stmt_list pair_list1 pair_list

/* The following declaration provides names for possible semantic types
 * passed by the compiler.  It actually translates to a C++ union type.
 * This is like a class, but its fields are mutually exclusive.  For
 * technical reasons, all these types must be "POD (Plain Old Data) types";
 * they can't have constructors or other fancy C++ features.  Therefore,
 * they are all numeric types or pointer types. */

%union {
    std::string* str;
    AST_Ptr ast;
    AST_Vect* astVect;
}

/* GLR parsing is useful for cases where the parser must make a reduction before
 * it has sufficient information to know which reduction to make.  For example,
 * consider a statement that begins
 *      a[i], b[j], c
 * (it's not useful, but is valid Python as it stands).  As a tuple, this 
 * consists of a list of expressions.  a[i] is a subscription, and corresponds
 * to a (subscript ...) AST.  But if we have
 *      a[i], b[j], c = L
 * then the a[i] should create a subscript_assign.  If you try to handle this
 * by having two rules for subscription, one for the first case and one 
 * for the second, the parser has to decide which to choose just after 
 * seeing a[i], but long before seeing "=", which is how one tells which
 * translation is appropriate.  A GLR parser will hold off on this decision
 * until is reaches the =. */

%glr-parser

/* If you use the GLR features, Bison will report conflicts.  Without GLR,
 * a conflict generally means an error.  With GLR, it could mean an error,
 * or it could indicate conflicts that the GLR algorithm will correctly resolve.
 * There's really no way to know without testing.  When you get conflicts
 * THAT YOU EXPECT you can record here these expectations by reporting how
 * many reduce/reduce (%expect-rr) and shift-reduce (%expect) you expect. 
 * Before increasing these counts, make sure you understand what causes your
 * conflicts and that GLR will resolve them.  Don't expect too many
 * and try to remove conflicts rather than tolerating them.
 * A conflict will occur when there is a situation where Bison cannot decide
 * on the basis of the input so far whether to perform a reduction.  The 
 * conflict is OK if it will become clear later on in the input what should
 * have been done. */
%expect-rr 0
%expect 0

%%

/* See the ast.h file for declarations of NODE and LEAF.  NODE is for
 * creating AST nodes that have 0 or more children and no string content,
 * while LEAF is for creating childless nodes whose principal semantic
 * content is a string or integer value. */

program : stmt_list   { theTree = NODE (MODULE_AST, $1); }
        ;

// REPLACE THE FOLLOWING WITH SOMETHING REAL.  (These are incomplete examples.)

stmt_list :
      print_stmt NEWLINE { $$ = new AST_Vect(1, $1); }
    | stmt_list print_stmt NEWLINE { $$ = $1; $$->push_back($2); }
    ;

print_stmt : "print" expression_list 
			{ $$ = NODE (PRINTLN_AST, $2); $$->setLoc(@1); }
    ;

expression_list :
                expression_list1
                | expression_list1 ',' { $$ = $1; }
                | /*empty*/         { $$ = new AST_Vect(); }
                ;

expression_list1 :
      expression        { $$ = new AST_Vect(1, $1); }
    | expression_list1 ',' expression
                        { $$ = $1; $$->push_back($3); }
    ;

expression :
           atom
           ;

atom :
     INT               { $$ = LEAF(INT_LITERAL_AST, *$1, @1); }
     | string_literal
     | '(' expression_list ')'
         { if($2->size() == 1) $$ = (*$2)[0];
           else $$ = NODE(TUPLE_AST, $2); }
     | '[' expression_list ']'
         { $$ = NODE(LIST_DISPLAY_AST, $2); }
     | '{' pair_list '}'
         { $$ = NODE(DICT_DISPLAY_AST, $2); }
     ;

pair :
     expression ':' expression { $$ = NODE(PAIR_AST, $1, $3); }
     ;

pair_list1 :
           pair { $$ = new AST_Vect(1, $1); }
           | pair_list1 ',' pair { $$ = $1; $$->push_back($3); }
           ;

pair_list :
          pair_list1
          | pair_list1 ',' { $$ = $1; }
          | /*empty*/ { $$ = new AST_Vect(); }
          ;

string_literal :
      STRING    	{ $$ = LEAF(STRING_LITERAL_AST, *$1, @1); }
                        // FIXME (doesn't do "foo" "bar")
    ;

%%

bool debugParser;

#include "apyc-lexer.cc"

void
parse (FILE* f, const string& name)
{
    if (debugParser)
        yydebug = 1;
    initLexer (name);
    theTree = NULL;
    yyparse ();
    if (theTree != NULL) {
        theTree->print (cout, 0);
    }
}

static void
yyerror (const char* s)
{
    error (currentLocation (), s);
}
