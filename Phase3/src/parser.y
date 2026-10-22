// Copied in from Phase 2
/* ------------------------------- Part 1 ----------------------------------- */
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<../src/tree.h>
#include<../src/strtab.h>

extern char currFunction[256];

extern int yylineno;
extern int yylex(void);

int yywarning(char *msg);
int yyerror(char *msg);

int callArgDepth = 0;


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

#define TYPE_ERROR (-1)

static char current_function[256] = "";
static int pending_func_index = -1;
static int pending_param_count = 0;

static int in_local_scope(void){
    return current_function[0] != '\0';
}

static int is_same_scope_entry(symEntry *entry){
    if (!entry) { return 0; }
    if (!in_local_scope()) { return (entry->scope == NULL || entry->scope[0] == '\0'); }
    return (entry->scope != NULL && strcmp(entry->scope, current_function) == 0);
}

static int insert_decl(char *id, int data_type, int symbol_type){
  int scope_flag = in_local_scope() ? 1 : 0;
  symEntry *existing = ST_lookup(id);

  if(existing && strcmp(existing->id, id) == 0 && is_same_scope_entry(existing)){
    yyerror("Symbol declared multiple times.");
    return -1;
  }

  return ST_insert(id, data_type, symbol_type, &scope_flag);
}

static symEntry* lookup_var(char *id){
  symEntry *entry = ST_lookup(id);
  if (!entry){
    if(callArgDepth == 0){ yyerror("Undeclared variable."); } // editted from prev version due to extra undeclared variable calls when testing.
    return NULL;
  }
  return entry;
}

static symEntry* lookup_func(char *id){
  symEntry *entry = ST_lookup(id);
  if (!entry || entry->symbol_type != FUNCTION){
    yyerror("Undefined function.");
    return NULL;
  }
  return entry;
}

static int id_for_ast(symEntry *entry){ return entry ? 0 : -1; }

static int combine_arithmetic_type(int lhs, int rhs){
  if(lhs == TYPE_ERROR || rhs == TYPE_ERROR){ return TYPE_ERROR; }
  if(lhs == rhs && lhs != VOID_TYPE) { return lhs; }
  return TYPE_ERROR;
}
static void set_expr(tree *n, int type, int scope, int val){
  n->type = type;
  n->scope = scope;
  n->val = val;
}

static int validate_func_call(symEntry *fn, tree *args){
  if (!fn) { return TYPE_ERROR; }

  int numArgsGiven = (args == NULL) ? 0 : args->numChildren;
  
  if(numArgsGiven < fn->size){
    yyerror("Too few arguments provided in function call.");
    return fn->data_type;
  }
  if(numArgsGiven > fn->size){
    yyerror("Too many arguments provided in function call.");
    return fn->data_type;
  }

  param *parameters = fn->params;
  for(int i = 0; i < numArgsGiven && parameters != NULL; i++){
    tree *arg = getChild(args, i);
    if (arg->type == TYPE_ERROR || arg->type != parameters->data_type){
      yyerror("Argument type mismatch in function call.");
      break;
    }
    parameters = parameters->next;
  }
  return fn->data_type;
  
}

%}

/* ------------------------------- Part 2 ----------------------------------- */
/* the union describes the fields available in the yylval variable */
%union
{
    int value;
    struct treenode *node;
    char *strval;
}

%token <strval> ID
%token <value> INTCONST CHARCONST
%token KWD_INT KWD_CHAR KWD_VOID KWD_WHILE KWD_RETURN KWD_IF KWD_ELSE
%token LSQ_BRKT RSQ_BRKT LCRLY_BRKT RCRLY_BRKT LPAREN RPAREN
%token COMMA SEMICLN OPER_LTE OPER_LT OPER_DIV
%token OPER_GT OPER_GTE OPER_EQ OPER_ASGN OPER_NEQ OPER_ADD OPER_SUB OPER_MUL
%token ERROR ILLEGAL_TOK

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


