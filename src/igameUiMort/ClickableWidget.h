#ifndef _CLICKABLE_WIDGET_H_
#define _CLICKABLE_WIDGET_H_

#include "MItem.h"
#include "SceneManager.h"
#include <QFile>

class ClickableWidget: public MItem
{
	private:
		SceneManager* m_senemgr;
	public:
		ClickableWidget(SPECIESTYPE type=SPEC_COMPARTMENT);
		ClickableWidget(const QString& xmlfile, SPECIESTYPE type=SPEC_COMPARTMENT);
		virtual ~ClickableWidget();
		void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
};

#endif
