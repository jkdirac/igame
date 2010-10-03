%{
#include "parseryac.h"
#include "genXml.h"
#include <string.h>
#include <stdio.h>

extern int lineno;

int dbgToken(int tok, char *s)
{

#ifdef DEBUG_OUTPUT
	fprintf(stderr,"-- TOKEN-DEBUG token %s line:%d\n", s, lineno);
#endif

	return tok;
}

#define my_return(x) {return dbgToken(x, #x);}

#ifdef DEBUG_OUTPUT
	#define my_printf(fm, arg...) printf(fm, ##arg);
#else
	#define my_printf(arg...) 
#endif

%}

ws        [ \t]+
comment   #.*
valuestring \[[^\[\]\n]*[\]\n]
qstring   \"[^\"\n]*[\"\n]
sstring	  ([^ \t\n\"]+(\\\ )+[a-zA-Z0-9]+)+ 
nl        [\n] 
nousedchar [,\r]+
xmlcommentstring <\!\-\-.*\-\->
identifer [A-Za-z][^\[\]\"\ \n\t\r\=:]*

%%
{nousedchar} ;
{ws}      ;
{nl}	  lineno++;
{comment} ;

NODENAME { yylval.string = strdup(yytext); my_return(TOK_NODENAME); }
file { yylval.string = strdup(yytext); my_return(TOK_FILENAME); }

{identifer} {
		yylval.string = strdup(yytext); /* skip open quote */
		my_printf("%s\n", yytext);
		my_return(TOKEN_IDENTIFIER);
	}

{xmlcommentstring} {
	yylval.string = strdup(yytext); /* skip open quote */
	my_printf("%s\n", yytext);
	my_return(TOKEN_COMMENT);
		   }

{valuestring} { 
	    yylval.string = strdup(yytext+1); /* skip open quote */

            if(yylval.string[yyleng-2] != ']')
						{
	        my_printf("Unterminated value string\n",(char *)0);
						}
	    else
			{
	        yylval.string[yyleng-2] = '\0'; /* remove close quote */
			}

	   // printf ("vauletring: %s\n", yylval.string);
            my_return(VALUESTRING);
	  }

{qstring} { 
	    yylval.string = strdup(yytext); /* skip open quote */
	    my_printf ("qstring: %s", yytext);
            my_return(QSTRING);
          }

{sstring} { 
	yylval.string = strdup(yytext); /* skip open quote */
	if((yylval.string[yyleng-1] != ',')
			&& (yylval.string[yyleng-1] != ';'))
	{
	//	printf("Unterminated character string\n",(char *)0);
	}
	else
	{
		yylval.string[yyleng-1] = '\0'; /* remove close quote */
	}

		my_printf ("sstring: %s\n", yylval.string);
            my_return( SSTRING );
          }

\{ 	 my_return( TOK_GROUPSTART ); 
\}	 my_return( TOK_GROUPEND ); 
.          { 
		my_printf("chartoken %c \t %d\n", yytext[0], yytext[0]); my_return( yytext[0] ); 
}

%%

