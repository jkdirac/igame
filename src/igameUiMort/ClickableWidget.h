#ifndef _CLICKABLE_WIDGET_H_
#define _CLICKABLE_WIDGET_H_

#include "MItem.h"
#include "SceneManager.h"
#include <QFile>

class ClickableWidget: public MItem
{
	private:
		SceneManager* m_senemgr;
		MScene* m_ownScene;

	public:
		const MScene* getOwnerScene() const { return m_ownScene; };
		ClickableWidget(SPECIESTYPE type=SPEC_COMPARTMENT);
		ClickableWidget(const QString& xmlfile, SPECIESTYPE type=SPEC_COMPARTMENT);
		virtual ~ClickableWidget();
		void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
		void deletOwnerScene();
		void invalidOwnerScene(bool invalid);
};

#endif
