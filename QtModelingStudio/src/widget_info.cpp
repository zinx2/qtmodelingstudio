#include "widget_info.h"

WidgetInfo::WidgetInfo(QWidget *parent) :
	WWidget(parent)
{
	this->setLayout(new QVBoxLayout(this));

	QWidget* w = new QWidget(this);
	w->setFixedSize(100, 100);
	w->setStyleSheet("background-color:#00ff00");

	this->layout()->addWidget(w);
}