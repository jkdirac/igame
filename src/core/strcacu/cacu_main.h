#ifndef _CACU_MAIN_H_
#define _CACU_MAIN_H_

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


void add_symbol(char *name, double value);
double get_symbol_value(char *name);
const char* get_err_msg();

extern int err_no;

#ifdef __cplusplus
}
#endif // end cplusplus

#endif //end _CACU_MAIN_H_
