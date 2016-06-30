#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

#define COLUMN 1
#define ENTITY 0

#define PRIMARY_KEY 2
#define FOREIGN_KEY 3

#define FOUND 1
#define NOT_FOUND 0

#define VALID 1
#define INVALID 0

int select_fields_counter = 0;

//Structure for Columns
struct element
{
	char element_name[MAX];
	int element_scope;
	char element_type[MAX];
	struct element *next_element;
	char entity_name[MAX];
	
};

//Structure for Entities
struct entity 
{
  char entity_name[MAX];
  struct element *element;
  struct entity *next_entity;
};

struct select
{
	int selection_fields;
	char entity_name[MAX];
	int validity;
	struct select *next_select;
};

struct selected_fields
{
	char field_name[MAX];
	struct select *select;
	int validity;
	struct selected_fields *next_selected_field;
};

struct foreign_key
{
	char foreign_key[MAX];
	char table[MAX];
	char table_primary_key[MAX];

	struct foreign_key *next_foreign_key; 
};

//Structures
typedef struct element element_instance;
typedef struct entity entity_instance;
typedef struct select select_instance;
typedef struct selected_fields selected_fields_instance;
typedef struct foreign_key foreign_key_instance;


//Pointers
element_instance *element_list_pointer;
entity_instance *entity_list_pointer;
select_instance *select_list_pointer;
selected_fields_instance *selected_fields_list_pointer;
foreign_key_instance *foreign_key_list_pointer;


// Inicialização das listas
element_instance *initialize_element_list(element_instance *list_pointer)
{
  list_pointer = (element_instance*) malloc (sizeof(element_instance));
  list_pointer->next_element = NULL;
  return list_pointer;
}

entity_instance *initialize_entity_list(entity_instance *list_pointer)
{
  list_pointer = (entity_instance*) malloc (sizeof(entity_instance));
  list_pointer->next_entity = NULL;
  return list_pointer;
}

select_instance *initialize_select_list(select_instance *list_pointer)
{
	list_pointer = (select_instance*) malloc (sizeof(select_instance));
	list_pointer->next_select = NULL;
	return list_pointer;
}

foreign_key_instance *initialize_foreign_list(foreign_key_instance *list_pointer)
{
	list_pointer = (foreign_key_instance*) malloc (sizeof(foreign_key_instance));
	list_pointer->next_foreign_key = NULL;
	return list_pointer;
}

selected_fields_instance *initialize_selected_fields_list(selected_fields_instance *list_pointer)
{
	list_pointer = (selected_fields_instance*) malloc (sizeof(selected_fields_instance));
	list_pointer->next_selected_field = NULL;
	return list_pointer;
}


// Declaração das funções da tabela de simbolos
void insert_element(element_instance *list_pointer, char element_name_insert[MAX], int element_scope_insert, char element_type_insert[MAX]);
void insert_entity(entity_instance *list_pointer, element_instance *element_insert);
void insert_select(select_instance *list_pointer, int selection_fields, char entity_name[MAX]);
void insert_foreign_key(foreign_key_instance *list_pointer, char table[MAX], char table_primary_key[MAX], char foreign_key[MAX]);
void insert_selected_fields(selected_fields_instance *list_pointer, char field_name[MAX]);
void create_entity_list(element_instance *list_pointer);
int print_element_list(element_instance *list_pointer);
int is_pk(element_instance *list_pointer, char primary_key[MAX]);
void print_entity_list(entity_instance *list_pointer);
void print_select_list(select_instance *list_pointer);
void print_foreign_key_list(foreign_key_instance *list_pointer);
void print_selected_fields_list(selected_fields_instance *list_pointer);
void associate_select_selected_fields(selected_fields_instance *selected_fields_list_pointer, select_instance *select_list_pointer);
void validate_selected_fields(selected_fields_instance *selected_fields_list_pointer, element_instance *element_list_pointer);

// Declaração das funcões relacionadas a geração de código
char *write_file_name(char name_array[][MAX], char type);
char *getPK(element_instance *list_pointer); 
char **write_array_type(int dimension, int i, char type_array[][MAX]);
void mount_method_insert(FILE *file_out, char name_array[][MAX],  char type_array[][MAX],int real_dimension, char primary_key[MAX]);
void mount_method_select(FILE *file_out, char name_array[][MAX], char type_array[][MAX], int real_dimension, char primary_key[MAX]);
void mount_method_select_all(FILE *file_out, char name_array[][MAX], char type_array[][MAX], int real_dimension, char primary_key[MAX]);
void mount_method_update(FILE *file_out, char name_array[][MAX], char type_array[][MAX], int real_dimension, char primary_key[MAX]);
void mount_method_delete(FILE *file_out, char name_array[][MAX], char type_array[][MAX], int real_dimension, char primary_key[MAX]);
void mount_method_specific_select(FILE *file_out, char name_array[][MAX], select_instance* select_list_pointer, char selected_fields_array[][MAX], char selected_fields_type_array[][MAX], int offset);
void write_java_file(element_instance *list_pointer, int dimension, char entity_name_validate[MAX]);
void write_java_DAO_file(element_instance *list_pointer, int dimension, char entity_name_validate[MAX], select_instance *select_list_pointer, selected_fields_instance *selected_fields_list_pointer);
void capitalize_name(char capitalized_name[MAX]);	

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

void insert_entity(entity_instance *list_pointer, element_instance *element_insert)
{
  entity_instance *new_entity, *first_entity;
  new_entity = (entity_instance*) malloc(sizeof(entity_instance));
  strcpy(new_entity->entity_name, element_insert->element_name);
  new_entity->element = element_insert;
  first_entity = list_pointer->next_entity;
  list_pointer->next_entity = new_entity;
  new_entity->next_entity = first_entity;
}

