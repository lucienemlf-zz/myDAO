%{
  #include "common.h"
	#include <stdio.h>
  #include <stdlib.h>
  #include "symbol_table.h"
  int columns = 0;
  FILE *yyin;
%}

/* Definições */

%union
{
  char * strval;
}

%token T_CREATE
%token T_TABLE
%token T_STRING
%token T_INT
%token T_VARCHAR
%token T_FLOAT
%token D_STRING
%type <strval> D_STRING
%type <strval> T_INT
%type <strval> T_VARCHAR
%type <strval> T_FLOAT
%type <strval> Type_specifier
%token D_INTEGER
%token D_FLOAT

%start Input

%% /* Regras */

Start_create_table:
  T_CREATE T_TABLE D_STRING '(' Create_column {insert_element(element_list_pointer, $3, ENTITY, "TABLE");}
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
  D_STRING Type_specifier Finish_create_table {insert_element(element_list_pointer, $1, COLUMN, $2);}
  | D_STRING Type_specifier ',' Create_column {insert_element(element_list_pointer, $1, COLUMN, $2);}
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
  int elements_number;
  
  element_list_pointer = (element_instance*)malloc(sizeof(element_instance));
  element_list_pointer->next_element = NULL;

  entity_list_pointer = (entity_instance*)malloc(sizeof(entity_instance));
  entity_list_pointer->next_entity = NULL;


  FILE *entry_file = fopen("arquivo_entrada.sql", "r");

  if(!entry_file) {
    printf("I can't open arquivo_entrada.sql.\n");
    exit(1);
  }

  yyin = entry_file;

  yyparse();
  
  printf("Elements found...\n");
  elements_number = print_element_list(element_list_pointer);
  printf("\n");

  create_entity_list(element_list_pointer);
  
  printf("Entities found... \n");
  print_entity_list(entity_list_pointer);
  printf("\n");

  //write_java_file(element_list_pointer, elements_number);
  //write_java_DAO_file(element_list_pointer, elements_number);

  fclose(entry_file);
 
  free(element_list_pointer);
  free(entity_list_pointer);
 
  return 0;
}
