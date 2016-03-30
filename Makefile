main: scanner.l
	flex scanner.l
	gcc lex.yy.c -o lexico

clean:
	rm lex.* 