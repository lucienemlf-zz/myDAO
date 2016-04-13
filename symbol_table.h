#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#define MAX 500

#define FOUND 1
#define NOT_FOUND 0

//Structure for Entities
struct entity
{
	char entity_name[MAX];
	struct entity *next_entity;
};

//Structure for Columns
struct column
{
	char column_name[MAX];
	char column_type[MAX];
	char entity_name[MAX];
	struct column *next_column;
};

//Structures
typedef struct entity entity_instance;
typedef struct column column_instance;

//Pointers
entity_instance *entity_list_pointer;
column_instance *column_list_pointer;

void insert_entity(entity_instance *list_pointer, char entity_name_insert[MAX])
{
	entity_instance *new_entity, *first_entity;
	new_entity = (entity_instance*)malloc(sizeof(entity_instance));
	strcpy(new_entity->entity_name, entity_name_insert);
	first_entity = list_pointer->next_entity;
	list_pointer->next_entity = new_entity;
	new_entity->next_entity = first_entity;
}

void insert_column(column_instance *list_pointer, char column_name_insert[MAX], char column_type_insert[MAX], char entity_name_insert[MAX])
{
	column_instance *new_column, *first_column;
	new_column = (column_instance*)malloc(sizeof(column_instance));
	strcpy(new_column->column_name, column_name_insert);
	strcpy(new_column->column_type, column_type_insert);
	strcpy(new_column->entity_name, entity_name_insert);
	first_column = list_pointer->next_column;
	list_pointer->next_column = new_column;
	new_column->next_column = first_column;
}

int search_entity(char entity_name_insert[MAX])
{
	if(entity_list_pointer == NULL)
    {
        return NOT_FOUND;
    }
    else
    {
        entity_instance *auxiliary_pointer = entity_list_pointer;
        while(auxiliary_pointer != NULL)
        {
            if (strcmp(entity_name_insert, auxiliary_pointer->entity_name) == 0)
            {
                return FOUND;
            }
            auxiliary_pointer = auxiliary_pointer->next_entity;
        }
        return NOT_FOUND;
    }
}

int search_column(char column_name_insert[MAX], char entity_name_insert[MAX])
{
	if(column_list_pointer == NULL)
    {
        return NOT_FOUND;
    }
    else
    {
        column_instance *auxiliary_pointer = column_list_pointer;
        while(auxiliary_pointer != NULL)
        {
            if (strcmp(entity_name_insert, auxiliary_pointer->entity_name) == 0
            	&& strcmp(column_name_insert, auxiliary_pointer->column_name) == 0)
            {
                return FOUND;
            }
            auxiliary_pointer = auxiliary_pointer->next_column;
        }
        return NOT_FOUND;
    }
}

void print_entity_list(entity_instance *list_pointer)
{
	entity_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_entity;
	while(auxiliary_pointer != NULL)
	{
		printf("%s.\n",auxiliary_pointer->entity_name);
		auxiliary_pointer = auxiliary_pointer->next_entity;
	}
}

void print_column_list(column_instance *list_pointer)
{
	column_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_column;
	while(auxiliary_pointer != NULL)
	{
		printf("%s.\n",auxiliary_pointer->column_name);
		printf("%s.\n",auxiliary_pointer->entity_name);
		printf("%s.\n",auxiliary_pointer->column_type);
		auxiliary_pointer = auxiliary_pointer->next_column;
	}
}

#endif