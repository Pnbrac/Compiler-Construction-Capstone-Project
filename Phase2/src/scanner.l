/* ---------------------------------- C Code ------------------------------- */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strtab.h"
#include "y.tab.h"

 /* integers to track line and column numbers */
int scancol = 1;
int yycol = 1;
int scanlineno = 1;

 /* char pointer to pass error messages to driver.c */
char *errorMsg;

 /* : functions to update line and column numbers */
void updateCol();
void countLines();

 /* : function to process a string literal */
int processString();
%}

/* -------------------------------- Definitions ----------------------------- */
newline         \n|\r|\r\n
whitespace      [ \t]+

integerlead0    0[0-9]+
integer         0|[1-9]([0-9])*
character       \'([^\'\\\n]|\\.)\'

/* String can contain any characters between the double quotes */
/* other than a newline or unescaped doublequotes */
string       \"([^\\\n\"]|\\.)*\"

/* If the end quote is not found in the same line the string is unterminated */
untermstring \"([^\\\n\"]|\\.)*

comment         \/\/.*
multlncomment   \/\*([^*]|\*+[^*/])*\*+\/
untermcomment   \/\*([^*]|\*+[^*/])*

illidentifier   [0-9]+([a-z]|[A-Z])+(([a-z]|[A-Z])|{integer})*
identifier      ([a-z]|[A-Z])(([a-z]|[A-Z])|{integer})*

yylineno = 1;


/* ---------------------------------- Rules --------------------------------- */
%%
 /* Keywords */
"if"        {updateCol(); return KWD_IF;}
"else"      {updateCol(); return KWD_ELSE;}
"while"     {updateCol(); return KWD_WHILE;}
"int"       {updateCol(); return KWD_INT;}
"string"    {updateCol(); return KWD_STRING;}
"char"      {updateCol(); return KWD_CHAR;}
"return"    {updateCol(); return KWD_RETURN;}
"void"      {updateCol(); return KWD_VOID;}

 /* Operators */
"+"         {updateCol(); return OPER_ADD;}
"-"         {updateCol(); return OPER_SUB;}
"*"         {updateCol(); return OPER_MUL;}
"/"         {updateCol(); return OPER_DIV;}
"<"         {updateCol(); return OPER_LT;}
">"         {updateCol(); return OPER_GT;}
">="        {updateCol(); return OPER_GTE;}
"<="        {updateCol(); return OPER_LTE;}
"=="        {updateCol(); return OPER_EQ;}
"!="        {updateCol(); return OPER_NEQ;}
"="         {updateCol(); return OPER_ASGN;}

 /* Brackets & Parens */
"["         {updateCol(); return LSQ_BRKT;}
"]"         {updateCol(); return RSQ_BRKT;}
"{"         {updateCol(); return LCRLY_BRKT;}
"}"         {updateCol(); return RCRLY_BRKT;}
"("         {updateCol(); return LPAREN;}
")"         {updateCol(); return RPAREN;}

 /* Punctuation */
","         {updateCol(); return COMMA;}
";"         {updateCol(); return SEMICLN;}


 /* Identifiers */
 /* TEMPORAILY CHANGED RETURN ERROR TO RETURN 0 TO STOP ERRORS FROM OCCURING */
{identifier}    {updateCol(); yylval.strval = strdup(yytext); return ID;}
{illidentifier} {updateCol(); errorMsg = "ILLEGAL TOKEN"; return 0;}

 /* Constants */
{integerlead0}  {updateCol(); errorMsg = "ILLEGAL TOKEN"; return 0;}

  /* yylval is a union defined in parser.y */
  /* INTCONST, and other defined, are generated automatically from parser.y */
  /* If you don't use a return value in parser.py, it won't be defined */
{integer}       { yylval.value = atoi(yytext); return INTCONST; }

{character}     {updateCol(); return CHARCONST;}
{string}        {updateCol(); return processString();}
{untermstring}  {updateCol(); errorMsg = "UNTERMINATED STRING"; return 0;}

 /* Comments */
{comment}       {updateCol();}
{untermcomment} {
    updateCol();
    //for(int i = 0; i < yyleng; i++){    if(yytext[i] == '\n'){  countLines();   }   }
    errorMsg = "UNTERMINATED COMMENT";
    return 0;}
{multlncomment} {
    updateCol();
    for(int i = 0; i < yyleng; i++){    if(yytext[i] == '\n'){  countLines();   }   }
}

 /* Other */
{newline}       {countLines();}
{whitespace}    {updateCol();}

%%

/* ----------------------------- User Routines ------------------------------ */

void updateCol(){
    yycol = scancol;
    scancol += yyleng;
}

void countLines(){
    yylineno++;
    scancol = 1;
    yycol = 1;
}

int processString(){
    static char inputString[512];
    int i = 1;
    int c = 0;

    while(yytext[i] != '"' && yytext[i] != '\0'){
        if(yytext[i] == '\r'){
            errorMsg = "STRING SPANS MULTIPLE LINES";
            return 0;
        }
        if(yytext[i] == '\\'){
            i++;
            switch (yytext[i]){
                case 'n':
                    inputString[c] = '\n';
                    break;
                case 't':
                    inputString[c] = '\t';
                    break;
                case '\"':
                    inputString[c] = '\"';
                    break;
                case '\\':
                    inputString[c] = '\\';
                    break;
                default:
                    errorMsg = "UNRECOGNIZED ESCAPE CHARACTER IN STRING";
                    yycol += i;
                    return 0;
            }
        }
        else{
            inputString[c] = yytext[i];
        }
        i++;
        c++;
    }
    if(yytext[i] == '\0'){
        errorMsg = "UNTERMINATED STRING CONSTANT";
        return 0;
    }
    inputString[c] = '\0';
    strcpy(yytext,inputString);
    return STRCONST;
}

/* video on lex/yacc mentions, unsure if needed for this project */
int yywrap(void){
  return 1;
}