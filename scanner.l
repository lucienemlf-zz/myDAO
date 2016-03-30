%{
	#include "common.h"
	#include "parser.tab.h"
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
"VARCHAR" { return T_VARCHAR; }
"INT" { return T_INT; }
"FLOAT" { return T_FLOAT; }
[\(\)\{\}:;=,] {return yytext[0];}

{STRING} { return D_STRING; }
{INTEGER} { return D_INTEGER; }
{FLOAT} { return D_FLOAT; }

{ANY_CHAR} {
	printf("Unexpected character in input: '%c' (ASCII=%d)\n", yytext[0], yytext[0]);
}


%% /* Código C */

