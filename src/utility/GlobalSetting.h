#ifndef _GLOBAL_SETTING_H_
#define _GLOBAL_SETTING_H_

#if __cplusplus
extern "C" {
#endif

void set_igame_home(const char*);
const char* get_igame_home_dir();

void set_copasi_path(const char*);
void get_copasi_path();
#if __cplusplus
}
#endif

#endif
