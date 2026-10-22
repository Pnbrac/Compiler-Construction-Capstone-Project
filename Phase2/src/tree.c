#include<tree.h>
#include<strtab.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct treenode tree;

// the root of the ast
tree *ast;

extern struct strEntry strTable[MAXIDS];

// NodeKinds
enum {
  NK_PROGRAM, NK_DECLLIST, NK_DECL, NK_VARDECL, NK_TYPESPEC, NK_FUNDECL,
  NK_FORMALDECLLIST, NK_FORMALDECL, NK_FUNBODY, NK_LOCALDECLLIST,
  NK_STATEMENTLIST, NK_STATEMENT, NK_COMPOUNDSTMT, NK_ASSIGNSTMT,
  NK_CONDSTMT, NK_LOOPSTMT, NK_RETURNSTMT, NK_EXPRESSION, NK_RELOP,
  NK_ADDEXPR, NK_ADDOP, NK_TERM, NK_MULOP, NK_FACTOR, NK_FUNCCALLEXPR,
  NK_ARGLIST, NK_INTEGER, NK_IDENTIFIER, NK_VAR, NK_ARRAYDECL, NK_CHAR,
  NK_FUNCTYPENAME
};

static const char *nodeLabel[] = {
  "program", "decList", "decl", "varDecl", "typeSpecifier", "funDecl", "formalDecList",
  "formalDecl", "funBody", "localDeclList", "statementList", "statement", "compoundStmt",
  "assignStmt", "condStmt", "loopStmt", "returnStmt", "expression", "relop", "addExpr",
  "addop", "term", "mulop", "factor", "funcCallExpr", "argList", "integer", "identifier",
  "var", "arrayDecl", "char", "funcTypeName"
};

static const char *typeSpecStr[] = {"int", "char", "void"};

// helper functions
static const char *addOpStr(int val) {
  switch (val) {
    case 0: return "+";
    case 1: return "-";
    default: return "?";
  }
}

static const char *mulOpStr(int val) {
  switch (val) {
  case 2: return "*";
  case 3: return "/";
  default: return "?";
  }
}

static const char *relOpStr(int val){
  switch (val) {
    case 4: return "<";
    case 5: return "<=";
    case 6: return "==";
    case 7: return ">=";
    case 8: return ">";
    case 9: return "!=";
    default: return "?";
  }
}

tree *maketree(int kind) {
  tree *n = (tree *)calloc(1, sizeof(tree));
  if (!n) { return NULL; } 

  n->nodeKind = kind;
  n->numChildren = 0;
  n->val = 0;
  n->parent = NULL;

  return n;
}
tree *maketreeWithVal(int kind, int val) {
  // since we are just doing the same thing with the addition of a val, we can call this first
  tree *n = maketree(kind);

  if (!n){ return NULL; } 

  n->val = val;

  return n;
}
void addChild(tree *parent, tree *child) {
  if (!parent || !child) { return; } 
  if (parent->numChildren >= MAXCHILDREN) { return; } 

  parent->children[parent->numChildren] = child;
  parent->numChildren++;

  child->parent = parent;
}
void printAst(tree *root, int nestLevel) {
  // this function shouldn't be called with a NULL node
  // you should be able to remove this return check
  if (!root) return;
  // we print nestLevel*2 spaces, then we print the number 123
  // if nestLevel == 0 then there are 0 leading spaces
  // if nestLevel == 1 then there are 2 leading spaces
  // we can easily tab out print statements with this method
  // printf("%*s%d\n", nestLevel*2, "", 123);
  
  // we can also print our variable spacing first ...
  // printf("%*s", nestLevel*2, "");
  // then print the node information
  // printf("%s\n", "addexpr");
  // then we print the child nodes
  // for i from zero to root->numchildren printast(root->child[i], nestlevel+1)

  int indent = nestLevel*2;
  const char *label = nodeLabel[root->nodeKind];

  switch(root->nodeKind){
    case NK_TYPESPEC:
      printf("%*s%s,%s\n", indent, "", label, typeSpecStr[root->val]);
      break;

    case NK_INTEGER:
      printf("%*s%s,%d\n", indent, "", label, root->val);
      break;

    case NK_CHAR:
      printf("%*s%s,%d\n", indent, "", label, root->val);
      break;

    case NK_IDENTIFIER:
      if(root->val >= 0 && root->val < MAXIDS && strTable[root->val].id != NULL){
        printf("%*s%s,%s\n", indent, "", label, strTable[root->val].id);
      }
      else{ printf("%*sUNDECLARED VARIABLE\n", indent, ""); }
      break;

    case NK_RELOP:
      printf("%*s%s,%s\n", indent, "", label, relOpStr(root->val));
      break;

    case NK_ADDOP:
      printf("%*s%s,%s\n", indent, "", label, addOpStr(root->val));
      break;

    case NK_MULOP:
      printf("%*s%s,%s\n", indent, "", label, mulOpStr(root->val));
      break;

    default:
      printf("%*s%s\n", indent, "", label);
      break;
  }

  // recursively call for each child node
  for (int i = 0; i < root->numChildren; i++){
    printAst(root->children[i], nestLevel + 1);
  }
}
