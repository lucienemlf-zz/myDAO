%{
	#include <stdio.h>
%}

/* Definições */




%% /* Regras */



%% /* Código C */


main(){
	yylex();
}


yywrap () {
	return 0;
}