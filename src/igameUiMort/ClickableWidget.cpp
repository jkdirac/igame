#include "ClickableWidget.h"

ClickableWidget::ClickableWidget() : MItem()
{
}

ClickableWidget::~ClickableWidget()
{
}

ClickableWidget::ClickableWidget(const QString& fileName) : MItem(fileName)
{
	ClickableWidget();

    return;
}

void ClickableWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	debugOut() << "haha mouseDouble click of clickable item" << endl;
}
