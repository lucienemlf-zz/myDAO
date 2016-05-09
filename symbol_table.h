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

//Structure for Entities
struct entity 
{
  char entity_name[MAX];
  struct element *element;
  struct entity *next_entity;
};

//Structures
typedef struct element element_instance;
typedef struct entity entity_instance;

//Pointers
element_instance *element_list_pointer;
entity_instance *entity_list_pointer;

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

void create_entity_list(element_instance *list_pointer)
{
	if(list_pointer == NULL)
	{ 
		printf("There is no entity.\n");
		exit(1);
	}

	element_instance *auxiliary_pointer;
	auxiliary_pointer = list_pointer->next_element;
	while(auxiliary_pointer != NULL)
	{		
    if(auxiliary_pointer->element_scope == 0)
    {
     insert_entity(entity_list_pointer, auxiliary_pointer); 
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
    printf("%s\n",auxiliary_pointer->element_name);
		printf("%d\n",auxiliary_pointer->element_scope);
		printf("%s\n",auxiliary_pointer->element_type);

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

char *write_file_name(char name_array[][MAX], char type)
{
	static char file_out_name[MAX], source_string[MAX];
	strcpy(file_out_name, name_array[0]);

	if(type == 'm'){
		strcpy(source_string, ".java");
	}else{
		strcpy(source_string, "DAO.java");
	}
	strcat(file_out_name, source_string);

printf("\n\nDEU CERTO ATE AQUI %s\n\n", file_out_name);	
	return file_out_name;
}

void write_java_file(element_instance *list_pointer, int dimension)
{
	FILE *file_out;
	char type_out[dimension][MAX];
	char name_array[dimension][MAX];
	char name_upcase[dimension][MAX];
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

	char *file_out_name; 
	file_out_name = write_file_name(name_array, 'm');

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
	fprintf(file_out, "	}\n\n");


	//Escrevendo Gettings
	for(i = 1; i < dimension; i ++)
	{	
		//Transformando primeiro char em maiusculo
		strcpy(name_upcase[i], name_array[i]);
		name_upcase[i][0] = toupper(name_array[i][0]);
		
		fprintf(file_out, "	public %s get%s () {\n", type_out[i], name_upcase[i]);
		fprintf(file_out, "\t\treturn this.%s;\n", name_array[i]);
		fprintf(file_out, "	}\n\n");
	}

	//Escrevendo Settings
	for(i = 1; i < dimension; i ++)
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

	printf("Writing java file completed.\n");

	fclose(file_out);
}


void mount_method_insert(FILE *file_out)
{	
	
	//Escrevendo carcaça do método INSERT
	fprintf(file_out, "	public void inserir(s s) {\n");
	fprintf(file_out, "\t\tString sql = 'INSERT INTO s (s, s) VALUE (?, ?)';\n");//Vai ser um for
	fprintf(file_out, "\t\tPreparedStatement statement = conn.preparedStatement(sql);\n");
	//Vai ser um for
		fprintf(file_out, "\t\tstatement.setString(1, 'Teste 1');\n");
		fprintf(file_out, "\t\tstatement.setString(2, 'Teste 2');\n");
	
	fprintf(file_out, "\t\tint rowsInserted = statement.executeUpdate();\n");
	fprintf(file_out, "\t\tif (rowsInserted > 0) {\n");
	fprintf(file_out, "\t\t\tSystem.out.println('A new user was inserted successfully!');\n");
	fprintf(file_out, "\t\t}\n");
	fprintf(file_out, "\t}");

}

void mount_method_update(FILE *file_out)
{	
	
	//Escrevendo carcaça do método update
	fprintf(file_out, "	public void autalizar(S s) {\n");
	fprintf(file_out, "\t\tString sql = 'UPDATE s SET column1=?, column2=? WHERE username=?';\n");//Vai ser um for
	fprintf(file_out, "\t\tPreparedStatement statement = conn.preparedStatement(sql);\n");
	//Vai ser um for
		fprintf(file_out, "\t\tstatement.setString(1, 'Teste 1');\n");
		fprintf(file_out, "\t\tstatement.setString(2, 'Teste 2');\n");
	
	fprintf(file_out, "\t\tint rowsInserted = statement.executeUpdate();\n");
	fprintf(file_out, "\t\tif (rowsInserted > 0) {\n");
	fprintf(file_out, "\t\t\tSystem.out.println('An existing user was updated successfully!');\n");
	fprintf(file_out, "\t\t}\n");
	fprintf(file_out, "\t}");
		
}

void mount_method_delete(FILE *file_out)
{	
	
	//Escrevendo carcaça do método excluir
	fprintf(file_out, "	public void excluir(User user) {\n");
	fprintf(file_out, "\t\tString sql = 'DELETE FROM User WHERE username=?';\n");//Vai ser um for
	fprintf(file_out, "\t\tPreparedStatement statement = conn.preparedStatement(sql);\n");
	
	fprintf(file_out, "\t\tstatement.setString(1, user);\n");
	
	fprintf(file_out, "\t\tint rowsInserted = statement.executeUpdate();\n");
	fprintf(file_out, "\t\tif (rowsInserted > 0) {\n");
	fprintf(file_out, "\t\t\tSystem.out.println('An existing user was deleted successfully!');\n");
	fprintf(file_out, "\t\t}\n");
	fprintf(file_out, "\t}");
		
}


void mount_method_select(FILE *file_out)
{	

	//Escrevendo carcaça do método INSERT
	fprintf(file_out, "	public void selecionar(s s) {\n");
	fprintf(file_out, "\t\tString sql = 'SELECT * FROM Users';\n");
	fprintf(file_out, "\t\tStatement statement = conn.createStatement();\n");
	fprintf(file_out, "\t\tResultSet result = statement.executeQuery(sql);\n");
	fprintf(file_out, "\t\tint count = 0;\n");

		//Vai ser um for
		fprintf(file_out, "\t\twhile (result.next()) {\n");
		fprintf(file_out, "\t\t\tString name = result.getString(2);\n");
		fprintf(file_out, "\t\t\tString fullname = result.getString('fullname');\n");
		fprintf(file_out, "\t\t}\n");
	
	fprintf(file_out, "\t\tString output = 'User #Teste: Teste1 - Teste2';\n");
	fprintf(file_out, "\t\tSystem.out.println(String.format(output, ++count, name, fullname));\n");
	fprintf(file_out, "\t}");
		
}

void write_java_DAO_file(element_instance *list_pointer, int dimension)
{

	FILE *file_out;
	char *file_out_name; 
char name_array[dimension][MAX];  // Apagar quando refatorar
strcpy(name_array[0], "pessoa");
	file_out_name = write_file_name(name_array, 'd');

	printf("Writing java insertDAO file...\n");
	file_out = fopen(file_out_name, "w");

	if(!file_out)
	{
		printf("I can't open javaDAO file.\n");
		exit(1);
	}	

	mount_method_insert(file_out);
	fprintf(file_out, "\n\n");

	mount_method_select(file_out);
	fprintf(file_out, "\n\n");

	mount_method_update(file_out);
	fprintf(file_out, "\n\n");

	mount_method_delete(file_out);

}

#endif
