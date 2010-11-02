#ifndef _COMMON_SCENE_H_
#define _COMMON_SCENE_H_

#include "MScene.h"

class CommonScene : public MScene
{
	CommonScene(const QString &id, SPECIESTYPE type, MItem *root=NULL);
};

#endif
