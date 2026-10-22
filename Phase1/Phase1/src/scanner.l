
/* definitions */

%{
#include <stdio.h>
#include <stdlib.h>
#include "tokendef.h"

 /* integers to track line and column numbers */
int scancol = 1;
int yycol = 1;
int scanlineno = 1;

 /* char pointer to pass error messages to driver.c */
char *yyerror;

 /* : functions to update line and column numbers */
void updateCol();
void countLines();

 /* : function to process a string literal */
int processString();

%}

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

%%

 /* rules */

 /* Keywords */
 /* Support all keywords in mC */
"if"        {updateCol(); return KWD_IF;}
"else"      {updateCol(); return KWD_ELSE;}
"while"     {updateCol(); return KWD_WHILE;}
"int"       {updateCol(); return KWD_INT;}
"string"    {updateCol(); return KWD_STRING;}
"char"      {updateCol(); return KWD_CHAR;}
"return"    {updateCol(); return KWD_RETURN;}
"void"      {updateCol(); return KWD_VOID;}

 /* Operators */
 /* Support all operators in mC */
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
"@"         {updateCol(); return OPER_AT;}
"++"        {updateCol(); return OPER_INC;}
"--"        {updateCol(); return OPER_DEC;}
"&&"        {updateCol(); return OPER_AND;}
"||"        {updateCol(); return OPER_OR;}
"!"         {updateCol(); return OPER_NOT;}
"%"         {updateCol(); return OPER_MOD;}

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
{identifier}    {updateCol(); return ID;}
{illidentifier} {updateCol(); yyerror = "ILLEGAL TOKEN"; return ERROR;}

 /* Constants */
{integerlead0}  {updateCol(); yyerror = "ILLEGAL TOKEN"; return ERROR;}
{integer}       {updateCol(); return INTCONST;}
{character}     {updateCol(); return CHARCONST;}
{string}        {updateCol(); return processString();}
{untermstring}  {updateCol(); yyerror = "UNTERMINATED STRING"; return ERROR;}

 /* Comments */
{comment}       {updateCol();}
{untermcomment} {
    updateCol();
    //for(int i = 0; i < yyleng; i++){    if(yytext[i] == '\n'){  countLines();   }   }
    yyerror = "UNTERMINATED COMMENT";
    return ERROR;}
{multlncomment} {
    updateCol();
    for(int i = 0; i < yyleng; i++){    if(yytext[i] == '\n'){  countLines();   }   }
}

 /* Other */
{newline}       {countLines();}
{whitespace}    {updateCol();}
.               {updateCol(); return ILLEGAL_TOK;}

%%

/* user routines */

/* Implement this function to keep track of column numbers */
void updateCol(){
    yycol = scancol;
    scancol += yyleng;
}

/* Implement this function to keep track of line numbers */
void countLines(){
    yylineno++;
    scancol = 1;
    yycol = 1;
}


/*
 Implement this function to check for illegal escape
 sequences in string literals and convert valid escape 
 sequences into escaped characters, e.g.

 (string[0] == '\\' and string[1] == 'n', then string[0] should be '\n')
*/
int processString(){
    static char inputString[512];
    int i = 1;
    int c = 0;

    while(yytext[i] != '"' && yytext[i] != '\0'){
        if(yytext[i] == '\r'){
            yyerror = "STRING SPANS MULTIPLE LINES";
            return ERROR;
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
                    yyerror = "UNRECOGNIZED ESCAPE CHARACTER IN STRING";
                    yycol += i;
                    return ERROR;
            }
        }
        else{
            inputString[c] = yytext[i];
        }
        i++;
        c++;
    }
    if(yytext[i] == '\0'){
        yyerror = "UNTERMINATED STRING CONSTANT";
        return ERROR;
    }
    inputString[c] = '\0';
    strcpy(yytext,inputString);
    return STRCONST;
}
