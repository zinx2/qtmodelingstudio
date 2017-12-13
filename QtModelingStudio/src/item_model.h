#pragma once
#include <QAbstractItemModel>
#include "model.h"
#include <QDebug>
class Object : public Proto
{
	Q_OBJECT
public:
	enum TYPE { PACKAGE, CLASS, PROPERTY };
	Object(int id, int pid, int type, QString name) : 
		Proto(id, pid, type, name)
	{ 
		if(type == CLASS || type == PROPERTY)	m_hidden = true;		
	}
	Object(int id, int pid, int type, QString name, QString dataType, QString dir="", QString listType="") :
		Proto(id, pid, type, name, dataType, dir, listType)
	{
		if (type == CLASS || type == PROPERTY)	m_hidden = true;
	}

	bool hidden() const { return m_hidden; }
	void setHidden(bool m) { m_hidden = m; }

	bool extended() const { return m_extended; }
	void setExtended(bool m) { m_extended = m; }

private:
	bool m_hidden = false;
	bool m_extended = false;
};

class ListModel : public AbstractListModel {
	Q_OBJECT
private:
	ListModel() { };
	static ListModel* m_instance;
public:
	static ListModel* instance() {
		if (m_instance == nullptr) m_instance = new ListModel();
		return m_instance;
	}

	void moveClass(int fromIndex, int toIndex) {  
		Object* fromItem = qobject_cast<Object*>(objs()[fromIndex]);
		Object* toItem = qobject_cast<Object*>(objs()[toIndex]);
		if (fromItem->type() == Object::CLASS && toItem->type() == Object::CLASS 
				&& fromItem->parent() == toItem->parent() ) {
			move(fromIndex, toIndex);
		}
	}

	void extend(int row) {
		qobject_cast<Object*>(objs()[row])->setExtended(true);
		QList<int> children = objs()[row]->children();
		for (int id : children) 
			qobject_cast<Object*>(iterate(id))->setHidden(false);
	}

	void fold(int row, bool isParent = true) {
		if(!isParent)
			qobject_cast<Object*>(objs()[row])->setHidden(true);
		qobject_cast<Object*>(objs()[row])->setExtended(false);
		QList<int> children = objs()[row]->children();		
		for (int id : children) {
			int index = getIndex(id);
			if(index > -1)
				fold(getIndex(id), false);
		}
	}
};