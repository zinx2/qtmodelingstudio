#pragma once
#include "qheader.h"

class Proto : public QObject {
	Q_OBJECT
		Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
		Q_PROPERTY(int parent READ parent WRITE setParent NOTIFY parentChanged)
		Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
		Q_PROPERTY(QList<int> children READ children WRITE setChildren NOTIFY childrenChanged)
public:
	Proto() { }
	Proto(int id, int pid, int type, QString name, QString dir="") : m_id(id), m_name(name), m_type(type), m_parent(pid), m_dir(dir) { }

	int id() const { return m_id; }
	int parent() const { return m_parent; }
	int type() const { return m_type; }
	int offset() const { return m_offset - 1; }
	QString name() const { return m_name; }
	QString dir() const { return m_dir; }
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
	void setDir(const QString m) { m_name = m; emit dirChanged(); }
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
	void dirChanged();
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
	QString m_dir;
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

	int getRowId(int id ) {
		for (int i = 0; i < m_objs.size(); i++) {
			if (id == m_objs[i]->id()) {				
				return i;
			}
		}
		return -1;
	}

signals:
	void objsChanged();

protected:
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

Q_DECLARE_METATYPE(Proto*)


class Explorer : public QObject {
	Q_OBJECT
		Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
		Q_PROPERTY(int parent READ parent WRITE setParent NOTIFY parentChanged)
		Q_PROPERTY(bool extended READ extended WRITE extend NOTIFY extendedChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
		Q_PROPERTY(QList<QObject*> children READ children WRITE setChildren NOTIFY childrenChanged)
public:

	Explorer(int id, QString name, QString path) : m_id(id), m_name(name), m_path(path) { }
	Explorer(int id, QString name, QString path, bool extended) : m_id(id), m_name(name), m_path(path), m_extended(extended) { }
	Explorer(
		int id,
		int parent,
		QString name,
		QString path,
		QList<QObject*> children) : m_id(id), m_parent(parent), m_name(name), m_path(path), m_children(children) { 	}
	Explorer(
		int id,
		int parent,
		QString name,
		QString path,
		bool extended,
		QList<QObject*> children) : m_id(id), m_parent(parent), m_name(name), m_path(path), m_extended(extended), m_children(children) { 	}

	int id() const { return m_id; }
	int parent() const { return m_parent; }
	bool extended() const { return m_extended; }
	QString name() const { return m_name; }
	QString path() const { return m_path; }
	QList<QObject*> children() const { return m_children; }

	public slots:
	void setId(const int id) { m_id = id; }
	void setParent(const int parent) { m_parent = parent; }
	void setName(const QString &m) { m_name = m; emit nameChanged(); }
	void setPath(const QString &m) { m_path = m; emit pathChanged(); }
	void setChildren(const QList<QObject*> &m) { m_children = m; emit childrenChanged(); }
	void extend(bool m) { m_extended = m; emit extendedChanged(); };

signals:
	void idChanged();
	void parentChanged();
	void nameChanged();
	void pathChanged();
	void childrenChanged();
	void extendedChanged();


private:
	int m_id = -1;
	int m_parent = -1;
	bool m_extended = false;
	QString m_name;
	QString m_path;
	QList<QObject*> m_children;
};


class ViewModel : public QObject {
	Q_OBJECT
		Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
		Q_PROPERTY(int selectedItem READ selectedItem WRITE selectItem NOTIFY itemSelected)
		Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
		Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
		Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)
		Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)
		Q_PROPERTY(bool full READ full WRITE setFull NOTIFY fullChanged)
		Q_PROPERTY(bool pressedCtrl READ pressedCtrl WRITE pressCtrl NOTIFY pressedCtrlChanged)
		Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
		Q_PROPERTY(int scaledItemWidth READ scaledItemWidth WRITE setScaledItemWidth NOTIFY scaledItemWidthChanged)
		Q_PROPERTY(int scaledItemHeight READ scaledItemHeight WRITE setScaledItemHeight NOTIFY scaledItemHeightChanged)
		Q_PROPERTY(int itemFixedWidth READ itemFixedWidth WRITE setItemFixedWidth NOTIFY itemFixedWidthChanged)
		Q_PROPERTY(int itemFixedHeight READ itemFixedHeight WRITE setItemFixedHeight NOTIFY itemFixedHeightChanged)
private:
	ViewModel() { };
	static ViewModel* m_instance;
public:
	static ViewModel* instance() {
		if (m_instance == nullptr) m_instance = new ViewModel();
		return m_instance;
	}

	QList<Explorer*> projects() { return m_projects; }
	QString message() const { return m_message; }
	int count() { return m_projects.size(); }
	int selectedItem() const { return m_selectedItem; }
	QString path() const { return m_path; }
	QString dir() const { return m_dir; }
	QString log() const { return m_log; }
	QString date() const { return m_date; }
	bool full() const { return m_full; }
	bool pressedCtrl() const { return m_pressedCtrl; }
	qreal scale() const { return m_scale; }
	int scaledItemWidth() const { return m_scaledItemWidth; }
	int scaledItemHeight() const { return m_scaledItemHeight; }
	int itemFixedWidth() const { return m_itemFixedWidth; }
	int itemFixedHeight() const { return m_itemFixedHeight; }

	public slots:
	void setProjects(QList<Explorer*> m) { m_projects = m; }
	void setMessage(QString m) { m_message = m; emit messageChanged(); }
	void selectItem(int m) { m_selectedItem = m; emit itemSelected(); }
	void setPath(QString m) { m_path = m; emit pathChanged(); }
	void setDir(QString m) { m_dir = m; emit dirChanged(); }
	void setLog(QString m) { m_log = m; emit logChanged(); }
	void setDate(QString m) { m_date = m; emit dateChanged(); }
	void setFull(bool m) { m_full = m; emit fullChanged(); }
	void pressCtrl(bool m) { m_pressedCtrl = m; emit pressedCtrlChanged(); }
	void setScale(qreal m) { m_scale = m; emit scaleChanged(); }
	void setScaledItemWidth(int m) { m_scaledItemWidth = m; emit scaledItemWidthChanged(); }
	void setScaledItemHeight(int m) { m_scaledItemHeight = m; emit scaledItemHeightChanged(); }
	void setItemFixedWidth(int m) { m_itemFixedWidth = m; emit itemFixedWidthChanged(); }
	void setItemFixedHeight(int m) { m_itemFixedHeight = m; emit itemFixedHeightChanged(); }

signals:
	void messageChanged();
	void itemSelected();
	void pathChanged();
	void dirChanged();
	void logChanged();
	void dateChanged();
	void dirRemove();
	void dirRefresh();
	void logClear();
	void zoomIn();
	void zoomOut();
  void fullChanged();
	void pressedCtrlChanged();
	void scaleChanged();
	void scaledItemWidthChanged();
	void scaledItemHeightChanged();
	void itemFixedWidthChanged();
	void itemFixedHeightChanged();

private:
	QList<Explorer*> m_projects;
	QString m_message;
	int m_selectedItem;
	QString m_path;
	QString m_dir;
	QString m_log;
	QString m_date;
	bool m_full = false;
	bool m_pressedCtrl = false;
	qreal m_scale = 1;
	int m_scaledItemWidth = 720;
	int m_scaledItemHeight = 1080;
	int m_itemFixedWidth = 720;
	int m_itemFixedHeight = 1280;
};