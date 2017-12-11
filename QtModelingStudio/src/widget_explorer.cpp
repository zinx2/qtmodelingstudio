#include "widget_explorer.h"
#include "list_widget.h"
WidgetExplorer::WidgetExplorer(QWidget *parent) :
	WWidget(parent)
{
	qDebug() << parent->geometry().width();
	qDebug() << parent->geometry().height();
	this->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
	this->setLayout(new QVBoxLayout(this));
	this->layout()->setMargin(0);

	/*QWidget* w = new QWidget(this);	
	w->setStyleSheet("background-color:orange");*/
	ListWidget* w = new ListWidget(this);
	this->layout()->addWidget(w);
}	