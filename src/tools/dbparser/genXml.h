#ifndef _GEN_XML_H_
#define _GEN_XML_H_

#include <stdio.h>
//#define DEBUG_OUTPUT

#ifdef DEBUG_OUTPUT
#define debug_output(...) 
//{printf("-----COMMON DEBUG: "); printf(__VA_ARGS__);}
#else
#define debug_output(...) 
#endif

typedef unsigned char bool;
#define true 1
#define false 0

FILE* open_file(const char *filename);
void close_file(FILE *fp);
void put_string(FILE* fp, int tabs, const char *instring);

typedef struct _att_t
{
	struct _att_t *next;
	char *name;
	char *value;
	int size;
}att_t;

att_t* start_par_att();
void add_att(att_t* head, const char* name, const char* vaule);
char* make_node_name_str(const char *name, att_t* head);
char* make_node_str(const char *node_name, att_t* head, const char* value);
void finish_make_node_name_str(char *str, att_t **head);
void end_par_att(att_t *head);

#define MAX_DEPTH 64
typedef struct _my_stack
{
	int values[MAX_DEPTH];
	int top;
} stack;

void init_stack(stack *s);
void push_stack(stack *s, int value);
void pop_stack(stack *s);
int top_stack(stack *s);
bool isempty(stack *s);

#endif
