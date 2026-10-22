/* ------------------------------- Part 1 ----------------------------------- */
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<../src/tree.h>
#include<../src/strtab.h>

extern int yylineno;
extern int yylex(void);

int yywarning(char *msg);
int yyerror(char *msg);


typedef struct treenode tree;
extern tree *ast;

/* nodeTypes refer to different types of internal and external nodes
  that can be part of the abstract syntax tree.
  */
enum nodeTypes {PROGRAM, DECLLIST, DECL, VARDECL, TYPESPEC, FUNDECL,
                FORMALDECLLIST, FORMALDECL, FUNBODY, LOCALDECLLIST,
                STATEMENTLIST, STATEMENT, COMPOUNDSTMT, ASSIGNSTMT,
                CONDSTMT, LOOPSTMT, RETURNSTMT, EXPRESSION, RELOP,
                ADDEXPR, ADDOP, TERM, MULOP, FACTOR, FUNCCALLEXPR,
                ARGLIST, INTEGER, IDENTIFIER, VAR, ARRAYDECL, CHAR,
                FUNCTYPENAME};

enum opType {ADD, SUB, MUL, DIV, LT, LTE, EQ, GTE, GT, NEQ};

/* NOTE: mC has two kinds of scopes for variables : local and global.
  Variables declared outside any function are considered globals,
    whereas variables (and parameters) declared inside a function foo
    are local to foo.
  You should update the scope variable whenever you are inside a production
    that matches function definition (funDecl production).
  The rationale is that you are entering that function, so all variables,
    arrays, and other functions should be within this scope.
  You should pass this variable whenever you are
    calling the ST_insert or ST_lookup functions.
  This variable should be updated to scope = ""
    to indicate global scope whenever funDecl finishes.
  Treat these hints as helpful directions only.
  You may implement all of the functions as you like
    and not adhere to my instructions.
  As long as the directory structure is correct and the file names are correct,
    we are okay with it.
  */
char* scope = "";
%}

/* ------------------------------- Part 2 ----------------------------------- /*
/* the union describes the fields available in the yylval variable */
%union
{
    int value;
    struct treenode *node;
    char *strval;
}

%token <strval> ID STRCONST
%token <value> INTCONST CHARCONST
%token KWD_INT KWD_CHAR KWD_VOID KWD_WHILE KWD_RETURN KWD_IF KWD_ELSE KWD_STRING
%token LSQ_BRKT RSQ_BRKT LCRLY_BRKT RCRLY_BRKT LPAREN RPAREN
%token COMMA SEMICLN OPER_LTE OPER_LT OPER_DIV
%token OPER_GT OPER_GTE OPER_EQ OPER_ASGN OPER_NEQ OPER_ADD OPER_SUB OPER_MUL

/* split type nodes for readability */
%type <node> program declList decl varDecl funDecl typeSpecifier funcTypeName 
%type <node> formalDeclList formalDecl funBody arrayDecl localDeclList
%type <node> statementList statement compoundStmt assignStmt var
%type <node> expression condStmt loopStmt returnStmt addExpr relop addop term
%type <node> funCallExpr argList mulop factor


/* https://stackoverflow.com/questions/6894826/ */
%nonassoc LOWER_THAN_ELSE
%nonassoc KWD_ELSE

%start program


/* ------------------------------- Part 3 ----------------------------------- /*
/* Grammar and semantic actions  */

/* Notes to myself to understand. LS name : name {maketree = (CAPITALNAME);}
you do addChild($$, $_) when there are multiple things in the name section that
needs to be connected to the node, you determine # by counting out its placement
*/

%%
program         : declList
                 {
                    tree *progNode = maketree(PROGRAM);
                    addChild(progNode, $1);
                    $$ = progNode;
                    ast = progNode;
                 }
                ;

declList        : decl
                 {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, $1);
                    $$ = declListNode;
                 }
                | declList decl
                 {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, $1);
                    addChild(declListNode, $2);
                    $$ = declListNode;
                 }
                ;

decl            : varDecl
                 {
                    $$ = maketree(DECL);
                    addChild($$, $1);
                 }
                | funDecl
                 {
                    $$ = maketree(DECL);
                    addChild($$, $1);
                 }
                ;

varDecl         : typeSpecifier ID SEMICLN
                 {
                    tree *varDeclNode = maketree(VARDECL);
                    addChild(varDeclNode, $1);
                    addChild(varDeclNode, maketreeWithVal(IDENTIFIER, ST_insert($2, scope, $1->val, SCALAR)));
                    $$ = varDeclNode;
                 }
                | typeSpecifier ID arrayDecl SEMICLN
                 {
                    tree *varDeclNode = maketree(VARDECL);
                    addChild(varDeclNode, $1);
                    addChild(varDeclNode, maketreeWithVal(IDENTIFIER, ST_insert($2, scope, $1->val, ARRAY)));
                    addChild(varDeclNode, $3);
                    $$ = varDeclNode;
                 }
                ;

