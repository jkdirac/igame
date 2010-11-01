#ifndef _ROTATE_WIDGET_H_
#define _ROTATE_WIDGET_H_

#include <QWidget>
#include <QPushButton>

class RotateWidget : public QPushButton
{
	public:
		RotateWidget( QWidget *parent = 0 );

	protected:
		void paintEvent(QPaintEvent *event);
};

#endif
