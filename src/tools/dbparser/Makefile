LIBS = 
CC = cc
LEX = flex
YACC = yacc
CCFLAGS = -g

parser:	parseryac.o parserlex.o genXml.o
	${CC} ${CCFLAGS} -o $@ $^ ${LIBS}

genXml.o: genXml.c genXml.h
	${CC} -c ${CCFLAGS} $^ ${LIBS}

parserlex.o: parserlex.c parseryac.h

parserlex.c:	parser.l
	${LEX} parser.l
	mv lex.yy.c parserlex.c

parseryac.c parseryac.h:	parser.y
	${YACC} -d parser.y
	mv y.tab.c parseryac.c
	mv y.tab.h parseryac.h

clean:
	rm *.o
	rm parseryac.c parseryac.h parserlex.c
