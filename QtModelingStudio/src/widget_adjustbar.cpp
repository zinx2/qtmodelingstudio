#include "widget_adjustbar.h"
#include "design.h"
WidgetAdjustbar::WidgetAdjustbar(Qt::Orientation type, QWidget *parent) :
	WWidget(parent), ori(type)
{
	d = Design::instance();
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	mainWidget = new QWidget;
	mainWidget->setGeometry(this->geometry());
	//mainWidget->setStyleSheet("background-color:" + d->c().adjustbar);

	mainVBox = new QVBoxLayout;
	mainVBox->addWidget(mainWidget);
	mainVBox->setMargin(0);
	this->setLayout(mainVBox);
	this->setAttribute(Qt::WA_Hover, true);

}
void	WidgetAdjustbar::mouseMoveEvent(QMouseEvent *event)
{
	emit adjust(event);
}
void WidgetAdjustbar::enterEvent(QEvent * event)
{
	Q_UNUSED(event);
	mainWidget->setStyleSheet("background-color:gray");

	Qt::CursorShape type = (ori == Qt::Vertical ? Qt::SizeHorCursor : Qt::SizeVerCursor);
	this->setCursor(QCursor(type));
}

void WidgetAdjustbar::leaveEvent(QEvent * event)
{
	Q_UNUSED(event);
	mainWidget->setStyleSheet("background-color:white"/* + d->c().adjustbar*/);
	this->setCursor(QCursor(Qt::ArrowCursor));
}

