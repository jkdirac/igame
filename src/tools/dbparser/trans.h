#ifndef _TRAN_H_
#define _TRAN_H_

#ifdef __cplusplus
extern "C" {
#endif

//char* translateInfix (const char* formula);
char *translateInfixCh (const char* formula);
char * translateMathML (const char* xml);

#ifdef __cplusplus
}
#endif

#endif
