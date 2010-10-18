#include "globalSetting.h"

string system_igame_home = "";

/** 
 * @breif  set the global home path
 * 
 * @Param input
 */
void set_igame_home(const char* input)
{
	if (input == NULL)
		return;

	system_igame_home = input;
}

const char* get_igame_home_dir()
{
	return system_igame_home.c_str();
}