void insert_select(select_instance *list_pointer, int selection_fields, char entity_name[MAX])
{
	select_instance *new_select, *first_select;
	new_select = (select_instance*) malloc(sizeof(select_instance));
	new_select->selection_fields = selection_fields;
	new_select->validity = VALID;
	strcpy(new_select->entity_name, entity_name);
	first_select = list_pointer->next_select;
	list_pointer->next_select = new_select;
	new_select->next_select = first_select;
}

void insert_foreign_key(foreign_key_instance *list_pointer, char table[MAX], char table_primary_key[MAX], char foreign_key[MAX])
{
	foreign_key_instance *new_foreign_key, *first_foreign_key;
	new_foreign_key = (foreign_key_instance*) malloc(sizeof(foreign_key_instance));
	strcpy(new_foreign_key->table, table);
	strcpy(new_foreign_key->table_primary_key, table_primary_key);
	strcpy(new_foreign_key->foreign_key, foreign_key);
	first_foreign_key = list_pointer->next_foreign_key;
	list_pointer->next_foreign_key = new_foreign_key;
	new_foreign_key->next_foreign_key = first_foreign_key;
}

void insert_selected_fields(selected_fields_instance *list_pointer,char field_name[MAX])
{
	selected_fields_instance *new_selected_field, *first_selected_field;
	new_selected_field = (selected_fields_instance*) malloc(sizeof(selected_fields_instance));
	strcpy(new_selected_field->field_name, field_name);
	new_selected_field->select = NULL;
	new_selected_field->validity = INVALID;
	first_selected_field = list_pointer->next_selected_field;
	list_pointer->next_selected_field = new_selected_field;
	new_selected_field->next_selected_field = first_selected_field;
}

void create_entity_list(element_instance *list_pointer)
{
	if(list_pointer == NULL)
	{ 
		printf("There is no entity.\n");
		exit(1);
	}
	char entity_name_for_element[MAX];
	element_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_element;
	while(auxiliary_pointer != NULL)
	{		
    	if(auxiliary_pointer->element_scope == 0)
    	{
     		insert_entity(entity_list_pointer, auxiliary_pointer); 
     		strcpy(entity_name_for_element, auxiliary_pointer->element_name);
    	}
    	else{
    		strcpy(auxiliary_pointer->entity_name, entity_name_for_element);
    	}

		auxiliary_pointer = auxiliary_pointer->next_element;
	}
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
    	printf("%s\t",auxiliary_pointer->element_name);
		printf("%d\t",auxiliary_pointer->element_scope);
		printf("%s\t",auxiliary_pointer->element_type);
		if(auxiliary_pointer->element_scope == COLUMN)
		{
			printf("%s\t",auxiliary_pointer->entity_name);
		}
		printf("\n");
		auxiliary_pointer = auxiliary_pointer->next_element;
		elements_counter += 1;
	}
	return elements_counter;
}

void print_entity_list(entity_instance *list_pointer)
{
	if(list_pointer == NULL)
	{ 
		printf("There is no entity.\n");
		exit(1);
	}

	entity_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_entity;
	while(auxiliary_pointer != NULL)
	{		
    	printf("%s\n",auxiliary_pointer->entity_name);
		auxiliary_pointer = auxiliary_pointer->next_entity;
	}
}

void print_select_list(select_instance *list_pointer)
{
	if(list_pointer == NULL)
	{ 
		printf("There is no select.\n");
		exit(1);
	}

	select_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_select;
	while(list_pointer->next_select != NULL)
	{	
	    int validade_select = search_entity(list_pointer->next_select->entity_name);	
	    if(validade_select == FOUND)
	    {    
	      	printf("Select %d from %s.\n",list_pointer->next_select->selection_fields, list_pointer->next_select->entity_name);
	    }
	    else
	   	{
	   		list_pointer->next_select->validity = INVALID;
	    	printf("Select query doesnt have a valid entity.\n");
	    }
		list_pointer->next_select = list_pointer->next_select->next_select;
	}
	list_pointer->next_select = auxiliary_pointer;
}

void print_foreign_key_list(foreign_key_instance *list_pointer)
{
	if(list_pointer == NULL)
	{ 
		printf("There is no foreign key.\n");
		exit(1);
	}

	foreign_key_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_foreign_key;
	while(auxiliary_pointer != NULL)
	{	
	    printf("FOREIGN_KEY %s REFERENCES %s(%s) \n",auxiliary_pointer->foreign_key, auxiliary_pointer->table, auxiliary_pointer->table_primary_key);

		auxiliary_pointer = auxiliary_pointer->next_foreign_key;
	}
}

void print_selected_fields_list(selected_fields_instance *list_pointer)
{
	if(list_pointer == NULL)
	{ 
		printf("There is no selected fields.\n");
		exit(1);
	}

	selected_fields_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_selected_field;
	while(auxiliary_pointer != NULL)
	{	
		if(auxiliary_pointer->validity == VALID){
    		printf("%s\t", auxiliary_pointer->field_name);
    		printf("%s\n", auxiliary_pointer->select->entity_name);
    	}
    	else
    	{
    		printf("SELECT FIELD %s NOT VALID\n", auxiliary_pointer->field_name);
    	}
		auxiliary_pointer = auxiliary_pointer->next_selected_field;
	}
}

