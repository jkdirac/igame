#ifndef _GLOBAL_SETTING_H_
#define _GLOBAL_SETTING_H_

#include <string>
using namespace std;

#if __cplusplus
extern "C" {
#endif

void set_igame_home(const char*);
const char* get_igame_home_dir();

#if __cplusplus
}
#endif

#endif
