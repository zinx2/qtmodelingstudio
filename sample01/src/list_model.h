#pragma once
#include <QObject>
#include <QList>
#include <QAbstractItemModel>
class Proto : public QObject {
	Q_OBJECT
		Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
		Q_PROPERTY(int parent READ parent WRITE setParent NOTIFY parentChanged)
		Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QList<int> children READ children WRITE setChildren NOTIFY childrenChanged)
public:

	Proto(int id, int pid, int type, QString name) : m_id(id), m_name(name), m_type(type), m_parent(pid) { }

	int id() const { return m_id; }
	int parent() const { return m_parent; }
	int type() const { return m_type; }
	int offset() const { return m_offset - 1; }
	QString name() const { return m_name; }
	QList<int> children() const { return m_children; }
	int lastChild() {
		int size = m_children.size();
		if (size == 0) return -1;
		return  m_children[size - 1];
	}

	public slots :
	void setId(const int m) { m_id = m; emit idChanged(); }
	void setParent(const int m) { m_parent = m; emit parentChanged(); }
	void setType(const int m) { m_type = m; emit typeChanged(); }
	void setName(const QString m) { m_name = m; emit nameChanged(); }
	void setChildren(const QList<int> m) { m_children = m; emit childrenChanged(); }

	bool appendChild(const int targetId) {
		/* FIND IF THE EQUAL ID EXISTS IN LIST. */
		for (int idx : m_children) {
			if (targetId == idx) return false;
		}
		m_children.append(targetId);
		emit childrenChanged();
		return true;
	}
	bool removeChild(const int targetId) {
		for (int i = 0; i < m_children.size(); i++) {
			if (targetId == m_children[i]) {
				m_children.removeAt(i);
				emit childrenChanged();
				return true;
			}
		}
		return false;
	}
	bool moveChild(const int fromId, const int toId) {
		int fromIndex = findChildIndex(fromId);
		int toIndex = findChildIndex(toId);
		if (fromIndex == -1 || toIndex == -1)
			return false;

		m_children.move(fromIndex, toIndex);
		emit childrenChanged();
		return true;
	}
	void increaseOffset() { m_offset++; }
	void decreaseoffset() { m_offset--; }

signals:
	void idChanged();
	void parentChanged();
	void nameChanged();
	void typeChanged();
	void childrenChanged();

protected:
	int findChildIndex(int targetId) {
		for (int i = 0; i < m_children.size(); i++) {
			if (targetId == m_children[i]) {
				return i;
			}
		}
		return -1;
	}

private:
	int m_id;
	int m_parent = -1;
	int m_type;
	int m_offset = 0;
	QString m_name;
	QList<int> m_children;
};
class AbstractListModel : public QObject {
	Q_OBJECT
		Q_PROPERTY(QList<Proto*> objs READ objs WRITE setObjs NOTIFY objsChanged)

public:
	~AbstractListModel() {
		for (Proto* o : m_objs)
			delete o;
	}
	QList<Proto*> objs() const { return m_objs; }
	int size() { return m_objs.size(); }
	Proto* obj(int index) { return m_objs[index]; }
	public slots :
	void setObjs(QList<Proto*> m) { m_objs = m; }
	void append(Proto* p) {
		int toIndex = -1;
		if (p->parent() > -1) {
			/* IF EXSISTS PARENT, FIND PARENT ID. */
			for (int i = 0; i < m_objs.size(); i++) {
				if (m_objs[i]->id() == p->parent())
					toIndex = i;
			}
		}

		/* WHEN HAVE NO PARENT, FIND PARENT ID. */
		if (toIndex == -1)
			m_objs.append(p);
		else {
			/* WHEN HAVE PARENT, ADD OFFSET AT INDEX. */
			Proto* parent = m_objs[toIndex];
			if (parent->appendChild(p->id()))
				m_objs.insert(toIndex + 1 + parent->offset(), p);
		}

		/* THE OFFSET HAVE TO INCREASE ALWAYS. */
		increaseOffset(p->id());
		emit objsChanged();
	}

