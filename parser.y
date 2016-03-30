%{
  #include "common.h"
	#include <stdio.h>
%}


/* Definições */

%token T_CREATE
%token T_TABLE
%token T_STRING
%token T_INT
%token T_VARCHAR
%token T_FLOAT
%token D_STRING
%token D_INTEGER
%token D_FLOAT

%start Input

%% /* Regras */

Start_create_table:
  T_CREATE T_TABLE T_STRING '(' 
;

Finish_create_table:
  ')' ';'
;

Type_specifier:
  T_INT
  | T_VARCHAR
  | T_FLOAT
;

Create_column:
  T_STRING " " Type_specifier ','
;

Input:
  
  | Input Start_create_table
;
  

%% /* Código C */

void yyerror(const char* errmsg)
{
  printf("\n*** Erro: %s, on line: \n", errmsg);
}
 
int yywrap(void) 
{ 
  return 1;
}
 
int main(int argc, char** argv)
{
     yyparse();
     return 0;
}

