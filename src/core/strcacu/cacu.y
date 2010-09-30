%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cacu_main.h"

int lineno = 0;
double result;

extern int err_no;
extern char err_msg[MSG_BUFF];
%}

%union { 
    char *string;     /* string buffer */
    int    integer;          /* int value */
    double real;
}

%token TOKEN_EQU TOKEN_NEQU TOKEN_LESS_EQ TOKEN_MORE_EQ TOKEN_AND TOKEN_OR
%token TOKEN_PLUS TOKEN_MINUS TOKEN_TIMES TOKEN_DIVIDE
%token <string> TOKEN_IDENTIFIER
%token <real> TOKEN_NUM
%token <real> TOKEN_REAL
%token TOKEN_LEFT_BRACKET TOKEN_RIGHT_BRACKET

%left TOKEN_AND TOKEN_OR
%left TOKEN_EQU TOKEN_NEQU 
%left '<' '>' TOKEN_LESS_EQ TOKEN_MORE_EQ 
%left TOKEN_PLUS TOKEN_MINUS 
%left TOKEN_TIMES TOKEN_DIVIDE

%type <real> cacuexpr expression

%%

expression: assignexp ';' cacuexpr ';'
	{
		$$ = $3;
		result = $$;
		my_printf ("result: %f\n", $$);
	};

assignexp : /**/
	  {
	 }
       | TOKEN_IDENTIFIER '=' TOKEN_NUM
	{
		add_symbol($1, $3);
	}
       | assignexp ',' TOKEN_IDENTIFIER '=' TOKEN_NUM
	{
		add_symbol($3, $5);
	};

cacuexpr :TOKEN_LEFT_BRACKET cacuexpr TOKEN_RIGHT_BRACKET
		{
			$$ = $2;
		}
	 | TOKEN_NUM
		{
			$$ = $1;
		my_printf ("TOKEN NUM: %f\n", $1);
		}
	 | TOKEN_IDENTIFIER
		{
			$$ = get_symbol_value($1);
			if ($$ == STRCACU_SYMBOL_NOT_FOUND)
			{
				err_no = STRCACU_SYMBOL_NOT_FOUND;
				memset(err_msg, 0, MSG_BUFF);
				sprintf(err_msg, "Symbol %s not assignment, set to the default value 0 ", $1);
				$$ = 0;
			}
		}
	 | cacuexpr TOKEN_TIMES cacuexpr
		{
			$$ = $1 * $3;
		}
	 | cacuexpr TOKEN_DIVIDE cacuexpr
		{
			$$ = $1 / $3;
		}
	 | cacuexpr TOKEN_PLUS cacuexpr 
		{
			$$ = $1 + $3;
		}
	 | cacuexpr TOKEN_MINUS cacuexpr 
		{
			$$ = $1 - $3;
		}
	 | cacuexpr TOKEN_NEQU cacuexpr 
		{
			$$ = ($1 != $3);
		}
	 | cacuexpr TOKEN_EQU cacuexpr 
		{
			$$ = ($1 == $3);
		}
	 | cacuexpr '>' cacuexpr 
		{
			$$ = ($1 > $3);
		}
	 | cacuexpr '<' cacuexpr 
		{
			$$ = ($1 < $3);
		}
	 | cacuexpr TOKEN_LESS_EQ cacuexpr 
		{
			$$ = ($1 <= $3);
		}
	 | cacuexpr TOKEN_MORE_EQ cacuexpr 
		{
			$$ = ($1 >= $3);
		}
	 | cacuexpr TOKEN_AND cacuexpr
		{
			$$ = ($1 && $3);
		}
	 | cacuexpr TOKEN_OR cacuexpr
		{
			$$ = ($1 || $3);
		}
;
%%

int yyerror (char *err) {
	err_no = STRCACU_SYNTAX_ERROR;
/*     fprintf(stderr, "line %d, err: %s\n", lineno, err);*/
}

int yywrap () {
	return 1;
}

extern FILE* yyin;
extern int yy_flex_debug;
int cacu_string_exp(char *par, char *expr)
{
	err_no = 0;
	yy_flex_debug = 1;
	lineno = 1;
	FILE *fp;

	if (expr == NULL)
	{
		err_no = STRCACU_NULL_POINTER;
		return -1;
	}

	fp = fopen("tmp.cacu", "w");
	if (fp == NULL)
	{
		err_no = STRCACU_NULL_POINTER;
		return -1;
	}

	if (par == NULL)
	{
		fprintf(fp, ";%s;", expr); 
	}
	else
	{
		fprintf(fp, "%s;%s;", par, expr);
	}

	fflush(fp);
	fclose(fp);

	fp = fopen("tmp.cacu", "r");
	yyin = fp;
 	init_symbol_table();
	yyparse();
/*        yylex();*/
	fclose(fp);
	return result;
}