funcTypeName    : typeSpecifier ID
                 {
                    scope = strdup($2);
                    $$ = maketree(FUNCTYPENAME);
                    addChild($$, $1);
                    addChild($$, maketreeWithVal(IDENTIFIER, ST_insert($2, "", $1->val, FUNCTION)));
                 }
                ;

typeSpecifier   : KWD_INT
                 {
                    $$ = maketreeWithVal(TYPESPEC, INT_TYPE);
                 }
                | KWD_CHAR
                 {
                    $$ = maketreeWithVal(TYPESPEC, CHAR_TYPE);
                 }
                | KWD_VOID
                 {
                    $$ = maketreeWithVal(TYPESPEC, VOID_TYPE);
                 }
                ;

funDecl         : funcTypeName LPAREN RPAREN funBody
                 {
                    tree *funDeclNode = maketree(FUNDECL);
                    addChild(funDeclNode, $1);
                    addChild(funDeclNode, $4);
                    scope = "";
                    $$ = funDeclNode;
                 }
                | funcTypeName LPAREN formalDeclList RPAREN funBody
                 {
                    tree *funDeclNode = maketree(FUNDECL);
                    addChild(funDeclNode, $1);
                    addChild(funDeclNode, $3);
                    addChild(funDeclNode, $5);
                    scope = "";
                    $$ = funDeclNode;
                 }
                ;

formalDeclList  : formalDecl
                 {
                    $$ = maketree(FORMALDECLLIST);
                    addChild($$, $1);
                 }
                | formalDeclList COMMA formalDecl
                 {
                    $$ = maketree(FORMALDECLLIST);
                    addChild($$, $1);
                    addChild($$, $3);
                 }
                ;

formalDecl      : typeSpecifier ID
                 {
                    $$ = maketree(FORMALDECL);
                    addChild($$, $1);
                    addChild($$, maketreeWithVal(IDENTIFIER, ST_insert($2, scope, $1->val, SCALAR)));
                 }
                | typeSpecifier ID LSQ_BRKT RSQ_BRKT
                 {
                    $$ = maketree(FORMALDECL);
                    addChild($$, $1);
                    addChild($$, maketreeWithVal(IDENTIFIER, ST_insert($2, scope, $1->val, ARRAY)));
                 }
                ;

arrayDecl       : LSQ_BRKT INTCONST RSQ_BRKT
                 {
                    $$ = maketree(ARRAYDECL);
                    addChild($$, maketreeWithVal(INTEGER, $2));
                 }
                ;
  
funBody         : LCRLY_BRKT localDeclList statementList RCRLY_BRKT
                 {
                    $$ = maketree(FUNBODY);
                    addChild($$, $2);
                    addChild($$, $3);
                 }
                ;

localDeclList   : /* empty ε */ 
                  {
                    $$ = maketree(LOCALDECLLIST);
                  }
                  | varDecl localDeclList
                  {
                    $$ = maketree(LOCALDECLLIST);
                    addChild($$, $1);
                    addChild($$, $2);
                  }
                ;

statementList   : /* empty ε */
                  {
                    $$ = maketree(STATEMENTLIST);
                  }
                  | statement statementList
                  {
                    $$ = maketree(STATEMENTLIST);
                    addChild($$, $1);
                    addChild($$, $2);
                  }
                ;

statement       : compoundStmt
                  {
                    $$ = maketree(STATEMENT);
                    addChild($$, $1);
                  }
                  | assignStmt
                  {
                    $$ = maketree(STATEMENT);
                    addChild($$, $1);
                  }
                  | condStmt
                  {
                    $$ = maketree(STATEMENT);
                    addChild($$, $1);
                  }
                  | loopStmt
                  {
                    $$ = maketree(STATEMENT);
                    addChild($$, $1);
                  }
                  | returnStmt
                  {
                    $$ = maketree(STATEMENT);
                    addChild($$, $1);
                  }
                  | expression SEMICLN
                  {
                    $$ = maketree(STATEMENT);
                    addChild($$, $1);
                  }
                ;

compoundStmt    : LCRLY_BRKT statementList RCRLY_BRKT
                  {
                    $$ = maketree(COMPOUNDSTMT);
                    addChild($$, $2);
                  }
                ;

assignStmt      : var OPER_ASGN expression SEMICLN
                  {
                    $$ = maketree(ASSIGNSTMT);
                    addChild($$, $1);
                    addChild($$, $3);
                  }
                ;
                
condStmt        : KWD_IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
                  {
                    $$ = maketree(CONDSTMT);
                    addChild($$, $3);
                    addChild($$, $5);
                  }
                  | KWD_IF LPAREN expression RPAREN statement KWD_ELSE statement
                  {
                    $$ = maketree(CONDSTMT);
                    addChild($$, $3);
                    addChild($$, $5);
                    addChild($$, $7);
                  }
                ;

