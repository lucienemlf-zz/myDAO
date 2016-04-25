#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#define MAX 500

#define FOUND 1
#define NOT_FOUND 0

#define COLUMN 2
#define ENTITY 3


//Structure for Columns
struct element
{
	char element_name[MAX];
	int element_scope;
	char element_type[MAX];
	struct element *next_element;
};

//Structures
typedef struct element element_instance;

//Pointers
element_instance *element_list_pointer;

void insert_element(element_instance *list_pointer, char element_name_insert[MAX], int element_scope_insert, char element_type_insert[MAX])
{
	element_instance *new_element, *first_element;
	new_element = (element_instance*) malloc(sizeof(element_instance));
	strcpy(new_element->element_name, element_name_insert);
	new_element->element_scope = element_scope_insert;
	strcpy(new_element->element_type, element_type_insert);
	first_element = list_pointer->next_element;
	list_pointer->next_element = new_element;
	new_element->next_element = first_element;
}


int print_element_list(element_instance *list_pointer)
{
	if(list_pointer==NULL){ 
		printf("There is no instance\n");
		return -1;
	}
	element_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_element;
	while(auxiliary_pointer != NULL)
	{
		printf("%s\n",auxiliary_pointer->element_name);
		printf("%d\n",auxiliary_pointer->element_scope);
		printf("%s\n",auxiliary_pointer->element_type);

		auxiliary_pointer = auxiliary_pointer->next_element;
	}
	return 0;
}

#endif