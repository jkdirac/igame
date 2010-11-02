#include "GlobalSetting.h"
#include <QDir>
#include <string>

using namespace std;

string system_igame_home = QDir::currentPath().toLatin1().constData();
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
