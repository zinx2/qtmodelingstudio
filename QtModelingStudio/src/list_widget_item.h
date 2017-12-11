#pragma once
#include <QListWidgetItem>

class ListWidgetItem : public QListWidgetItem {

public:	
	ListWidgetItem(QString name) : QListWidgetItem(name) {

	}
	int index() const { return m_index; }
	void setIndex(int index) { m_index = index; }

private:
	int m_index;
};