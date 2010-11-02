#include "RotateWidget.h"
#include <QPainter>
#include <QTimer>
#include <QTime>

RotateWidget::RotateWidget( QWidget *parent ) :QPushButton( parent )
{
	QTimer *timer = new QTimer(this);
	connect( timer, SIGNAL(timeout()), this, SLOT( update() ) );
	timer->start(50);

//    setWindowTitle( tr("Rotating Quad") );
	resize( 360, 360 );
}

void RotateWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint( QPainter::Antialiasing );
	QColor quadColor( 0, 0, 255 );

	painter.setBrush( quadColor );

	QTime time = QTime::currentTime();

	painter.translate( width() / 2, height() / 2 );
	painter.rotate( ( time.second() + ( time.msec() / 1000.0 ) ) * 6.0 );

	painter.drawRect( QRect( -50, -50, 100, 100 ) );

}