/* ------------------------------- Part 3 ----------------------------------- */
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
                    int idx = insert_decl($2, $1->val, SCALAR);
                    addChild(varDeclNode, $1);
                    addChild(varDeclNode, maketreeWithVal(IDENTIFIER, idx));
                    $$ = varDeclNode;
                 }
                | typeSpecifier ID arrayDecl SEMICLN
                 {
                    tree *varDeclNode = maketree(VARDECL);
                    int idx = insert_decl($2, $1->val, ARRAY);

                    if($3->val == 0){ yyerror("Array variable declared with size of zero."); }

                    addChild(varDeclNode, $1);
                    addChild(varDeclNode, maketreeWithVal(IDENTIFIER, idx));
                    addChild(varDeclNode, $3);
                    $$ = varDeclNode;

                    symEntry *arr = ST_lookup($2);
                    if (arr && arr->symbol_type == ARRAY && is_same_scope_entry(arr)){
                      arr->size = $3->val;
                    }
                 }
                ;

funcTypeName    : typeSpecifier ID
                 {
                    int idx = insert_decl($2, $1->val, FUNCTION);

                    strncpy(current_function, $2, sizeof(current_function)-1);
                    current_function[sizeof(current_function)-1] = '\0';
                    strncpy(currFunction, current_function, sizeof(currFunction)-1);
                    currFunction[sizeof(currFunction)-1] = '\0';
                    scope = current_function;

                    pending_func_index = idx;
                    pending_param_count = 0;
                    working_list_head = NULL;
                    working_list_end = NULL;

                    new_scope();

                    $$ = maketree(FUNCTYPENAME);
                    addChild($$, $1);
                    addChild($$, maketreeWithVal(IDENTIFIER, idx));
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

                    connect_params(pending_func_index, 0);
                    up_scope();

                    current_function[0] = '\0';
                    currFunction[0] = '\0';
                    scope = "";

                    $$ = funDeclNode;
                 }
                | funcTypeName LPAREN formalDeclList RPAREN funBody
                 {
                    tree *funDeclNode = maketree(FUNDECL);
                    addChild(funDeclNode, $1);
                    addChild(funDeclNode, $3);
                    addChild(funDeclNode, $5);

                    connect_params(pending_func_index, pending_param_count);
                    up_scope();

                    current_function[0] = '\0';
                    currFunction[0] = '\0';
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
                    int idx = insert_decl($2, $1->val, SCALAR);
                    pending_param_count++;
                    add_param($1->val, SCALAR);

                    $$ = maketree(FORMALDECL);
                    addChild($$, $1);
                    addChild($$, maketreeWithVal(IDENTIFIER, idx));
                 }
                | typeSpecifier ID LSQ_BRKT RSQ_BRKT
                 {
                    int idx = insert_decl($2, $1->val, ARRAY);
                    pending_param_count++;
                    add_param($1->val, ARRAY);

                    $$ = maketree(FORMALDECL);
                    addChild($$, $1);
                    addChild($$, maketreeWithVal(IDENTIFIER, idx));
                 }
                ;

arrayDecl       : LSQ_BRKT INTCONST RSQ_BRKT
                 {
                    $$ = maketree(ARRAYDECL);
                    $$->val = $2;
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

                    if($1->type == TYPE_ERROR || $3->type == TYPE_ERROR || $1->type != $3->type){ yyerror("Type mismatch in assignment."); }
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
                    symEntry *entry = lookup_var($1);

                    $$ = maketree(VAR);
                    addChild($$, maketreeWithVal(IDENTIFIER, id_for_ast(entry)));

                    if(entry){
                      $$->type = entry->data_type;
                      $$->sym_type = entry->symbol_type;
                    }
                    else{
                      $$->type = TYPE_ERROR;
                      $$->sym_type = SCALAR;
                    }
                  }
                  | ID LSQ_BRKT addExpr RSQ_BRKT
                  {
                    symEntry *entry = lookup_var($1);

                    $$ = maketree(VAR);
                    addChild($$, maketreeWithVal(IDENTIFIER, id_for_ast(entry)));
                    addChild($$, $3);

                    if(!entry){ $$->type = TYPE_ERROR; $$->sym_type = SCALAR; }
                    else{
                      if(entry->symbol_type != ARRAY){ yyerror("Non-array identifier used as an array."); }
                      if($3->type != INT_TYPE){ yyerror("Array indexed using non-integer expression."); }
                      if(entry->symbol_type == ARRAY && entry->size > 0 && $3->scope == 1){
                        if($3->val < 0 || $3->val >= entry->size){ yyerror("Statically sized array indexed with constant, out-of-bounds expression."); }
                      }
                      $$->type = entry->data_type;
                      $$->sym_type = SCALAR;
                    }
                  }
                ;
   
