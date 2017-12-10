#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication4.h"

class QtGuiApplication4 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication4(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtGuiApplication4Class ui;
};
