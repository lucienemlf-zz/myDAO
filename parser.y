%{
  #include "common.h"
	#include <stdio.h>
  #include <stdlib.h>
  #include "symbol_table.h"
  FILE *yyin;
%}

/* Definições */

%union
{
  char * strval;
}

%token T_CREATE 
%token T_IGNORE T_NOT_NULL
%token T_TABLE
%token T_SELECT
%token T_FROM
%token T_PRIMARY_KEY
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
  T_PRIMARY_KEY '(' D_STRING ')'')' ';' {insert_element(element_list_pointer, $3, PRIMARY_KEY, "PRIMARY_KEY");} 
  | T_PRIMARY_KEY '(' D_STRING ')'')' ';' Create_select_query {insert_element(element_list_pointer, $3, PRIMARY_KEY, "PRIMARY_KEY");}
;

Create_select_query:
  T_SELECT D_STRING T_FROM D_STRING ';' {insert_select(select_list_pointer, $2, $4);}
  | T_SELECT D_STRING T_FROM D_STRING ';' Create_select_query {insert_select(select_list_pointer, $2, $4);}
;

Type_specifier:
  T_INT
  | T_VARCHAR
  | T_FLOAT
;

Type_constraint:

  | T_NOT_NULL Type_constraint  
  | T_IGNORE Type_constraint
;



Create_column:
  D_STRING Type_specifier Type_constraint ',' Finish_create_table {insert_element(element_list_pointer, $1, COLUMN, $2);}
  | D_STRING Type_specifier Type_constraint ',' Create_column {insert_element(element_list_pointer, $1, COLUMN, $2);}
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

  element_instance *element_pointer;
  element_list_pointer = initialize_element_list(element_pointer);

  entity_instance *entity_pointer;
  entity_list_pointer = initialize_entity_list(entity_pointer);

  select_instance *select_pointer;
  select_list_pointer = initialize_select_list(select_pointer);

  FILE *entry_file = fopen("arquivo_entrada.sql", "r");

  if(!entry_file) {
    printf("I can't open arquivo_entrada.sql.\n");
    exit(1);
  }

  yyin = entry_file;

  // Montar tabela de simbolos
  yyparse();
  
  printf("Elements found...\n");
  create_entity_list(element_list_pointer);
  elements_number = print_element_list(element_list_pointer);
  printf("\n");

  
  printf("Entities found... \n");
  print_entity_list(entity_list_pointer);
  printf("\n");

  printf("Selects found... \n");
  print_select_list(select_list_pointer);
  printf("\n");

  printf("Creating folders...\n");
  int code_returned_folder_model = system("mkdir Model");
  int code_returned_folder_dao = system("mkdir DAO");

  
  // parse

  // Voltar o ponteiro de parse pro início do arquivo de entrada

  // Faz as validações e cria os arquivos
  int i;

  entity_instance *auxiliary_pointer;
  auxiliary_pointer = entity_list_pointer->next_entity;

  for(i = 0; auxiliary_pointer != NULL; i++)
  {
    int validade_entity = search_entity(auxiliary_pointer->entity_name);
    if (validade_entity == 1)
    {
      write_java_file(auxiliary_pointer->element, elements_number, auxiliary_pointer->entity_name);
    }
    else
    {
      printf("Entidade Não Existente\n");
    }
    auxiliary_pointer = auxiliary_pointer->next_entity;
  }

  entity_instance *auxiliary_pointer_dao;
  auxiliary_pointer_dao = entity_list_pointer->next_entity;

  for(i = 0; auxiliary_pointer_dao != NULL; i++)
  {
    int validade_entity = search_entity(auxiliary_pointer_dao->entity_name);
    if (validade_entity == 1)
    {
      write_java_DAO_file(auxiliary_pointer_dao->element, elements_number, auxiliary_pointer_dao->entity_name);
    }
    else
    {
      printf("Entidade Não Existente\n");
    }
    auxiliary_pointer_dao = auxiliary_pointer_dao->next_entity;
  }

  fclose(entry_file);
 
  free(element_list_pointer);
  free(entity_list_pointer);
 
  return 0;
}
