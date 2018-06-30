%{
//cojaroge
//1558818



#include <cassert>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "astree.h"
#include "lyutils.h"

%}

%debug
%defines
%error-verbose
%token-table
%verbose

%destructor { destroy ($$); } <>
%printer { astree::dump (yyoutput, $$,0); } <>

%initial-action {
   parser::root = new astree (TOK_ROOT, {0, 0, 0}, "<>");
}

%token TOK_VOID TOK_CHAR TOK_INT TOK_STRING
%token TOK_IF TOK_ELSE TOK_WHILE TOK_RETURN TOK_STRUCT
%token TOK_NULL TOK_NEW TOK_ARRAY
%token TOK_EQ TOK_NE TOK_LT TOK_LE TOK_GT TOK_GE
%token TOK_IDENT TOK_INTCON TOK_CHARCON TOK_STRINGCON

%token TOK_BLOCK TOK_CALL TOK_IFELSE TOK_INITDECL
%token TOK_POS TOK_NEG TOK_NEWARRAY TOK_TYPEID TOK_FIELD
%token TOK_ORD TOK_CHR TOK_ROOT

%token TOK_NEWSTRING TOK_RETURNVOID TOK_VARDECL TOK_FUNCTION
%token TOK_PARAMLIST TOK_PROTOTYPE TOK_INDEX TOK_DECLID

%right  TOK_IF TOK_ELSE
%right  '='
%left  TOK_EQ TOK_NE TOK_LT TOK_LE TOK_GT TOK_GE
%left   '+' '-'
%left   '*' '/' '%'
%left   '{' '.'
%right TOK_POS TOK_NEG TOK_NEW '!'
%left  TOK_IDENT TOK_FUNCTION TOK_FIELD


%expect 27

%start start

%%

start     : program            
    { $$ = $1 = new astree (TOK_ROOT, {0, 0, 0}, "<>"); }
          ; 
                                                    
program   : program structdef  { $$ = $1->adopt ($2); }
          | program function   { $$ = $1->adopt ($2); }
          | program statement  { $$ = $1->adopt ($2); }
          | program error '}'  { destroy($3); $$ = $1; }            
          | program error ';'  { destroy($3); $$ = $1; }            
          | { $$ = parser::root; }
          ;

structdef_ellipse   : '{' fielddecl ';' 
                        {
                            destroy($3); 
                            $$ = $1->adopt($2);
                        }
                    | structdef_ellipse fielddecl ';'  
                        {
                            destroy($3); 
                            $$ = $1->adopt($2);
                        }
                    ;

structdef   : TOK_STRUCT TOK_IDENT structdef_ellipse '}'   
                {
                    destroy($4); 
                    $2 = $2->substitute($2, TOK_TYPEID); 
                    $$ = $1->adopt($2,$3);
                }
            | TOK_STRUCT TOK_IDENT '{' '}'     
                {
                    destroy($3,$4); 
                    $2 = $2->substitute($2, TOK_TYPEID); 
                    $$ = $1->adopt($2);
                }
            ;

fielddecl   : basetype TOK_IDENT            
                {
                    $2 = $2->substitute($2,TOK_FIELD); 
                    $$ = $1->adopt($2);
                }
            | basetype TOK_ARRAY TOK_IDENT   
                {
                    $3 = $3->substitute($3,TOK_FIELD); 
                    $$ = $2->adopt($1,$3);
                }
            ;

basetype    : TOK_VOID        { $$ = $1; }
            | TOK_INT         { $$ = $1; }
            | TOK_STRING      { $$ = $1; }
            | TOK_TYPEID      { $$ = $1; }
            | TOK_IDENT       
                { 
                    $1 = $1->substitute($1,TOK_TYPEID); 
                    $$ = $1; 
                }
            ;

function_ellipse    : '(' identdecl                     
                        {
                            $1 = $1->substitute($1, 
                                TOK_PARAMLIST); 
                            $$ = $1->adopt($2);
                        }
                    | function_ellipse ',' identdecl    
                        {
                            destroy($2); 
                            $$ = $1->adopt($3);
                        }
                    ;

function    : identdecl function_ellipse ')' block 
                {
                    destroy($3);
                    $$ = new astree(TOK_FUNCTION, $1->lloc, "");
                    $$ = $$->adopt($1, $2);
                    $$ = $$->adopt($4);
                }
            | identdecl function_ellipse ')' ';'
                {
                    destroy($3,$4);
                    $$ = new astree(TOK_PROTOTYPE, $1->lloc, "");
                    $$ = $$->adopt($1,$2);
                }
            | identdecl '(' ')' block 
                {
                    destroy($3);
                    $2 = $2->substitute($2, TOK_PARAMLIST);
                    $$ = new astree(TOK_FUNCTION, $1->lloc, "");
                    $$ = $$->adopt($1,$2);
                    $$ = $$->adopt($4);
                }
            | identdecl '(' ')' ';'
                {
                    destroy($3, $4);
                    $2 = $2->substitute($2, TOK_PARAMLIST);
                    $$ = new astree(TOK_PROTOTYPE, $1->lloc, "");
                    $$ = $$->adopt($1, $2);
                }
            ;

identdecl   : basetype TOK_IDENT            
                {
                    $2 = $2->substitute($2, TOK_DECLID); 
                    $$ = $1->adopt($2);
                }
            | basetype TOK_ARRAY TOK_IDENT  
                {
                    $3 = $3->substitute($3, TOK_DECLID); 
                    $$ = $2->adopt($1, $3);
                }
            ;

