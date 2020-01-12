default:build check
build:
	flex src/lexical.l
	cc lex.yy.c -lfl
	./a.out < test/testcase.pl0
	bison -d src/parsing.y
	flex src/parsing.l
	gcc parsing.tab.c lex.yy.c -lfl
	./a.out < test/testcase.pl0
check:
.PHONY:default build check
