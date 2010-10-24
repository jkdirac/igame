#ifndef _CLICKABLE_WIDGET_H_
#define _CLICKABLE_WIDGET_H_

#include "MItem.h"
#include "SceneManager.h"
#include "DebugOut.h"
#include <QFile>

class ClickableWidget: public MItem
{
	private:
		SceneManager* m_senemgr;
	public:
		ClickableWidget();
		ClickableWidget(const QString& xmlfile);
		virtual ~ClickableWidget();
		void mouseDoubleClickEvent(QMouseEvent* event);
};

#endif
