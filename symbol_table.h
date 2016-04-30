#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

#define COLUMN 1
#define ENTITY 0

#define INTEIRO 2
#define VARCHAR 3
#define FLOAT 4


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
	int elements_counter = 0;

	if(list_pointer == NULL)
	{ 
		printf("There is no instance.\n");
		exit(1);
	}

	element_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_element;
	while(auxiliary_pointer != NULL)
	{
		printf("%s\n",auxiliary_pointer->element_name);
		printf("%d\n",auxiliary_pointer->element_scope);
		printf("%s\n",auxiliary_pointer->element_type);

		auxiliary_pointer = auxiliary_pointer->next_element;
		elements_counter += 1;
	}
	return elements_counter;
}

void write_java_file(element_instance *list_pointer, int dimension)
{
	FILE *file_out;
	char type_out[dimension][MAX];
	char name_array[dimension][MAX];
	char type_array[dimension][MAX];
	char integer_type[MAX];
	char varchar_type[MAX];
	char float_type[MAX];
	char table_type[MAX];
	int i;

	if(list_pointer == NULL)
	{
		printf("There is no instance.\n");
		exit(1);
	}

	element_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_element;
	for(i = 0; auxiliary_pointer != NULL; i++)
	{
		strcpy(name_array[i], auxiliary_pointer->element_name);
		strcpy(type_array[i], auxiliary_pointer->element_type);

		auxiliary_pointer = auxiliary_pointer->next_element;
	}

	strcpy(integer_type, "INT");
	strcpy(varchar_type, "VARCHAR");
	strcpy(float_type, "FLOAT");
	strcpy(table_type, "TABLE");

	for(i = 0; i < dimension; i++)
	{
		if((strcmp(type_array[i], table_type)) == 0)
		{
			strcpy(type_out[i], "table");
		}
		if((strcmp(type_array[i], integer_type)) == 0)
		{
			strcpy(type_out[i], "int");
		}		
		if((strcmp(type_array[i], varchar_type)) == 0)
		{
			strcpy(type_out[i], "String");
		}
		if((strcmp(type_array[i], float_type)) == 0)
		{
			strcpy(type_out[i], "float");
		}
	}

	char file_out_name[MAX], source_string[MAX];
	strcpy(file_out_name, name_array[0]);
	strcpy(source_string, ".java");
	strcat(file_out_name, source_string);

	printf("Writing java file...\n");
	file_out = fopen(file_out_name, "w");

	if(!file_out)
	{
		printf("I can't open java file.\n");
		exit(1);
	}

	fprintf(file_out, "public class %s {\n", name_array[0]);
	fprintf(file_out, "\n");

	for(i = 1; i < dimension; i ++)
	{
		fprintf(file_out, "	private %s %s;\n", type_out[i], name_array[i]);
	}

	fprintf(file_out, "\n");
	fprintf(file_out, "	public %s() {\n", name_array[0]);
	fprintf(file_out, "\n");
	fprintf(file_out, "	}\n");
	fprintf(file_out, "}");

	printf("Writing java file completed.\n");

	fclose(file_out);
}

#endif