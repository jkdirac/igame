LIBS = 
TARGETLIB = libstr_cacu.a
CC = gcc
CPULSPLUS = g++
LEX = flex
YACC = yacc
CCFLAGS = -g
AR = ar

all: ${TARGETLIB} cacu

${TARGETLIB}: cacuyac.o caculex.o str_cacu.o strcacuexception.o 
	${AR} rv $@ $^
# ${TARGETLIB}
cacu:	 cacu_main.o ${TARGETLIB} 
	${CPULSPLUS} ${CCFLAGS} -o $@ $^

strcacuexception.o: StrCacuException.cpp
	${CPULSPLUS} -c ${CCFLAGS} $^ -o $@

str_cacu.o: str_cacu.cpp
	${CPULSPLUS} -c ${CCFLAGS} $^ -o $@

cacu_main.o: cacu_main.cpp
	${CPULSPLUS} -c ${CCFLAGS} $^ -o $@

caculex.o: caculex.c cacuyac.h

caculex.c:	cacu.l
	${LEX} cacu.l
	mv lex.yy.c caculex.c

cacuyac.c cacuyac.h:	cacu.y
	${YACC} -d cacu.y
	mv y.tab.c cacuyac.c
	mv y.tab.h cacuyac.h

clean:
	rm *.o
	rm cacuyac.c cacuyac.h caculex.c
	rm *.a
