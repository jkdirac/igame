%{
#include "cacuyac.hpp"
#include <string.h>
#include <stdio.h>
#include "cacu_main.h"

extern int lineno;

int dbgToken(int tok, char *s)
{
#ifdef DEBUG_OUTPUT
	printf("-- TOKEN-DEBUG token %s line:%d\n", s, lineno);
#endif
	return tok;
}

#define my_return(x) return dbgToken(x, #x);
%}

ws        [ \t]+
nl        [\n] 
nousedchar [\r]+
identifer [A-Za-z][\_0-9A-Za-z]*
numstring [\-]?[0-9]+
realstring [\-]?[0-9]+[\.][0-9]+
equal ==
nequal !=
less_and_eq <=
more_and_eq >=
and	(&&)
or	(\|\|)
plus    (\+)
minus	(\-)
times	(\*)
divide	(\/)

%%
{nousedchar} ;
{ws}      ;
{nl}	  lineno++;

{numstring} {
		yylval.real = atoi(yytext); 
		my_printf("integer value %f\n", yylval.real);
		my_return(TOKEN_NUM);
	}

{identifer} {
		yylval.string = strdup(yytext);
		my_printf("%s\n", yylval.string);
		my_return(TOKEN_IDENTIFIER);
	}

{realstring} {
		yylval.real = atof(yytext);
		my_printf("real num value %f\n", yylval.real);
		my_return(TOKEN_NUM);
	}

{equal} { my_return(TOKEN_EQU); }
{nequal} { my_return(TOKEN_NEQU); }
{less_and_eq} { my_return(TOKEN_LESS_EQ); }
{more_and_eq} { my_return(TOKEN_MORE_EQ); }
{and} { my_return(TOKEN_AND); }
{or} { my_return(TOKEN_OR); }
{plus} { my_return(TOKEN_PLUS); }
{minus} { my_return(TOKEN_MINUS); }
{times} { my_return(TOKEN_TIMES); }
{divide} { my_return(TOKEN_DIVIDE); }

\( { my_return(TOKEN_LEFT_BRACKET); }
\) { my_return(TOKEN_RIGHT_BRACKET); }

.          { my_printf("chartoken %c \t %d\n", yytext[0], yytext[0]); my_return( yytext[0] ); }

%%
