#ifndef _STR_CACU_H__
#define _STR_CACU_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif //end cplusplus
//err msg buff len
#define MSG_BUFF 64

//debug macro may edit here
//#define DEBUG_OUTPUT
#define TEST_OUTPUT

#ifdef DEBUG_OUTPUT
#define my_printf(...) printf(__VA_ARGS__);
#else
#define my_printf(...)
#endif

//error code
#define STRCACU_SUCCESS 0
#define STRCACU_SYMBOL_NOT_FOUND -1
#define STRCACU_NULL_POINTER -2
#define STRCACU_SYNTAX_ERROR -3

extern int err_no;

void add_symbol(char *name, double value);
double get_symbol_value(char *name);
const char* get_err_msg();
extern int cacu_string_exp(const char *par, const char *expr);
void init_symbol_table();
#ifdef __cplusplus
}
#endif // end cplusplus

int cacu_str_exp(char const*par, char const*expr);

#endif //end _CACU_MAIN_H_