void associate_select_selected_fields(selected_fields_instance *selected_fields_list_pointer, select_instance *select_list_pointer)
{
	select_instance *auxiliary_select_pointer;
	auxiliary_select_pointer = select_list_pointer->next_select;
	selected_fields_instance *auxiliary_selected_fields_pointer;
	auxiliary_selected_fields_pointer = selected_fields_list_pointer->next_selected_field;
	while(select_list_pointer->next_select != NULL)
	{
		int i;
		for(i = 0; i < select_list_pointer->next_select->selection_fields; i++)
		{
			selected_fields_list_pointer->next_selected_field->select = select_list_pointer->next_select;
			selected_fields_list_pointer->next_selected_field = selected_fields_list_pointer->next_selected_field->next_selected_field;
		}
		select_list_pointer->next_select = select_list_pointer->next_select->next_select;
	}
	select_list_pointer->next_select = auxiliary_select_pointer;
	selected_fields_list_pointer->next_selected_field = auxiliary_selected_fields_pointer;
}

void validate_selected_fields(selected_fields_instance *selected_fields_list_pointer, element_instance *element_list_pointer)
{
	element_instance *auxiliary_element_pointer;
	auxiliary_element_pointer = element_list_pointer->next_element;
	selected_fields_instance *auxiliary_selected_fields_pointer;
	auxiliary_selected_fields_pointer = selected_fields_list_pointer->next_selected_field;
	while(selected_fields_list_pointer->next_selected_field != NULL)
	{
		while(auxiliary_element_pointer != NULL)
		{	
			if(strcmp(selected_fields_list_pointer->next_selected_field->field_name, "*") == 0)
			{
				if(strcmp(selected_fields_list_pointer->next_selected_field->select->entity_name, auxiliary_element_pointer->entity_name) == 0)
				{
					selected_fields_list_pointer->next_selected_field->validity = VALID;
					break;
				}
			}
			else
				{
					if(auxiliary_element_pointer->element_scope == COLUMN)
					{
						if(strcmp(selected_fields_list_pointer->next_selected_field->select->entity_name, auxiliary_element_pointer->entity_name) == 0
						&& strcmp(selected_fields_list_pointer->next_selected_field->field_name, auxiliary_element_pointer->element_name) == 0)
						{
							selected_fields_list_pointer->next_selected_field->validity = VALID;
							break;
						}
					}
				}
			auxiliary_element_pointer = auxiliary_element_pointer->next_element;	
		}
		auxiliary_element_pointer = element_list_pointer->next_element;
		selected_fields_list_pointer->next_selected_field = selected_fields_list_pointer->next_selected_field->next_selected_field;
	}
	selected_fields_list_pointer->next_selected_field = auxiliary_selected_fields_pointer;
}