	bool remove(int targetId) {
		Proto* target = iterate(targetId);
		if (target == nullptr) return false;

		Proto* parent = iterate(target->parent());
		if (parent != nullptr)
			parent->removeChild(targetId);

		/* RELEASE CHILDREN */
		removeChildAll(target);

		/* RELEASE PACKAGE */
		return removeObj(target);
	}
	void move(int fromIndex, int toIndex) {
		Proto* target = m_objs[fromIndex];
		if (target != nullptr) {

			Proto* parent = iterate(target->parent());
			int parentRow = -1;
			for (int i = 0; i < m_objs.size(); i++) {
				if (parent->id() == m_objs[i]->id()) {
					parentRow = i;
					break;
				}
			}

			int offset = parent->offset();
			QList<Proto*> listA;
			QList<Proto*> listB;
			QList<Proto*> listC;
			QList<Proto*> listD;
			QList<Proto*> listE;

			if (fromIndex != toIndex) {

				int topIdx = toIndex;
				int bottomIdx = fromIndex;
				if (fromIndex < toIndex) {
					topIdx = fromIndex;
					bottomIdx = toIndex;
				}

				listA = m_objs.mid(0, topIdx);
				listB = m_objs.mid(topIdx, m_objs[topIdx]->offset() + 1);

				int startIndex = topIdx + m_objs[topIdx]->offset() + 1;
				listC = m_objs.mid(startIndex, bottomIdx - startIndex);
				listD = m_objs.mid(bottomIdx, m_objs[bottomIdx]->offset() + 1);

				startIndex = bottomIdx + m_objs[bottomIdx]->offset() + 1;
				listE = m_objs.mid(startIndex, m_objs.size() - startIndex);

				m_objs.clear();
				m_objs.append(listA);
				if (fromIndex < toIndex) {
					m_objs.append(listC);
					m_objs.append(listD);
					m_objs.append(listB);

				}
				else {
					m_objs.append(listD);
					m_objs.append(listB);
					m_objs.append(listC);
				}
				m_objs.append(listE);
			}
			emit objsChanged();
		}
	}

signals:
	void objsChanged();

protected:
	Proto* iterate(int id) {
		Proto* obj = nullptr;
		for (int i = 0; i < m_objs.size(); i++) {
			if (id == m_objs[i]->id()) {
				obj = m_objs[i];
				break;
			}
		}
		return obj;
	}

	/* REMOVE ALL CHILD RECURSIVELY AND DECREASE OFFSET */
	void removeChildAll(Proto* target) {
		if (target->children().size() == 0) return;
		for (int i = 0; i < target->children().size(); i++) {
			Proto* child = iterate(target->children()[i]);
			decreaseOffset(target->id());
			removeChildAll(child);
			removeObj(child);
		}
	}

	/* REMOVE CHILD FROM LIST AND DECREASE OFFSET */
	bool removeObj(Proto* target) {
		for (int i = 0; i < m_objs.size(); i++) {
			if (target->id() == m_objs[i]->id()) {
				decreaseOffset(target->id());
				m_objs.removeAt(i);
				delete target;
				target = nullptr;
				emit objsChanged();
				return true;
			}
		}
		return false;
	}

	/* INCREASE RECURSIVELY OFFSET */
	void increaseOffset(int id) {
		Proto* p = iterate(id);
		if (p == nullptr) return;
		p->increaseOffset();
		increaseOffset(p->parent());
	}

	/* DECREASE RECURSIVELY OFFSET */
	void decreaseOffset(int id) {
		Proto* p = iterate(id);
		if (p == nullptr) return;
		p->decreaseoffset();
		decreaseOffset(p->parent());
	}

	/* RETURN INDEX BY ID */
	int getIndex(int id) {
		for (int i = 0; i < size(); i++) {
			if (id == objs()[i]->id()) return i;
		}
		return -1;
	}
private:
	QList<Proto*> m_objs;
};
class Object : public Proto
{
	Q_OBJECT
public:
	enum TYPE { PACKAGE, CLASS, PROPERTY };
	Object(int id, int pid, int type, QString name) :
		Proto(id, pid, type, name)
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
public:
	void moveClass(int fromIndex, int toIndex) {
		Object* fromItem = qobject_cast<Object*>(objs()[fromIndex]);
		Object* toItem = qobject_cast<Object*>(objs()[toIndex]);
		if (fromItem->type() == Object::CLASS && toItem->type() == Object::CLASS
			&& fromItem->parent() == toItem->parent()) {
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
		if (!isParent)
			qobject_cast<Object*>(objs()[row])->setHidden(true);
		qobject_cast<Object*>(objs()[row])->setExtended(false);
		QList<int> children = objs()[row]->children();
		for (int id : children) {
			int index = getIndex(id);
			if (index > -1)
				fold(getIndex(id), false);
		}
	}
};
Q_DECLARE_METATYPE(Proto*)
