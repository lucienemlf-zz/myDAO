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
%token T_FOREIGN_KEY
%token T_REFERENCES
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

/*
  Validações FK:
    - validar se parametro existe na tabela
    - se existe a tabela referenciada
    - se existe atributo da tabela referenciada
*/

Start_create_table:
  T_CREATE T_TABLE D_STRING '(' Create_column {insert_element(element_list_pointer, $3, ENTITY, "TABLE");}
;

Create_primary_key:
  T_PRIMARY_KEY '(' D_STRING ')'',' Create_foreign_key {insert_element(element_list_pointer, $3, PRIMARY_KEY, "PRIMARY_KEY");} 
  | T_PRIMARY_KEY '(' D_STRING ')' Finish_create_table {insert_element(element_list_pointer, $3, PRIMARY_KEY, "PRIMARY_KEY");}
;

Create_foreign_key:
   T_FOREIGN_KEY '(' D_STRING ')' T_REFERENCES D_STRING'(' D_STRING ')' Finish_create_table {insert_foreign_key(foreign_key_list_pointer, $6, $8, $3);}
;

Finish_create_table:
  ')' ';'
;

Create_select_query:
  T_SELECT Selection_fields T_FROM D_STRING ';' {insert_select(select_list_pointer, select_fields_counter, $4);select_fields_counter = 0;}
;

Selection_fields:
  D_STRING {insert_selected_fields(selected_fields_list_pointer,$1);select_fields_counter++;}
  | D_STRING ',' Selection_fields {insert_selected_fields(selected_fields_list_pointer,$1);select_fields_counter++;}
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
  D_STRING Type_specifier Type_constraint ',' Create_primary_key {insert_element(element_list_pointer, $1, COLUMN, $2);}
  | D_STRING Type_specifier Type_constraint ',' Create_column {insert_element(element_list_pointer, $1, COLUMN, $2);}
;

Input:
  
  | Input Start_create_table
  | Input Create_select_query
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

int main(int argc, char *argv[])
{ 
  int elements_number;

  element_instance *element_pointer;
  element_list_pointer = initialize_element_list(element_pointer);

  entity_instance *entity_pointer;
  entity_list_pointer = initialize_entity_list(entity_pointer);

  select_instance *select_pointer;
  select_list_pointer = initialize_select_list(select_pointer);  

  selected_fields_instance *selected_fields_pointer;
  selected_fields_list_pointer = initialize_selected_fields_list(selected_fields_pointer);

  foreign_key_instance *foreign_key_pointer;
  foreign_key_list_pointer = initialize_foreign_list(foreign_key_pointer);

  char *sql_file_name;

  int i;
  int strsize = 0;
  for (i=1; i<argc; i++) {
      strsize += strlen(argv[i]);
      if (argc > i+1)
          strsize++;
  }

  sql_file_name = malloc(strsize);
  sql_file_name[0] = '\0';

  for (i=1; i<argc; i++) {
      strcat(sql_file_name, argv[i]);
      if (argc > i+1)
          strcat(sql_file_name, " ");
  }

  FILE *entry_file = fopen(sql_file_name, "r");

  if(!entry_file) {
    printf("Error opening %s.\n", sql_file_name);
    exit(1);
  }

  yyin = entry_file;

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

  printf("Foreign Keys found... \n");
  print_foreign_key_list(foreign_key_list_pointer);
  printf("\n");

  associate_select_selected_fields(selected_fields_list_pointer, select_list_pointer);
  validate_selected_fields(selected_fields_list_pointer, element_list_pointer);

  printf("Selected fields found... \n");
  print_selected_fields_list(selected_fields_list_pointer);
  printf("\n");

  printf("Creating folders...\n");
  int code_returned_folder_model = system("mkdir Model");
  int code_returned_folder_dao = system("mkdir DAO");
  printf("Folders succesfully created.\n\n");

  printf("Creating models files...\n");

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
      printf("Entity does not exist.\n");
    }
    auxiliary_pointer = auxiliary_pointer->next_entity;
  }

  printf("Models succesfully created.\n\n");

  printf("Creating DAOs files...\n");

  printf("Creating BasicDAO file...\n");
  write_basic_dao_file();
  printf("BasicDAO file successfully created.\n\n");

  entity_instance *auxiliary_pointer_dao;
  auxiliary_pointer_dao = entity_list_pointer->next_entity;

  for(i = 0; auxiliary_pointer_dao != NULL; i++)
  {
    int validade_entity = search_entity(auxiliary_pointer_dao->entity_name);
    if (validade_entity == 1)
    {
      write_java_DAO_file(auxiliary_pointer_dao->element, elements_number, auxiliary_pointer_dao->entity_name, select_list_pointer, selected_fields_list_pointer);
    }
    else
    {
      printf("Entity does not exist.\n");
    }
    auxiliary_pointer_dao = auxiliary_pointer_dao->next_entity;
  }

  printf("DAOs succesfully created.\n");

  fclose(entry_file);
 
  free(element_list_pointer);
  free(entity_list_pointer);
  free(select_list_pointer);
  free(selected_fields_list_pointer);
  free(foreign_key_list_pointer);
 
  return 0;
}
