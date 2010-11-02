#ifndef _ORDERED_SCENE_H_
#define _ORDERED_SCENE_H_

#include "MScene.h"
#include <QList>

//可以调整大小
//有三个固定的biobrick
//每个biobrick的位置可以调节
class OrderedScene : public MScene
{
	public: 
		OrderedScene(const QString &id, SPECIESTYPE type, MItem *root=NULL);
		bool itemDropped(MItem *item);

		void rearrangeItem();
		void adjustItemPos();

		QString generateSpeXmlString();
		void insertItem(MItem *item);

	private:
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		int m_margin;
		int m_bioWidth;
		MItem* m_bone;
		MItem* m_head;
		MItem* m_tail;

		QList<MItem*> m_validItem;
		static bool posxGreatethan(MItem* it1, MItem* it2);
};

#endif
