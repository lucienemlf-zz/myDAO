%{
	#include "common.h"
	#include "parser.tab.h"
%}

/* Definições */

STRING [a-zA-Z][a-z0-9]*
WHITESPACE [ \n\r\t]+
FLOAT [0-9]+\.[0-9]+
INTEGER [0-9]+
IGNORE (UNIQUE|CHECK|DEFAULT)
ANY_CHAR .

%% /* Regras */

{WHITESPACE} /* Ignore */ ; 


"NOT NULL" { return T_NOT_NULL;}
"CREATE" { return T_CREATE;}
"TABLE" { return T_TABLE; } 
"VARCHAR" { yylval.strval = strdup(yytext); return T_VARCHAR; }
"INT" {yylval.strval = strdup(yytext); return T_INT; }
"FLOAT" { yylval.strval = strdup(yytext); return T_FLOAT; }
[\(\)\{\}:;=,] {return yytext[0];}

{IGNORE} {return T_IGNORE;}
{STRING} {yylval.strval = strdup(yytext);return D_STRING;}
{INTEGER} { return D_INTEGER; }
{FLOAT} { return D_FLOAT; }

{ANY_CHAR} {
	printf("Unexpected character in input: '%c' (ASCII=%d)\n", yytext[0], yytext[0]);
}


%% /* Código C */

