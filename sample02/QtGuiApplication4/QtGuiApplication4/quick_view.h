#pragma once
#include <QQuickWidget>
#include "application_data.h"
class QView : public QQuickWidget
{
	Q_OBJECT
public:
	explicit QView(QWidget *parent = Q_NULLPTR) : QQuickWidget(parent) { 
	
		ApplicationData data;
		this->setSource(QUrl::fromLocalFile("C:/Users/fifa3/source/repos/QtGuiApplication4/QtGuiApplication4/Test1.qml"));
		this->rootContext()->setContextProperty("applicationData", &data);
	};

};