%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "genXml.h"
#include "trans.h"

int lineno = 0;
FILE *fp_outfile;
att_t* p_attr;
char* p_att_str; 
int cur_depth = 0;
int next_depth = 0;
stack depth_stack;
%}

%union { char    *string;     /* string buffer */
    int    integer;          /* int value */
}

%token <string> VALUESTRING QSTRING SSTRING TOKEN_COMMENT TOKEN_IDENTIFIER TOK_GROUPSTART TOK_GROUPEND
%token <string> TOK_FILENAME TOK_MATH
%type <string> module_name
%type <integer> module_body_statement module_statement

%%
files:  /*empty*/
     | files file_des;

file_des: filename_state module_statement
	;

filename_state: TOK_FILENAME '=' VALUESTRING
	      { 
		fp_outfile = open_file($3); 
	      } ;
	
module_statement: module_name TOK_GROUPSTART module_body_statement TOK_GROUPEND 
			{
				pop_stack(&depth_stack);
				if (isempty(&depth_stack) == true)
					cur_depth = 0;
				else 
					cur_depth = top_stack(&depth_stack);

				put_string(fp_outfile, cur_depth, "</");
				put_string(fp_outfile, 0, $1);
				put_string(fp_outfile, 0, ">\n");
				$$ = 1;
			}
		| TOKEN_IDENTIFIER ':' VALUESTRING module_attribute separte
			{
					cur_depth = top_stack(&depth_stack);
					//头部
					if (p_attr == NULL)
						p_attr = start_par_att(); 
					p_att_str = make_node_str($1, p_attr, $3);;
					if (p_att_str != NULL)
					{
						put_string(fp_outfile, cur_depth, p_att_str);
						put_string(fp_outfile, 0, "\n");
						finish_make_node_name_str(p_att_str, &p_attr);
					}
			}
		| TOK_MATH ':' VALUESTRING separte
			{
					char *math = translateInfixCh($3);
					cur_depth = top_stack(&depth_stack);
					if (math != NULL)
						put_string(fp_outfile, cur_depth, math);
			}
		;

module_name: TOKEN_IDENTIFIER module_attribute 
	  	{
			//尾部
			if (isempty(&depth_stack) == true)
			{
				cur_depth = 0;
				push_stack(&depth_stack, 0);
			}

			cur_depth = top_stack(&depth_stack);
			next_depth = top_stack(&depth_stack) + 1;
			push_stack(&depth_stack, next_depth);

			/* generate node head*/
			if (p_attr == NULL)
				p_attr = start_par_att(); 

			p_att_str = make_node_name_str($1, p_attr);
			if (p_att_str != NULL)
			{
				put_string(fp_outfile, cur_depth, p_att_str);
				put_string(fp_outfile, 0, "\n");
				finish_make_node_name_str(p_att_str, &p_attr);
			}
			$$ = $1;
		} 
		;

module_attribute:  /*empty*/
		| module_attribute TOKEN_IDENTIFIER '=' VALUESTRING 
			{ 
				if(p_attr == NULL)
					p_attr = start_par_att();
			  	add_att(p_attr, $2, $4);
			}
		;

module_body_statement:  {}/*empty body*/
		     | module_body_statement TOKEN_COMMENT 
			{ 
				if (isempty(&depth_stack) == true)
				{
					cur_depth = 0;
					push_stack(&depth_stack, 0);
				}
				else
				{
					cur_depth = top_stack(&depth_stack);
				}
					
				put_string(fp_outfile, cur_depth, $2); 
				put_string(fp_outfile, 0, "\n");
				$$ = 0;
			}
		     | module_body_statement module_statement 
			{
				debug_output("sub module\n");
			}
		     ;

separte: ';'
       ;
%%

int yyerror (char *err) {
     fprintf(stderr, "-- line %d, err: %s\n", lineno, err);
}

int yywrap () {
	return 1;
}

extern int yy_flex_debug;
int main()
{
	yy_flex_debug = 1;
	lineno = 1;
	init_stack(&depth_stack);
	push_stack(&depth_stack, 0);
	yyparse ();
/*yylex();*/
return 0;
}