expression     : addExpr
                  {
                    $$ = maketree(EXPRESSION);
                    addChild($$, $1);
                    set_expr($$, $1->type, $1->scope, $1->val);
                  }
                  | expression relop addExpr
                  {
                    $$ = maketree(EXPRESSION);
                    addChild($$, $1);
                    addChild($$, $2);
                    addChild($$, $3);

                    if($1->type == TYPE_ERROR || $3->type == TYPE_ERROR || $1->type == VOID_TYPE || $3->type == VOID_TYPE || $1->type != $3->type){
                      set_expr($$, TYPE_ERROR, 0, 0);
                    }
                    else{
                      set_expr($$, INT_TYPE, 0 ,0);
                    }
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
                    addChild($$, $1);
                    set_expr($$, $1->type, $1->scope, $1->val);
                  }
                  | addExpr addop term
                  { 
                    $$ = maketree(ADDEXPR);
                    addChild($$, $1);
                    addChild($$, $2);
                    addChild($$, $3);

                    int typ = combine_arithmetic_type($1->type, $3->type);
                    if(typ == TYPE_ERROR){ set_expr($$, TYPE_ERROR, 0, 0); }
                    else if($1->scope == 1 && $3->scope == 1){ 
                      int vl = ($2->val == ADD) ? ($1->val + $3->val) : ($1->val - $3->val); 
                      set_expr($$, typ, 1, vl);
                    }
                    else{ set_expr($$, typ, 0, 0); }
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
                    set_expr($$, $1->type, $1->scope, $1->val);
                  }
                  | term mulop factor
                  {
                    $$ = maketree(TERM);
                    addChild($$, $1);
                    addChild($$, $2);
                    addChild($$, $3);

                    int typ = combine_arithmetic_type($1->type, $3->type);
                    if(typ == TYPE_ERROR){ set_expr($$, TYPE_ERROR, 0, 0); }
                    else if($1->scope == 1 && $3->scope == 1){
                      if($2->val == MUL){ set_expr($$, typ, 1, $1->val * $3->val); }
                      else{
                        if($3->val == 0){ set_expr($$, typ, 0, 0); }
                        else { set_expr($$, typ, 1, $1->val / $3->val); }
                      }
                    }
                    else{ set_expr($$, typ, 0, 0);}
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
                    set_expr($$, $2->type, $2->scope, $2->val);
                  }
                  | var
                  {
                    $$ = maketree(FACTOR);
                    addChild($$, $1);
                    set_expr($$, $1->type, 0, 0);
                  }
                  | funCallExpr
                  {
                    $$ = maketree(FACTOR);
                    addChild($$, $1);
                    set_expr($$, $1->type, 0, 0);
                  }
                  | INTCONST 
                  {
                    $$ = maketree(FACTOR);
                    addChild($$, maketreeWithVal(INTEGER, $1));
                    set_expr($$, INT_TYPE, 1, $1);
                  }
                  | CHARCONST
                  {
                    $$ = maketree(FACTOR);
                    addChild($$, maketreeWithVal(CHAR, $1));
                    set_expr($$, CHAR_TYPE, 1, $1);
                  }
                ;
      
funCallExpr     : ID LPAREN { callArgDepth++; } argList RPAREN
                  {
                    callArgDepth--;

                    symEntry *fn = lookup_func($1);

                    $$ = maketree(FUNCCALLEXPR);
                    addChild($$, maketreeWithVal(IDENTIFIER, id_for_ast(fn)));
                    addChild($$, $4);

                    $$->type = validate_func_call(fn, $4);
                  }
                  | ID LPAREN { callArgDepth++; } RPAREN
                  {
                    callArgDepth--;
                    symEntry *fn = lookup_func($1);

                    $$ = maketree(FUNCCALLEXPR);
                    addChild($$, maketreeWithVal(IDENTIFIER, id_for_ast(fn)));

                    $$->type = validate_func_call(fn, NULL);
                  }
                ;
        
argList         : expression
                  {
                    $$ = maketree(ARGLIST);
                    addChild($$, $1);
                  }
                  | argList COMMA expression
                  {
                    $$ = $1;
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
