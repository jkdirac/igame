#include "ClickableWidget.h"

ClickableWidget::ClickableWidget() : MItem()
{
	renew();
}

ClickableWidget::~ClickableWidget()
{
}

ClickableWidget::ClickableWidget(const QString& fileName) : MItem(fileName)
{
	ClickableWidget();

    return;
}

void ClickableWidget::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	debugOut() << "haha mouseDouble click of clickable item" << endl;
	QGraphicsItem::mouseDoubleClickEvent(event);
}