char *write_file_name(char name_array[][MAX], char type)
{
	static char file_out_name[MAX], source_string[MAX];
	strcpy(file_out_name, name_array[0]);

	capitalize_name(file_out_name);

	if(type == 'm'){
		strcpy(source_string, ".java");
	}else{
		strcpy(source_string, "DAO.java");
	}
	strcat(file_out_name, source_string);

	return file_out_name;
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

int search_column(char entity_name_insert[MAX], element_instance *element_pointer)
{
	if(element_list_pointer == NULL)
    {
        return NOT_FOUND;
    }
    else
    {
        if ((strcmp(entity_name_insert, element_pointer->entity_name) == 0)
        	|| (strcmp(entity_name_insert, element_pointer->element_name) == 0))
        {
            return FOUND;
        }
        return NOT_FOUND;
    }
}

char **write_array_type(int dimension, int i, char type_array[][MAX])
{
    char** type_out =(char**)malloc(dimension*sizeof(char*));
	char integer_type[MAX];
	char varchar_type[MAX];
	char float_type[MAX];
	char table_type[MAX];

	strcpy(integer_type, "INT");
	strcpy(varchar_type, "VARCHAR");
	strcpy(float_type, "FLOAT");
	strcpy(table_type, "TABLE");

	for(i = 0; i < dimension; i++)
	{
		if((strcmp(type_array[i], table_type)) == 0)
		{
			type_out[i] = "table";
		}
		if((strcmp(type_array[i], integer_type)) == 0)
		{
			type_out[i] = "int";
		}		
		if((strcmp(type_array[i], varchar_type)) == 0)
		{
			type_out[i] = "String";
		}
		if((strcmp(type_array[i], float_type)) == 0)
		{
			type_out[i] = "float";
		}
	}
	return type_out;
}

// Recuperando PK
char *getPK(element_instance *list_pointer) 
{

	element_instance *auxiliary_pk;
	auxiliary_pk = list_pointer;
	int m = 0;
	static char primary_key[MAX];
	for (m = 0; auxiliary_pk != NULL; m++)
	{

		if(auxiliary_pk->element_scope == PRIMARY_KEY)
		{
			strcpy(primary_key, auxiliary_pk ->element_name);
		}

		if((auxiliary_pk->next_element == NULL) || (auxiliary_pk->next_element->element_scope == 0))
		{
			break;
		}

		auxiliary_pk = auxiliary_pk->next_element;
	}

	return primary_key;
}

// Validando PK	
int is_pk(element_instance *list_pointer, char primary_key[MAX])
{

	element_instance *auxiliary_pkey;
	auxiliary_pkey = list_pointer;
	int found = 0;
	int n = 0;
	for (n = 0; auxiliary_pkey != NULL; n++)
	{
		if(auxiliary_pkey->element_scope == COLUMN)
		{
			int validate_pk = search_column(primary_key, auxiliary_pkey);
			if(validate_pk == FOUND)
			{
				found = 1;
			}
		}

		if((auxiliary_pkey->next_element == NULL) || (auxiliary_pkey->next_element->element_scope == 0))
		{
			break;
		}

	 	auxiliary_pkey = auxiliary_pkey->next_element;
	 }

	 return found;
}



void write_java_file(element_instance *list_pointer, int dimension, char entity_name_validate[MAX])
{
	FILE *file_out;
	char name_array[dimension][MAX];
	char name_upcase[dimension][MAX];
	char type_array[dimension][MAX];
	int i, real_dimension = 0;

	if(list_pointer == NULL)
	{
		printf("There is no instance.\n");
		exit(1);
	}

	char *primary_key;
	primary_key = getPK(list_pointer);


	int found = is_pk(list_pointer, primary_key);

	 // Imprime mensagens de erro caso PK não exista na tabela
	 if(found == 0){
	 	printf("\nThis field: %s, does not exist! Please check your sql file.\n", primary_key);
		exit(1);
	 }

	element_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer;
	for(i = 0; auxiliary_pointer != NULL; i++)
	{
		// Validando se a coluna existe na entidade
		int validate_column = search_column(entity_name_validate, auxiliary_pointer);
		if(validate_column == FOUND)
		{
			if(auxiliary_pointer->element_scope != PRIMARY_KEY){

				strcpy(name_array[i], auxiliary_pointer->element_name);
				strcpy(type_array[i], auxiliary_pointer->element_type);
				real_dimension++;
			}
		}

		else{
			printf("ERROR! Element does not belong in entity %s.", entity_name_validate);
		}

		if(auxiliary_pointer->next_element == NULL)
		{
			break;
		}
		else if(auxiliary_pointer->next_element->element_scope == 0)
		{
			break;
		}

		auxiliary_pointer = auxiliary_pointer->next_element;
	}

	char **type_out;
	type_out = write_array_type(dimension, i, type_array);


	char *file_out_name; 
	file_out_name = write_file_name(name_array, 'm');

	char folder_name[MAX];
	strcpy(folder_name, "Model/");
	strcat(folder_name,file_out_name);

	char entity_name_pascalcase[MAX];
	strcpy(entity_name_pascalcase, name_array[0]);
	capitalize_name(entity_name_pascalcase);

	printf("Writing java file for entity %s...\n",entity_name_pascalcase);
	file_out = fopen(folder_name, "w");

	if(!file_out)
	{
		printf("I can't open java file called %s.\n", file_out_name);
		exit(1);
	}

	fprintf(file_out, "public class %s {\n", entity_name_pascalcase);
	fprintf(file_out, "\n");

	for(i = 1; i < real_dimension; i ++)
	{
		fprintf(file_out, "	private %s %s;\n", type_out[i], name_array[i]);
	}

	fprintf(file_out, "\n");
	fprintf(file_out, "	public %s() {\n", entity_name_pascalcase);
	fprintf(file_out, "\n");
	fprintf(file_out, "	}\n\n");

	//Escrevendo Gettings
	for(i = 1; i < real_dimension; i ++)
	{	
		//Transformando primeiro char em maiusculo
		strcpy(name_upcase[i], name_array[i]);
		name_upcase[i][0] = toupper(name_array[i][0]);
		
		fprintf(file_out, "	public %s get%s () {\n", type_out[i], name_upcase[i]);
		fprintf(file_out, "\t\treturn this.%s;\n", name_array[i]);
		fprintf(file_out, "	}\n\n");
	}

	//Escrevendo Settings
	for(i = 1; i < real_dimension; i ++)
	{
		//Transformando primeiro char em maiusculo
		strcpy(name_upcase[i], name_array[i]);
		name_upcase[i][0] = toupper(name_array[i][0]);
		
		fprintf(file_out, "	public void set%s (%s %s) {\n", name_upcase[i], type_out[i], name_array[i]);
		fprintf(file_out, "\t\tthis.%s = %s;\n", name_array[i], name_array[i]);
		fprintf(file_out, "	}\n\n");		
	}

	//Fechando classe
	fprintf(file_out, "}");

	printf("Writing java file for entity %s completed.\n",entity_name_pascalcase);

	fclose(file_out);
}

void capitalize_name(char capitalized_name[MAX])
{
	capitalized_name[0] = toupper(capitalized_name[0]);
}

void uncapitalize_name(char uncapitalized_name[MAX])
{
	uncapitalized_name[0] = tolower(uncapitalized_name[0]);
}

void mount_method_insert(FILE *file_out, char name_array[][MAX],  char type_array[][MAX],int real_dimension, char primary_key[MAX])
{	
	// Capitalizing names
	char capital_entity_name[MAX];
	strcpy(capital_entity_name, name_array[0]);
	capitalize_name(capital_entity_name);

	char lowercase_entity_name[MAX];
	strcpy(lowercase_entity_name, name_array[0]);
	uncapitalize_name(lowercase_entity_name);

	char capital_primary_key[MAX];
	strcpy(capital_primary_key, primary_key);
	capitalize_name(capital_primary_key);

	//Escrevendo carcaça do método INSERT
	fprintf(file_out, "	public void insert(%s %s) throws SQLException {\n", capital_entity_name, lowercase_entity_name);
	fprintf(file_out, "\t\t\tString sql = 'INSERT INTO %s (", name_array[0]);

	// fprintf(file_out, "\t\t\tString sql = 'INSERT INTO %s (s, s) VALUE (?, ?)';\n", name_array[0]);

	int i = 0; 
	for (i = 1; i < real_dimension; ++i)
	{
		if (i != (real_dimension - 1))
		{
			fprintf(file_out, "%s, ", name_array[i]);	
		}
		else
		{
			fprintf(file_out, "%s)", name_array[i]);	
		}
		
	}

	fprintf(file_out, " VALUE (");

	int j = 0;
	for (j = 1; j < real_dimension; ++j)
	{
		
		if(j != (real_dimension - 1))
		{
			fprintf(file_out, "?, ", name_array[j]);	
		}
		else
		{
			fprintf(file_out, "?)';\n", name_array[j]);	
		}
		
	}

	fprintf(file_out, "\t\t\tPreparedStatement statement = conn.preparedStatement(sql);\n");
	
	// Setting values to statement
	int l = 1;
	for(l = 1; l<real_dimension; l++)
	{
			char capital_column_name[MAX];
			strcpy(capital_column_name, name_array[l]);
			capitalize_name(capital_column_name);

			if(strcmp(type_array[l], "INT") == 0)
			{

				fprintf(file_out, "\t\t\tstatement.setInt(%d, %s.get%s());\n", l, lowercase_entity_name, capital_column_name);
			}
			else if(strcmp(type_array[j], "FLOAT") == 0)
			{

				fprintf(file_out, "\t\t\tstatement.setFloat(%d, %s.get%s());\n", l, lowercase_entity_name, capital_column_name);
			}
			else{

				fprintf(file_out, "\t\t\tstatement.setString(%d, %s.get%s());\n", l, lowercase_entity_name, capital_column_name);
			}

	}

	fprintf(file_out, "\t\t\tint rowsInserted = statement.executeUpdate();\n");
	fprintf(file_out, "\t\t\tif (rowsInserted > 0) {\n");
	fprintf(file_out, "\t\t\t\tSystem.out.println('A new %s was inserted successfully!');\n", lowercase_entity_name);
	fprintf(file_out, "\t\t\t}\n");
	fprintf(file_out, "\t\t}");

}

void mount_method_update(FILE *file_out, char name_array[][MAX], char type_array[][MAX], int real_dimension, char primary_key[MAX])
{	
	char entity_name_pascalcase[MAX];
	strcpy(entity_name_pascalcase, name_array[0]);
	capitalize_name(entity_name_pascalcase);

	char lowercase_entity_name[MAX];
	strcpy(lowercase_entity_name, name_array[0]);
	uncapitalize_name(lowercase_entity_name);

	char capital_primary_key[MAX];
	strcpy(capital_primary_key, primary_key);
	capitalize_name(capital_primary_key);
	int i = 0;

	int k = 0;
	char **type_out;
	type_out = write_array_type(real_dimension, k, type_array);


	// Refatorar método de buscar primary key
	char type_primary_key[MAX];
	for(k = 0; k < real_dimension; k++){
		if(strcmp(name_array[k],primary_key) == 0){
			strcpy(type_primary_key, type_out[k]);
		}
	}

	char capital_type_primary_key[MAX];
	strcpy(capital_type_primary_key, type_primary_key);
	capitalize_name(capital_type_primary_key);

	fprintf(file_out, "	public void update(%s %s) throws SQLException {\n", entity_name_pascalcase, lowercase_entity_name);
	fprintf(file_out, "\t\t\tString sql = 'UPDATE %s SET' +\n", name_array[0]);
	
	for(i = 1; i<real_dimension; i++)
	{
		if(strcmp(name_array[i],primary_key) != 0)
		{
			fprintf(file_out, "\t\t\t'%s=?' +\n", name_array[i]);	
		}
	}
	
	fprintf(file_out, "\t\t\t'WHERE %s=?';\n", primary_key);
	fprintf(file_out, "\t\t\tPreparedStatement statement = conn.preparedStatement(sql);\n");
	
	int j = 1;
	for(i = 1; i<real_dimension; i++)
	{
		if(strcmp(name_array[i],primary_key) != 0)
		{
			char capital_column_name[MAX];
			strcpy(capital_column_name, name_array[i]);
			capitalize_name(capital_column_name);

			char capital_type_column[MAX];
			strcpy(capital_type_column, type_out[i]);
			capitalize_name(capital_type_column);

			fprintf(file_out, "\t\t\tstatement.set%s(%d, %s.get%s());\n", capital_type_column, j, lowercase_entity_name, capital_column_name);
			j++;
		}
	}
	fprintf(file_out, "\t\t\tstatement.set%s(%d, %s.get%s());\n", capital_type_primary_key, real_dimension-1, lowercase_entity_name, capital_primary_key);
	fprintf(file_out, "\t\t\tint rowsInserted = statement.executeUpdate();\n");
	fprintf(file_out, "\t\t\tif (rowsInserted > 0) {\n");
	fprintf(file_out, "\t\t\t\tSystem.out.println('An existing %s was updated successfully!');\n", lowercase_entity_name);
	fprintf(file_out, "\t\t\t}\n");
	fprintf(file_out, "\t\t}");
		
}

void mount_method_delete(FILE *file_out, char name_array[][MAX], char type_array[][MAX], int real_dimension, char primary_key[MAX])
{	
	char entity_name_pascalcase[MAX];
	strcpy(entity_name_pascalcase, name_array[0]);
	capitalize_name(entity_name_pascalcase);

	char lowercase_entity_name[MAX];
	strcpy(lowercase_entity_name, name_array[0]);
	uncapitalize_name(lowercase_entity_name);

	char capital_primary_key[MAX];
	strcpy(capital_primary_key, primary_key);
	capitalize_name(capital_primary_key);

	int k = 0;
	char **type_out;
	type_out = write_array_type(real_dimension, k, type_array);

	char type_primary_key[MAX];

	for(k = 0; k < real_dimension; k++){
		if(strcmp(name_array[k],primary_key) == 0){
			strcpy(type_primary_key, type_out[k]);
		}
	}

	char capital_type_primary_key[MAX];
	strcpy(capital_type_primary_key, type_primary_key);
	capitalize_name(capital_type_primary_key);

	fprintf(file_out, "	public void delete(%s %s) throws SQLException {\n", entity_name_pascalcase, lowercase_entity_name);
	fprintf(file_out, "\t\t\tString sql = 'DELETE FROM %s WHERE %s=?';\n", name_array[0], primary_key);
	fprintf(file_out, "\t\t\tPreparedStatement statement = conn.preparedStatement(sql);\n");
	
	char capital_column_name[MAX];
	strcpy(capital_column_name, primary_key);
	capitalize_name(capital_column_name);
	fprintf(file_out, "\t\t\tstatement.set%s(1, %s.get%s());\n", capital_type_primary_key, lowercase_entity_name, capital_column_name);
	
	fprintf(file_out, "\t\t\tint rowsInserted = statement.executeUpdate();\n");
	fprintf(file_out, "\t\t\tif (rowsInserted > 0) {\n");
	fprintf(file_out, "\t\t\t\tSystem.out.println('An existing %s was deleted successfully!');\n", lowercase_entity_name);
	fprintf(file_out, "\t\t\t}\n");
	fprintf(file_out, "\t\t}");
		
}

void mount_method_select(FILE *file_out, char name_array[][MAX], char type_array[][MAX], int real_dimension, char primary_key[MAX])
{	
	char entity_name_pascalcase[MAX];
	strcpy(entity_name_pascalcase, name_array[0]);
	capitalize_name(entity_name_pascalcase);

	char lowercase_entity_name[MAX];
	strcpy(lowercase_entity_name, name_array[0]);
	uncapitalize_name(lowercase_entity_name);

	char capital_primary_key[MAX];
	strcpy(capital_primary_key, primary_key);
	capitalize_name(capital_primary_key);

	int k = 0;
	char **type_out;
	type_out = write_array_type(real_dimension, k, type_array);

	char type_primary_key[MAX];

	for(k = 0; k < real_dimension; k++){
		if(strcmp(name_array[k],primary_key) == 0){
			strcpy(type_primary_key, type_out[k]);
		}
	}

	char capital_type_primary_key[MAX];
	strcpy(capital_type_primary_key, type_primary_key);
	capitalize_name(capital_type_primary_key);
	//Escrevendo carcaça do método INSERT
	fprintf(file_out, "	public %s select(%s %s) throws SQLException {\n",entity_name_pascalcase, type_primary_key, primary_key);
	fprintf(file_out, "\t\tString sql = 'SELECT * FROM %s WHERE %s = ?';\n", entity_name_pascalcase, primary_key);
	fprintf(file_out, "\t\t%s %s = new %s();\n", entity_name_pascalcase, lowercase_entity_name, entity_name_pascalcase);
	fprintf(file_out, "\t\tPreparedStatement statement = conn.preparedStatement(sql);\n");
	fprintf(file_out, "\t\tstatement.set%s(1, %s);\n", capital_type_primary_key, primary_key);
	fprintf(file_out, "\t\tResultSet result = statement.executeQuery(sql);\n");
	//Vai ser um for
	fprintf(file_out, "\t\twhile (result.next()) {\n");
	int i = 0,j = 1;
	for(i = 1; i<real_dimension; i++)
	{
		char capital_column_name[MAX];
		strcpy(capital_column_name, name_array[i]);
		capitalize_name(capital_column_name);

		char capital_type_column[MAX];
		strcpy(capital_type_column, type_out[i]);
		capitalize_name(capital_type_column);

		fprintf(file_out, "\t\t\t%s.set%s(result.get%s(%d));\n", lowercase_entity_name, capital_column_name, capital_type_column, i);
		j++;
	}
	fprintf(file_out, "\t\t}\n");
	fprintf(file_out, "\t\treturn %s;\n", lowercase_entity_name);
	
	fprintf(file_out, "\t}");
		
}

void mount_method_select_all(FILE *file_out, char name_array[][MAX], char type_array[][MAX], int real_dimension, char primary_key[MAX])
{	
	char entity_name_pascalcase[MAX];
	strcpy(entity_name_pascalcase, name_array[0]);
	capitalize_name(entity_name_pascalcase);

	char lowercase_entity_name[MAX];
	strcpy(lowercase_entity_name, name_array[0]);
	uncapitalize_name(lowercase_entity_name);

	char capital_primary_key[MAX];
	strcpy(capital_primary_key, primary_key);
	capitalize_name(capital_primary_key);

	int k = 0;
	char **type_out;
	type_out = write_array_type(real_dimension, k, type_array);

	char type_primary_key[MAX];

	for(k = 0; k < real_dimension; k++){
		if(strcmp(name_array[k],primary_key) == 0){
			strcpy(type_primary_key, type_out[k]);
		}
	}

	char capital_type_primary_key[MAX];
	strcpy(capital_type_primary_key, type_primary_key);
	capitalize_name(capital_type_primary_key);
	//Escrevendo carcaça do método INSERT
	fprintf(file_out, "	public ArrayList<%s> selectAll() throws SQLException {\n",entity_name_pascalcase);
	fprintf(file_out, "\t\tString sql = 'SELECT * FROM %s';\n", entity_name_pascalcase);
	fprintf(file_out, "\t\tArrayList<%s> %ss = new ArrayList<>();\n", entity_name_pascalcase, lowercase_entity_name);
	fprintf(file_out, "\t\tPreparedStatement statement = conn.preparedStatement(sql);\n");
	fprintf(file_out, "\t\tResultSet result = statement.executeQuery(sql);\n");

	fprintf(file_out, "\t\twhile (result.next()) {\n");
	fprintf(file_out, "\t\t\t%s %s = new %s();\n", entity_name_pascalcase, lowercase_entity_name, entity_name_pascalcase);

	int i = 0,j = 1;
	for(i = 1; i<real_dimension; i++)
	{
		char capital_column_name[MAX];
		strcpy(capital_column_name, name_array[i]);
		capitalize_name(capital_column_name);

		char capital_type_column[MAX];
		strcpy(capital_type_column, type_out[i]);
		capitalize_name(capital_type_column);

		fprintf(file_out, "\t\t\t%s.set%s(result.get%s(%d));\n", lowercase_entity_name, capital_column_name, capital_type_column, i);
		j++;
	}
	fprintf(file_out, "\t\t\tif (%s != null) {\n", lowercase_entity_name);
	fprintf(file_out, "\t\t\t\t%ss.add(%s);\n", lowercase_entity_name, lowercase_entity_name);
	fprintf(file_out, "\t\t\t}\n");
	fprintf(file_out, "\t\t}\n");
	fprintf(file_out, "\t\treturn %ss;\n", lowercase_entity_name);
	
	fprintf(file_out, "\t}");
		
}

void mount_method_specific_select(FILE *file_out, char name_array[][MAX], select_instance* select_list_pointer_write, char selected_fields_array[][MAX], char selected_fields_type_array[][MAX], int offset)
{

	char entity_name_pascalcase[MAX];
	strcpy(entity_name_pascalcase, name_array[0]);
	capitalize_name(entity_name_pascalcase);

	char lowercase_entity_name[MAX];
	strcpy(lowercase_entity_name, name_array[0]);
	uncapitalize_name(lowercase_entity_name);

	int k = 0;
	char **type_out;
	type_out = write_array_type(select_list_pointer_write->selection_fields, k, selected_fields_type_array);

	fprintf(file_out, "	public ArrayList<%s> select",entity_name_pascalcase);
	int z;
	for(z = offset; z < offset + select_list_pointer_write->selection_fields; z++)
	{
		char capital_column[MAX];
		strcpy(capital_column, selected_fields_array[z]);
		capitalize_name(capital_column);

		fprintf(file_out, "%s", capital_column);
	}
	fprintf(file_out, "All() throws SQLException {\n");
	fprintf(file_out, "\t\tString sql = 'SELECT ");
	for(z = offset; z < offset + select_list_pointer_write->selection_fields; z++)
	{
		fprintf(file_out, "%s", selected_fields_array[z]);
		if(z != (offset + select_list_pointer_write->selection_fields - 1))
			fprintf(file_out, ",");
	}
	fprintf(file_out, " FROM %s';\n", entity_name_pascalcase);
	fprintf(file_out, "\t\tArrayList<%s> %ss = new ArrayList<>();\n", entity_name_pascalcase, lowercase_entity_name);
	fprintf(file_out, "\t\tPreparedStatement statement = conn.preparedStatement(sql);\n");
	fprintf(file_out, "\t\tResultSet result = statement.executeQuery(sql);\n"); 

	fprintf(file_out, "\t\twhile (result.next()) {\n");
	fprintf(file_out, "\t\t\t%s %s = new %s();\n", entity_name_pascalcase, lowercase_entity_name, entity_name_pascalcase);

	int i = 0,j = 1;
	for(i = 0; i < select_list_pointer_write->selection_fields; i++)
	{
		char capital_column_name[MAX];
		strcpy(capital_column_name, selected_fields_array[i]);
		capitalize_name(capital_column_name);

		char capital_type_column[MAX];
		strcpy(capital_type_column, type_out[i]);
		capitalize_name(capital_type_column);

		fprintf(file_out, "\t\t\t%s.set%s(result.get%s(%d));\n", lowercase_entity_name, capital_column_name, capital_type_column, i);
		j++;
	}
	fprintf(file_out, "\t\t\tif (%s != null) {\n", lowercase_entity_name);
	fprintf(file_out, "\t\t\t\t%ss.add(%s);\n", lowercase_entity_name, lowercase_entity_name);
	fprintf(file_out, "\t\t\t}\n");
	fprintf(file_out, "\t\t}\n");
	fprintf(file_out, "\t\treturn %ss;\n", lowercase_entity_name);
	
	fprintf(file_out, "\t}");

}

void write_java_DAO_file(element_instance *list_pointer, int dimension, char entity_name_validate[MAX], select_instance *select_list_pointer, selected_fields_instance *selected_fields_list_pointer)
{
  	char name_array[dimension][MAX];
	char name_upcase[dimension][MAX];
	char type_array[dimension][MAX];
	char primary_key[MAX];
	int i, real_dimension = 0;

	if(list_pointer == NULL)
	{
		printf("There is no instance.\n");
		exit(1);
	}

	element_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer;
	for(i = 0; auxiliary_pointer != NULL; i++)
	{
		int validate_column = search_column(entity_name_validate, auxiliary_pointer);
		if(validate_column == FOUND)
		{
			if(auxiliary_pointer->element_scope == PRIMARY_KEY)
			{
				strcpy(primary_key, auxiliary_pointer->element_name);
			}
			else
			{
				strcpy(name_array[i], auxiliary_pointer->element_name);
				strcpy(type_array[i], auxiliary_pointer->element_type);
				real_dimension++;
			}

		}
		else
		{
			printf("ERROR! Element does not belong in entity %s.", entity_name_validate);
		}	

		if(auxiliary_pointer->next_element == NULL)
		{
			break;
		}
		else if(auxiliary_pointer->next_element->element_scope == 0)
		{
			break;
		}

		auxiliary_pointer = auxiliary_pointer->next_element;
	}

	int number_specific_selects = 0;
	int number_of_selected_fields = 0;
	select_instance *auxiliary_select_pointer;
	auxiliary_select_pointer = select_list_pointer->next_select;

	while(auxiliary_select_pointer != NULL)
	{
		if(strcmp(auxiliary_select_pointer->entity_name, name_array[0]) == 0)
		{
			number_specific_selects++;
			number_of_selected_fields = number_of_selected_fields + auxiliary_select_pointer->selection_fields;
		}
		auxiliary_select_pointer = auxiliary_select_pointer->next_select;
	}

	selected_fields_instance *auxiliary_selected_list;
	auxiliary_selected_list = selected_fields_list_pointer->next_selected_field;

	char selected_fields_array[number_of_selected_fields][MAX];

	int counter = 0;
	while(auxiliary_selected_list != NULL)
	{
		if(strcmp(auxiliary_selected_list->select->entity_name, name_array[0]) == 0)
		{
			strcpy(selected_fields_array[counter], auxiliary_selected_list->field_name);
			counter++;
		}
		auxiliary_selected_list = auxiliary_selected_list->next_selected_field;
	}

	char selected_fields_type_array[number_of_selected_fields][MAX];

	int type_counter;

	for(type_counter = 0; type_counter < number_of_selected_fields; type_counter++)
	{
		auxiliary_pointer = list_pointer;
		while(auxiliary_pointer != NULL)
	{
		if((strcmp(auxiliary_pointer->element_name, selected_fields_array[type_counter]) == 0) &&
			auxiliary_pointer->element_scope == COLUMN)
		{
			strcpy(selected_fields_type_array[type_counter], auxiliary_pointer->element_type);
		}

		if(auxiliary_pointer->next_element == NULL)
		{
			break;
		}
		else if(auxiliary_pointer->next_element->element_scope == 0)
		{
			break;
		}

		auxiliary_pointer = auxiliary_pointer->next_element;
		}
	}

	FILE *file_out;
	char *file_out_name; 
  
	file_out_name = write_file_name(name_array, 'd');

	char folder_name[MAX];
	strcpy(folder_name, "DAO/");
	strcat(folder_name,file_out_name);

	char entity_name_pascalcase[MAX];
	strcpy(entity_name_pascalcase, name_array[0]);
	capitalize_name(entity_name_pascalcase);

	printf("Writing java %sDAO file...\n", entity_name_pascalcase);
	file_out = fopen(folder_name, "w");

	if(!file_out)
	{
		printf("I can't open javaDAO file.\n");
		exit(1);
	}

	// Escrita dos imports
	fprintf(file_out, "import java.sql.PreparedStatement;\n");
	fprintf(file_out, "import java.sql.ResultSet;\n");
	fprintf(file_out, "import java.sql.SQLException;\n");
	fprintf(file_out, "import java.sql.DriverManager;\n");
	fprintf(file_out, "import java.util.ArrayList;\n\n");

	fprintf(file_out, "public class %sDAO {\n", entity_name_pascalcase);
	fprintf(file_out, "\n");

	fprintf(file_out, "\tprivate Connection conn = DriverManager.getConnection(dbURL, username, password);");
	fprintf(file_out, "\n\n");

	mount_method_insert(file_out, name_array, type_array, real_dimension, primary_key);
	fprintf(file_out, "\n\n");

	mount_method_select(file_out, name_array, type_array, real_dimension, primary_key);
	fprintf(file_out, "\n\n");

	mount_method_select_all(file_out, name_array, type_array, real_dimension, primary_key);
	fprintf(file_out, "\n\n");

	mount_method_update(file_out, name_array, type_array, real_dimension, primary_key);
	fprintf(file_out, "\n\n");

	mount_method_delete(file_out, name_array, type_array, real_dimension, primary_key);
	fprintf(file_out, "\n\n");
	select_instance *auxiliary_select_pointer_write;
	auxiliary_select_pointer_write = select_list_pointer->next_select;

	int offset = 0;

	while(auxiliary_select_pointer_write != NULL)
	{
		if(strcmp(auxiliary_select_pointer_write->entity_name, name_array[0]) == 0)
		{
			mount_method_specific_select(file_out, name_array, auxiliary_select_pointer_write, selected_fields_array, selected_fields_type_array, offset);
			fprintf(file_out, "\n\n");
			offset = offset + auxiliary_select_pointer_write->selection_fields;
		}
		auxiliary_select_pointer_write = auxiliary_select_pointer_write->next_select;
	}

	fprintf(file_out, "\n}");

	printf("Writing java %sDAO file completed.\n",entity_name_pascalcase);

	free(auxiliary_select_pointer);
	free(auxiliary_selected_list);
}

void split(char select_fields[MAX], char select_fields_array[][MAX])
{
    char * char_pointer;
    char_pointer = strtok (select_fields," ,.-");
    int i = 0;
    while (char_pointer != NULL)
    { 
        strcpy(select_fields_array[i], char_pointer);
        char_pointer = strtok (NULL, " ,.-");
        i++;
    }
}

#endif
