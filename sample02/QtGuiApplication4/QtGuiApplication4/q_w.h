#pragma once
#include <QWidget>
#include <QQuickWidget>
#include <QVBoxLayout>
#include "application_data.h"
class QWd : public QWidget
{
	Q_OBJECT
public:
	static QWd* instance() {
		if (m_instance == nullptr)
			m_instance = new QWd();

		return m_instance;
	}
	QWd(QQuickWidget* q, QWidget *parent=NULL) : QWidget(parent) {
		this->setLayout(new QVBoxLayout);
		this->layout()->addWidget(q);
		//q->show();		
	}
	void setQuick(QQuickWidget* q) { 
		this->setLayout(new QVBoxLayout);
		this->layout()->addWidget(q);
	}

private:
	static QWd* m_instance;
	QWd() { }
};

