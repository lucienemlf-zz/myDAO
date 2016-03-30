%{
	#include "common.h"
	//#include "parser.h"
	#include <stdio.h>
%}

/* Definições */

STRING [a-z][a-z0-9]*
WHITESPACE [ \n\r\t]+
FLOAT [0-9]+\.[0-9]+
INTEGER [0-9]+
ANY_CHAR .

%% /* Regras */

{WHITESPACE} /* Ignore */ ;
 
"CREATE" { return T_CREATE; }
"TABLE" { return T_TABLE; } 
{STRING} { return D_STRING; }
{INTEGER} { return D_INTEGER; }
{FLOAT} { return D_FLOAT; }


"VARCHAR" { return T_VARCHAR; }
"INT" { return T_INT; }
"FLOAT" { return T_FLOAT; }
 
"," { return T_COMMA; }
";" { return T_SEMICOLON; }
"( " {return T_OPEN_PARENTHESIS; } 
") " {return T_CLOSE_PARENTHESIS; } 

{ANY_CHAR} {
	printf("Unexpected character in input: '%c' (ASCII=%d)\n", yytext[0], yytext[0]);
}


%% /* Código C */


main(){
	yylex();
}


yywrap () {
	return 0;
}