block_ellipse   : '{'  statement             
                    { 
                        $1 = $1->substitute($1, TOK_BLOCK); 
                        $$ = $1->adopt($2); 
                    }
                | block_ellipse statement   {$$ = $1->adopt($2);}
                ;

block       : block_ellipse '}'     
                {
                    destroy($2); 
                    $$ = $1->substitute($1,TOK_BLOCK);
                }
            | '{' '}'               
                {
                    destroy($2); 
                    $$ = $1->substitute($1,TOK_BLOCK);
                }
            ;

statement   : block           { $$ = $1; }
            | vardecl         { $$ = $1; }
            | while           { $$ = $1; }
            | ifelse          { $$ = $1; }
            | return          { $$ = $1; }
            | expr ';'        { destroy($2); $$ = $1; }
            | ';'             { $$ = $1; }
            ;

vardecl     : identdecl '=' expr ';' 
                {
                    destroy($4); 
                    $2 = $2->substitute($2, TOK_VARDECL); 
                    $$ = $2->adopt($1,$3);
                }
            ;

while       : TOK_WHILE '(' expr ')' statement  
                {
                    destroy($2,$4); 
                    $$ = $1->adopt($3,$5);
                }
            ;

ifelse      : TOK_IF '(' expr ')' statement TOK_ELSE statement 
                {
                    destroy($2, $4); 
                    destroy($6); 
                    $1 = $1->substitute($1, TOK_IFELSE); 
                    $$ = $1->adopt($3,$5); 
                    $$ = $$->adopt($7);
                }
            | TOK_IF '(' expr ')' statement 
                {
                    destroy($2, $4); 
                    $$ = $1->adopt($3, $5);
                }
            ;

return      : TOK_RETURN  expr  ';'     
                {
                    destroy($3); 
                    $$ = $1->adopt($2);
                }
            | TOK_RETURN ';'            
                {
                    destroy($2); 
                    $$ = $1->substitute($1,TOK_RETURNVOID);
                }
            ;

binop       : TOK_EQ    { $$ = $1; }
            | TOK_NE    { $$ = $1; }
            | TOK_LT    { $$ = $1; }
            | TOK_LE    { $$ = $1; }
            | TOK_GT    { $$ = $1; }
            | TOK_GE    { $$ = $1; }
            | '='       { $$ = $1; }
            | '+'       { $$ = $1; }
            | '-'       { $$ = $1; }
            | '*'       { $$ = $1; }
            | '/'       { $$ = $1; }
            ;

unop        : '+'           
                { 
                    $1 = $1->substitute($1,TOK_POS); 
                    $$ = $1;
                }
            | '-'           
                { 
                    $1 = $1->substitute($1,TOK_NEG); 
                    $$ = $1;
                }
            | '!'             { $$ = $1; }
            | TOK_NEW         { $$ = $1; }
            ;



expr        : expr binop expr       { $$ = $2->adopt ($1, $3);}
            | unop expr             { $$ = $1->adopt($2); }           
            | allocator             { $$ = $1; }
            | call                  { $$ = $1; }
            | '(' expr ')'          
                { 
                    destroy ($1, $3); 
                    $$ = $2; 
                }
            | variable              { $$ = $1; }
            | constant              { $$ = $1; }
            ;




allocator   : TOK_NEW TOK_IDENT '(' ')'  
                {
                    destroy($3,$4); 
                    $2 = $2->substitute($2, TOK_TYPEID); 
                    $$ = $1->adopt($2); 
                }
            | TOK_NEW TOK_STRING '(' expr ')' 
                {
                    destroy ($3, $5); 
                    destroy($2); 
                    $1 = $1->substitute ($1,TOK_NEWSTRING); 
                    $$ = $1->adopt($4);
                }
            | TOK_NEW basetype '[' expr ']' 
                {
                    destroy ($3, $5); 
                    $1 = $1->substitute ($1, TOK_NEWARRAY); 
                    $$ = $1->adopt($2,$4); 
                }
            ;

call_elipse : TOK_IDENT '(' expr 
                {
                    $2 = $2->substitute($2, TOK_CALL);
                    $$ = $2->adopt($1, $3);
                }
            | call_elipse ',' expr 
                {
                    destroy($2); 
                    $$ = $1->adopt($3);
                }
            ;

call        : call_elipse ')' {destroy($2); $$ = $1;}
            | TOK_IDENT '(' ')' 
                {
                    destroy($3); 
                    $2 = $2->substitute($2, TOK_CALL);
                    $$ = $2->adopt($1);
                }
            ;

variable    : TOK_IDENT       { $$ = $1; }
            | expr '[' expr ']' 
                {
                    destroy($4); 
                    $2 = $2->substitute($2, TOK_INDEX); 
                    $$ = $2->adopt($1, $3); 
                }
            | expr '.' TOK_IDENT  
                {
                    $3 = $3->substitute($3, TOK_FIELD); 
                    $$ = $2->adopt($1,$3); 
                }
            ;

constant    : TOK_INTCON      { $$ = $1; }
            | TOK_CHARCON     { $$ = $1; }
            | TOK_STRINGCON   { $$ = $1; }
            | TOK_NULL        { $$ = $1; }
            ;


%%


const char *parser::get_tname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}


bool is_defined_token (int symbol) {
   return YYTRANSLATE (symbol) > YYUNDEFTOK;
}


// static void* yycalloc (size_t size) {
//    void* result = calloc (1, size);
//    assert (result != nullptr);
//    return result;
// }


