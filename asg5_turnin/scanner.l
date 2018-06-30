/* $Id: lexer.l,v 1.7 2016-10-27 19:45:59-07 - - $ */
/* add regex for all token types in parser.y */

%{

#include "lyutils.h"

#define YY_USER_ACTION  { lexer::advance(); }

int yylval_token (int symbol) {
   yylval = new astree (symbol, lexer::lloc, yytext);
   return symbol;
}

%}

%option 8bit
%option debug
%option nodefault
%option noinput
%option nounput
%option noyywrap
%option verbose
%option warn

LETTER          [A-Za-z_]
DIGIT           [0-9]
MANTISSA        ({DIGIT}+\.?{DIGIT}*|\.{DIGIT}+)
EXPONENT        ([Ee][+-]?{DIGIT}+)

NOTTOK_INT      ({MANTISSA}[Ee][+-]?)
NOTTOK_STRINGCON    ((["].*[^"])$)
NOTTOK_IDENT       ({DIGIT}({LETTER}|{DIGIT})*)

TOK_INTCON      ({MANTISSA}{EXPONENT}?)
TOK_IDENT       ({LETTER}({LETTER}|{DIGIT})*)
TOK_CHARCON     ('([^\\'\n]|\\[\\'"0nt])')
TOK_STRINGCON   (\"([^\\"\n]|\\[\\'"0nt])*\")
TOK_IF          "if"
TOK_ELSE        "else"
TOK_WHILE       "while"
TOK_RETURN      "return"
TOK_STRUCT      "struct"
TOK_NULL        "null"
TOK_NEW         "new"
TOK_INT         "int"
TOK_VOID        "void"
TOK_STRING      "string"
TOK_CHAR        "char"
TOK_EQ          "=="
TOK_NE          "!="
TOK_LT          "<"
TOK_LE          "<="
TOK_GT          ">"
TOK_GE          ">="
TOK_ARRAY       "[]"

%%

"#".*               { lexer::include(); }
[ \t]+              { }
\n                  { lexer::newline(); }

{TOK_INTCON}        { return yylval_token (TOK_INTCON); }
{TOK_CHARCON}       { return yylval_token (TOK_CHARCON); }
{TOK_STRINGCON}     { return yylval_token (TOK_STRINGCON); }
{TOK_IF}            { return yylval_token (TOK_IF); }
{TOK_ELSE}          { return yylval_token (TOK_ELSE); }
{TOK_WHILE}         { return yylval_token (TOK_WHILE); }
{TOK_RETURN}        { return yylval_token (TOK_RETURN); }
{TOK_STRUCT}        { return yylval_token (TOK_STRUCT); }
{TOK_NULL}          { return yylval_token (TOK_NULL); }
{TOK_NEW}           { return yylval_token (TOK_NEW); }
{TOK_INT}           { return yylval_token (TOK_INT); }
{TOK_VOID}          { return yylval_token (TOK_VOID); }
{TOK_STRING}        { return yylval_token (TOK_STRING); }
{TOK_CHAR}          { return yylval_token (TOK_CHAR); }
{TOK_EQ}            { return yylval_token (TOK_EQ); }
{TOK_NE}            { return yylval_token (TOK_NE); }
{TOK_LT}            { return yylval_token (TOK_LT); }
{TOK_LE}            { return yylval_token (TOK_LE); }
{TOK_GT}            { return yylval_token (TOK_GT); }
{TOK_GE}            { return yylval_token (TOK_GE); }
{TOK_ARRAY}         { return yylval_token (TOK_ARRAY); }
{TOK_IDENT}         { return yylval_token (TOK_IDENT); }


"="                 { return yylval_token ('='); }
"+"                 { return yylval_token ('+'); }
"-"                 { return yylval_token ('-'); }
"*"                 { return yylval_token ('*'); }
"/"                 { return yylval_token ('/'); }
"^"                 { return yylval_token ('^'); }
"("                 { return yylval_token ('('); }
")"                 { return yylval_token (')'); }
";"                 { return yylval_token (';'); }

"!"                 { return yylval_token ('!'); }
"%"                 { return yylval_token ('%'); }
","                 { return yylval_token (','); }
"."                 { return yylval_token ('.'); }
"["                 { return yylval_token ('['); }
"]"                 { return yylval_token (']'); } 
"{"                 { return yylval_token ('{'); }
"}"                 { return yylval_token ('}'); }

{NOTTOK_INT}     { lexer::badtoken (yytext);
                  return yylval_token (TOK_INTCON); }

{NOTTOK_STRINGCON}     { lexer::badtoken (yytext); 
                  return yylval_token (TOK_STRINGCON); }

{NOTTOK_IDENT}     { lexer::badtoken (yytext); 
                  return yylval_token (TOK_IDENT); }


.               { lexer::badchar (*yytext); }

%%

