LIBS = -lsbml
LDFLG = -L/home/jkdirac/Develop/igame/ExternalLib/linux
CC = cc
CXX = g++
LEX = flex
YACC = yacc
CCFLAGS = -g

parser:	parseryac.o parserlex.o genXml.o trans.o
	${CC} ${CCFLAGS} -o $@ $^ ${LIBS}

trans.o : trans.cpp 
	${CXX} -c ${CCFLAGS} $^ -o $@

genXml.o: genXml.c
	${CC} -c ${CCFLAGS} $^ -o $@

parserlex.o: parserlex.c 
	${CC} -c ${CCFLAGS} $^ -o $@

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
