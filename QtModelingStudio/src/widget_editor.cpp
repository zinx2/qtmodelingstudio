#include "widget_editor.h"
#include "model_editor.h"
WidgetEditor::WidgetEditor(QWidget *parent) :
	QWidget(parent)
{
	ModelEditor *tableWidget = new ModelEditor(this);
	this->setLayout(new QVBoxLayout(this));
	this->layout()->setMargin(0);
	this->layout()->addWidget(tableWidget);
}