loopStmt        : KWD_WHILE LPAREN expression RPAREN statement
                  {
                    $$ = maketree(LOOPSTMT);
                    addChild($$, $3);
                    addChild($$, $5);
                  }
                ;

returnStmt      : KWD_RETURN SEMICLN
                  {
                    $$ = maketree(RETURNSTMT);
                  }
                  | KWD_RETURN expression SEMICLN
                  {
                    $$ = maketree(RETURNSTMT);
                    addChild($$, $2);
                  }
                ;

var             : ID
                  {
                    $$ = maketree(VAR);
                    addChild($$, maketreeWithVal(IDENTIFIER, ST_lookup($1, scope)));
                  }
                  | ID LSQ_BRKT addExpr RSQ_BRKT
                  {
                    $$ = maketree(VAR);
                    addChild($$, maketreeWithVal(IDENTIFIER, ST_lookup($1, scope)));
                    addChild($$, $3);
                  }
                ;
   
expression     : addExpr
                  {
                    $$ = maketree(EXPRESSION);
                    addChild($$, $1);
                  }
                  | expression relop addExpr
                  {
                    $$ = maketree(EXPRESSION);
                    addChild($$, $1);
                    addChild($$, $2);
                    addChild($$, $3);
                  }
                ;

relop           : OPER_LTE
                  {
                    $$ = maketreeWithVal(RELOP, LTE);
                  }
                  | OPER_LT
                  {
                    $$ = maketreeWithVal(RELOP, LT);
                  }
                  | OPER_GT
                  {
                    $$ = maketreeWithVal(RELOP, GT);
                  }
                  | OPER_GTE 
                  {
                    $$ = maketreeWithVal(RELOP, GTE);
                  }
                  | OPER_EQ
                  {
                    $$ = maketreeWithVal(RELOP, EQ);
                  }
                  | OPER_NEQ
                  {
                    $$ = maketreeWithVal(RELOP, NEQ);
                  }
                ;

addExpr         : term
                  {
                    $$ = maketree(ADDEXPR);
                    addChild($$ ,$1);
                  }
                  | addExpr addop term
                  { 
                    $$ = maketree(ADDEXPR);
                    addChild($$, $1);
                    addChild($$, $2);
                    addChild($$, $3);
                  }
                ;
   
addop           : OPER_ADD
                  {
                    $$ = maketreeWithVal(ADDOP, ADD);
                  }
                  | OPER_SUB
                  {
                    $$ = maketreeWithVal(ADDOP, SUB);
                  }
                ;

term            : factor
                  {
                    $$ = maketree(TERM);
                    addChild($$, $1);
                  }
                  | term mulop factor
                  {
                    $$ = maketree(TERM);
                    addChild($$, $1);
                    addChild($$, $2);
                    addChild($$, $3);
                  }
                ;
   
mulop           : OPER_MUL
                  {
                    $$ = maketreeWithVal(MULOP, MUL);
                  }
                  | OPER_DIV
                  {
                    $$ = maketreeWithVal(MULOP, DIV);
                  }
                ;
   
factor          : LPAREN expression RPAREN
                  {
                    $$ = maketree(FACTOR);
                    addChild($$, $2);
                  }
                  | var
                  {
                    $$ = maketree(FACTOR);
                    addChild($$, $1);
                  }
                  | funCallExpr
                  {
                    $$ = maketree(FACTOR);
                    addChild($$, $1);
                  }
                  | INTCONST 
                  {
                    $$ = maketree(FACTOR);
                    addChild($$, maketreeWithVal(INTEGER, $1));
                  }
                  | CHARCONST
                  {
                    $$ = maketree(FACTOR);
                    addChild($$, maketreeWithVal(CHAR, $1));
                  }
                /* TODO: /*
                /*  | STRCONST{$$ = maketree(FACTOR);addChild($$, maketreeWithVal(STRING, $1));} */
                ;
      
funCallExpr     : ID LPAREN argList RPAREN
                  {
                    $$ = maketree(FUNCCALLEXPR);
                    addChild($$, maketreeWithVal(IDENTIFIER, ST_lookup($1, scope)));
                    addChild($$, $3);
                  }
                  | ID LPAREN RPAREN
                  {
                    $$ = maketree(FUNCCALLEXPR);
                    addChild($$, maketreeWithVal(IDENTIFIER, ST_lookup($1, scope)));
                  }
                ;
        
argList         : expression
                  {
                    $$ = maketree(ARGLIST);
                    addChild($$, $1);
                  }
                  | argList COMMA expression
                  {
                    $$ = maketree(ARGLIST);
                    addChild($$, $1);
                    addChild($$, $3);
                  }
                ;

%% 
int yywarning(char *msg){
  printf("warning: line %d: %s\n", yylineno, msg);
  return 0;
}

int yyerror(char * msg){
  printf("error: line %d: %s\n", yylineno, msg);
  return 0;
}
