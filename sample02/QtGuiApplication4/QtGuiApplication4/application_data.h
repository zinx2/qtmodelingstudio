#pragma once
#include <QQmlContext>
#include <QDateTime>
class ApplicationData : public QObject
{
	Q_OBJECT
public:
	ApplicationData(/*int displayWidth,*/QObject *parent = NULL) : QObject(parent) {

	}
	Q_INVOKABLE QDateTime getCurrentDateTime() const {
		return QDateTime::currentDateTime();
	}
};