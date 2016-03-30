%{
	#include <stdio.h>
%}


/* Definições */

%token T_CREATE
%token T_TABLE
%token T_STRING
%token T_OPEN_PARENTHESIS
%token T_CLOSE_PARENTHESIS
%token T_INT
%token T_VARCHAR
%token T_FLOAT
%token T_COMMA
%token T_SEMICOLON

%start Input

%% /* Regras */

Start_create_table:
  T_CREATE T_TABLE T_STRING T_OPEN_PARENTHESIS
;

Finish_create_table:
  T_CLOSE_PARENTHESIS T_SEMICOLON
;

Type_specifier:
  T_INT
  | T_VARCHAR
  | T_FLOAT
;

Create_column:
  T_STRING " " Type_specifier T_COMMA
;

Input:
  
  | Input Start_create_table
;
  

%% /* Código C */

int yyerror(char *s){
  printf("%s\n", s);
}

int main(void) {
  yyparse();
}
