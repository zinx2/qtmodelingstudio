#pragma once
#include <QObject>
#include <QList>
#include <QMap>
#include <QFile>
#include <QXmlSimpleReader>
#include <QXmlStreamWriter>

#define FILE_XML "model.xml"
#define FILE_HEADER "model.h"

//class Proto : public QObject {
//	Q_OBJECT
//		Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
//		Q_PROPERTY(int parent READ parent WRITE setParent NOTIFY parentChanged)
//		Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
//		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
//		Q_PROPERTY(QList<int> children READ children WRITE setChildren NOTIFY childrenChanged)
//public:
//	enum TYPE { PACKAGE, CLASS, PROPERTY };
//	Proto(int id, int pid, int type, QString name) : m_id(id), m_name(name), m_type(type), m_parent(pid) { }
//
//	int id() const { return m_id; }
//	int parent() const { return m_parent; }
//	int type() const { return m_type; }
//	QString name() const { return m_name; }
//	QList<int> children() const { return m_children; }
//
//	public slots :
//	void setId(const int m) { m_id = m; emit idChanged(); }
//	void setParent(const int m) { m_parent = m; emit parentChanged(); }
//	void setType(const int m) { m_type = m; emit typeChanged(); }
//	void setName(const QString m) { m_name = m; emit nameChanged(); }
//	void setChildren(const QList<int> m) { m_children = m; emit childrenChanged(); }
//	bool appendChild(const int targetId) {
//		/* FIND IF THE EQUAL ID EXISTS IN LIST. */
//		for (int idx : m_children) {
//			if (targetId == idx) return false;
//		}
//		m_children.append(targetId);
//		emit childrenChanged();
//		return true;
//	}
//	bool removeChild(const int targetId) {
//		for (int i = 0; i < m_children.size(); i++) {
//			if (targetId == m_children[i]) {
//				m_children.removeAt(i);
//				emit childrenChanged();
//				return true;
//			}
//		}
//		return false;
//	}
//	bool moveChild(const int fromId, const int toId) {
//		int fromIndex = findChildIndex(fromId);
//		int toIndex = findChildIndex(toId);
//		if (fromIndex == -1 || toIndex == -1)
//			return false;
//
//		m_children.move(fromIndex, toIndex);
//		emit childrenChanged();
//		return true;
//	}
//
//
//signals:
//	void idChanged();
//	void parentChanged();
//	void nameChanged();
//	void typeChanged();
//	void childrenChanged();
//
//protected:
//	int findChildIndex(int targetId) {
//		for (int i = 0; i < m_children.size(); i++) {
//			if (targetId == m_children[i]) {
//				return i;
//			}
//		}
//		return -1;
//	}
//
//private:
//	int m_id;
//	int m_parent;
//	int m_type;
//	QString m_name;
//	QList<int> m_children;
//};

//class Property : public Proto {
//	Q_OBJECT
//		Q_PROPERTY(QString dataType READ dataType WRITE setDataType NOTIFY dataTypeChanged)
//		Q_PROPERTY(QString valueType READ valueType WRITE setValueType NOTIFY valueTypeChanged)
//		Q_PROPERTY(QString listType READ listType WRITE setListType NOTIFY listTypeChanged)
//		Q_PROPERTY(bool isReadOnly READ isReadOnly WRITE setIsReadOnly NOTIFY isReadOnlyChanged)
//
//public:
//	Property(int id, int parent, int type, QString name) : Proto(id, parent, type, name) { }
//	QString dataType() const { return m_dataType; }
//	QString valueType() const { return m_valueType; }
//	QString listType() const { return m_listType; }
//	bool isReadOnly() const { return m_isReadOnly; }
//
//	public slots :
//	void setDataType(const QString m) { m_dataType = m; emit dataTypeChanged(); }
//	void setValueType(const QString m) { m_valueType = m; emit valueTypeChanged(); }
//	void setListType(const QString m) { m_listType = m; emit listTypeChanged(); }
//	void setIsReadOnly(const bool m) { m_isReadOnly = m; emit isReadOnlyChanged(); }
//
//signals:
//	void dataTypeChanged();
//	void valueTypeChanged();
//	void listTypeChanged();
//	void isReadOnlyChanged();
//
//private:
//	QString m_dataType;
//	QString m_valueType;
//	QString m_listType;
//	bool m_isReadOnly = false;
//};
//
//class Class : public Proto {
//	Q_OBJECT
//		Q_PROPERTY(QList<int> properties READ properties WRITE setProperties NOTIFY propertiesChanged)
//
//public:
//	Class(int id, int parent, int type, QString name) : Proto(id, parent, type, name) { }
//	QList<int> properties() const { return m_properties; }
//
//	public slots :
//		void setProperties(const QList<Property*> m) { m_properties = m; emit propertiesChanged(); }
//
//	bool appendProperty(Property* p) {
//		if (checkPropertyName(p->name()) < 0) {
//
//			if (!p->listType().compare("map") || !p->listType().compare("hash")) {
//				if (p->valueType().isEmpty())
//					return false;
//			}
//
//			m_properties.append(p);
//			emit propertiesChanged();
//			return true;
//		}
//		return false;
//	}
//	bool removeProperty(int rowId) {
//		if (rowId < m_properties.size()) {
//			m_properties.removeAt(rowId);
//			emit propertiesChanged();
//			return true;
//		}
//		return false;
//	}
//	bool modifyProperty(int rowId, Property* p) {
//		if (rowId >= m_properties.size())
//			return false;
//
//		if (checkPropertyName(p->name()) >= 0) {
//			m_properties[rowId] = p;
//			emit propertiesChanged();
//			return true;
//		}
//		return false;
//	}
//
//signals:
//	void propertiesChanged();
//
//protected:
//	int checkPropertyName(QString name) {
//		for (int i = 0; i < m_properties.size(); i++) {
//			Property* p = m_properties[i];
//			if (!p->name().compare(name)) {
//				return i;
//			}
//		}
//		return -1;
//	}
//
//private:
//	QList<Property*> m_properties;
//};
//
//class Package : public Proto {
//	Q_OBJECT
//		Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)
//		Q_PROPERTY(Class* service READ service WRITE setService NOTIFY serviceChanged)
//
//public:
//	Package(int id, int parent, int type, QString name) : Proto(id, parent, type, name) { }
//	~Package() {
//		for (Class* c : m_classes)
//			delete c;
//		delete m_service;
//	}
//
//	QString dir() const { return m_dir; }
//	QList<Class*> classes() const { return m_classes; }
//	Class* service() const { return m_service; }
//
//	public slots :
//	void setDir(const QString m) { m_dir = m; emit dirChanged(); }
//	void setClasses(const QList<Class*> m) { m_classes = m; emit classesChanged(); }
//	void setService(Class* m) { m_service = m; emit serviceChanged(); }
//	bool appendClass(Class* c) {
//		if (checkClassName(c->name()) < 0) {
//			m_classes.append(c);
//			emit classesChanged();
//			return true;
//		}
//		return false;
//	}
//	void removeClass(int rowId) {
//		if (rowId < m_classes.size()) {
//			m_classes.removeAt(rowId);
//			emit classesChanged();
//		}
//	}
//	bool modifyClass(int rowId, Class* c) {
//		if (rowId >= m_classes.size())
//			return false;
//
//		if (checkClassName(c->name()) >= 0) {
//			m_classes[rowId] = c;
//			emit classesChanged();
//			return true;
//		}
//		return false;
//	}
//	void modifyClassPosition(int fromRowId, int toRowId) {
//		if (fromRowId < m_classes.size() || toRowId < m_classes.size()) {
//			m_classes.move(fromRowId, toRowId);
//			emit classesChanged();
//		}
//	}
//
//signals:
//	void dirChanged();
//	void classesChanged();
//	void serviceChanged();
//
//protected:
//	int checkClassName(QString name) {
//		for (int i = 0; i < m_classes.size(); i++) {
//			Class* p = m_classes[i];
//			if (!p->name().compare(name)) {
//				return i;
//			}
//		}
//		return -1;
//	}
//
//private:
//	QString m_dir;
//	QList<Class*> m_classes;
//	Class* m_service;
//};
//class Service : public QObject {
//	Q_OBJECT
//		Q_PROPERTY(QList<Proto*> objs READ objs WRITE setObjs NOTIFY objsChanged)
//public:
//	Service* instance() {
//		if (m_instance == nullptr)
//			m_instance = new Service();
//		return m_instance;
//	}
//
//	QList<Proto*> objs() const { return m_objs; }
//
//	public slots:
//	void setObjs(QList<Proto*> m) { m_objs = m; }
//	void append(Proto* p) {
//		int toIndex = -1;
//		for (int i = 0; i < m_objs.size(); i++) {
//			if (m_objs[i]->id() == p->parent()) 
//				toIndex = i;
//		}
//
//		if (toIndex > -1) {
//			if (m_objs[toIndex]->appendChild(p->id())) {
//				m_objs.insert(toIndex, p);
//				
//				/* AFTER... MOVE 'Service' CLASS... */
//				emit objsChanged();
//			}
//		}
//		else {
//			m_objs.append(p);
//			emit objsChanged();
//		}
//	}
//	bool remove(int targetId) {
//		Proto* target = iterate(targetId);
//		if (target == nullptr) return false;
//		
//		Proto* parent = iterate(target->parent());
//		if (parent != nullptr) 
//			parent->removeChild(targetId);
//
//		/* RELEASE CHILDREN */
//		removeChildAll(target);		
//
//		/* RELEASE PACKAGE */
//		return removeObj(target);
//	}
//
//	void move(int fromId, int toId) {
//		Proto* target = iterate(fromId);				
//		if (target != nullptr) {
//			Proto* parent = iterate(target->parent());
//			parent->moveChild(fromId, toId);
//			emit objsChanged();
//		}
//	}
//
//signals:
//	void objsChanged();
//
//protected:
//	Proto* iterate(int id) {
//		Proto* obj = nullptr;
//		for (int i = 0; i < m_objs.size(); i++) {
//			if (id == m_objs[i]->id()) {
//				obj = m_objs[i];
//				break;
//			}
//		}
//		return obj;
//	}
//	void removeChildAll(Proto* target) {
//		if (target->children().size() == 0) return;
//		for (int i = 0; i < target->children().size(); i++) {
//			Proto* child = iterate(target->children()[i]);
//			removeObj(child);
//			delete child;
//			child = nullptr;
//			removeChildAll(child);
//		}
//	}
//	bool removeObj(Proto* target) {
//		for (int i = 0; i < m_objs.size(); i++) {
//			if (target->id() == m_objs[i]->id()) {
//				m_objs.removeAt(i);
//				delete target;
//				target = nullptr;
//				emit objsChanged();
//				return true;
//			}
//		}
//		return false;
//	}
//
//private:
//	static Service* m_instance;
//	Service() { }
//
//	QList<Proto*> m_objs;
//};
//struct Class {
//	QString name;
//	QList<Property> properties;
//};
//
//struct Model {
//	QString dir;
//	QString name;
//	QList<Class> classes;
//};

//class ModelManager : public QObject {
//	Q_OBJECT
//public:
//	static ModelManager* instance() {
//		if (m_instance == nullptr) m_instance = new ModelManager();
//		return m_instance;
//	}
//	~ModelManager() {
//		delete m_xml;
//	}
//
//	int modelSize() { return m_models.size(); }
//	void generate(int modelRowId) {
//
//		if (modelRowId >= modelSize()) return;
//
//		Model* m = m_models[modelRowId];
//
//		QFile::remove(m->dir() + FILE_XML);
//		QFile fXML(m->dir() + FILE_XML);
//		if (fXML.open(QFile::WriteOnly | QFile::Text)) {
//
//			if (m_xml != nullptr)
//				delete m_xml;
//
//			m_xml = new QXmlStreamWriter(&fXML);
//			m_xml->setAutoFormatting(true);
//			m_xml->writeStartDocument();
//			m_xml->writeStartElement("model");
//			m_xml->writeAttribute("name", m->name());
//		}
//
//		/* Create Models. */
//		for (Class* c : m->classes()) appendClass(c);
//		m_xml->writeEndElement();
//
//		/* Write Models. */
//		QFile *fHeader = new QFile;
//		QString hName = m->dir() + FILE_HEADER;
//		fHeader->setFileName(hName);
//		fHeader->open(QIODevice::WriteOnly);
//
//		QByteArray contetns;
//		contetns.append(m_code);
//		fHeader->write(contetns);
//		fHeader->close();
//
//		m_xml->writeEndDocument();
//		fXML.close();
//
//		m_code = "";
//	}
//	bool addModel(QString dir, QString name) {
//
//		if (name.isEmpty())
//			return false;
//
//		Model* m = new Model();
//
//		/* WHEN DIR IS EMPTY, DON'T APPEND '/'. */
//		dir = dir.isEmpty() ? "" : dir + "/";
//		m->setDir(dir); m->setName(name);
//		m->appendClass(new Class{ "Service",{} });
//		m_models.append(m);
//		emit modelChanged();
//		return true;
//	}
//	void removeModel(int modelRowId) {
//		if (modelRowId >= modelSize()) {
//			m_models.removeAt(modelRowId);
//			emit modelChanged();
//		}
//	}
//	bool addProperty(int modelRowId, int classRowId, Property p) {
//		int checkNum = checkPropertyName(modelRowId, classRowId, p.name);
//		if (checkNum == -1) {
//			m_models[modelRowId].classes[classRowId].properties.append(p);
//			emit propertyChanged();
//			return true;
//		}
//		return false;
//	}
//	bool removeProperty(int modelRowId, int classRowId, QString name) {
//		int checkNum = checkPropertyName(modelRowId, classRowId, name);
//		if (checkNum > -1) {
//			m_models[modelRowId].classes[classRowId].properties.removeAt(checkNum);
//			emit propertyChanged();
//			return true;
//		}
//		return false;
//	}
//	bool modifyProperty(int modelRowId, int classRowId, Property p) {
//		int checkNum = checkPropertyName(modelRowId, classRowId, p.name);
//		if (checkNum > -1) {
//			m_models[modelRowId].classes[classRowId].properties[checkNum] = p;
//			emit propertyChanged();
//			return true;
//		}
//		return false;
//	}
//	bool addClass(int modelRowId, Class c) {
//		int checkNum = checkClassName(modelRowId, c.name);
//		if (checkNum == -1) {
//			int size = m_models[modelRowId].classes.size();
//			m_models[modelRowId].classes.insert(size - 1, c);
//			emit classChanged();
//			return true;
//		}
//		return false;
//	}
//	bool removeClass(int modelRowId, QString name) {
//		int checkNum = checkClassName(modelRowId, name);
//		if (checkNum > -1) {
//			m_models[modelRowId].classes.removeAt(checkNum);
//			emit classChanged();
//			return true;
//		}
//		return false;
//	}
//	bool modifyClassPosition(int modelRowId, int fromClassRowId, int toClassRowId) {
//
//		/* IF IT WOULD BE THE FOLLOWING CASE, PLEASE NO MODIFY THE POSITION.
//		1. WHEN TARGET IS SERVICE CLASS.
//		2. WHEN TARGET ROW IS THE ROW THAT SERVICE IS POSITIONED. */
//
//		if (modelSize() == 0)
//			return false;
//
//		int size = m_models[modelRowId].classes.size();
//		if (fromClassRowId == size - 1 || toClassRowId == size - 1)
//			return false;
//
//		m_models[modelRowId].classes.move(fromClassRowId, toClassRowId);
//		emit classChanged();
//		return true;
//	}
//	bool modifyClass(int rowId, Class c) {
//		for (int i = 0; i < m_models[rowId].classes.size(); i++) {
//			if (!c.name.compare(m_models[rowId].classes[i].name)) {
//				m_models[rowId].classes[i] = c;
//				emit classChanged();
//				return true;
//			}
//		}
//		return false;
//	}
//	bool parse(QString filePath) {
//		QFile fXML(filePath);
//		if (fXML.open(QFile::ReadOnly | QFile::Text)) {
//			QXmlStreamReader xml(&fXML);
//			xml.readNextStartElement();
//			QString xmlName = xml.name().toString();
//			if (xmlName == "model") {
//				Model m; m.name = xml.attributes().value("name").toString();
//
//				Class c;
//				while (xml.readNext() && !xml.atEnd()) {
//					xmlName = xml.name().toString();
//					if (!xmlName.compare("class")) {
//						if (!c.name.isEmpty()) {
//							m.classes.append(c); c.properties.clear();
//						}
//						c.name = xml.attributes().value("name").toString();
//					}
//					else if (!xmlName.compare("property")) {
//						Property p;
//						p.name = xml.attributes().value("name").toString();
//						if (!p.name.isEmpty()) {
//							p.dataType = xml.attributes().value("dataType").toString();
//							p.isReadOnly = !xml.attributes().value("isReadOnly").toString().compare("true") ? true : false;
//							p.listType = xml.attributes().value("listType").toString();
//							p.valueType = xml.attributes().value("valueType").toString();
//							c.properties.append(p);
//						}
//					}
//				}
//				m_models.append(m);
//				fXML.close();
//				return true;
//			}
//			fXML.close();
//		}
//		return false;
//	}
//
//signals:
//	void modelChanged();
//	void classChanged();
//	void propertyChanged();
//
//protected:
//	void appendClass(Class* c) {
//		m_code += "class " + c->name() + " : public QObject {\n";
//		m_xml->writeStartElement("class");
//		m_xml->writeAttribute("name", c->name());
//
//		m_code += "  Q_OBJECT\n";
//		for (Property* p : c->properties()) appendProperty(p);
//
//		m_code += "\n  public:\n";
//		for (Property* p : c->properties()) appendValue(p);
//
//		m_code += "\n  public slots:\n";
//		for (Property* p : c->properties()) appendSlot(p);
//
//		m_code += "\n  signals:\n";
//		for (Property* p : c->properties()) appendSignal(p);
//
//		m_code += "\n  private:\n";
//		for (Property* p : c->properties()) appendMemValue(p);
//
//		m_code += "};\n\n";
//		m_xml->writeEndElement();
//	}
//	void appendProperty(Property* p) {
//
//		QString uName = p->name(); uName[0] = uName[0].toUpper();
//
//		m_code += "    Q_PROPERTY(" + datalistType(p) + " " + p.name
//			+ " READ " + p.name
//			+ (!p.isReadOnly ? " WRITE set" + uName : "")
//			+ " NOTIFY " + p.name + "Changed)\n";
//
//		m_xml->writeStartElement("property");
//		m_xml->writeAttribute("name", p.name);
//
//		if (!p.listType.compare("map") || !p.listType.compare("hash")) {
//			m_xml->writeAttribute("keyType", p.dataType);
//			m_xml->writeAttribute("valueType", p.valueType);
//		}
//
//		m_xml->writeAttribute("dataType", p.dataType);
//		m_xml->writeAttribute("listType", p.listType);
//		m_xml->writeAttribute("readOnly", p.isReadOnly ? "true" : "false");
//		m_xml->writeEndElement();
//	}
//	void appendValue(Property p) {
//		m_code += "    " + datalistType(p) + " " + p.name + "() const { return m_" + p.name + "; }\n";
//	}
//	void appendSlot(Property p) {
//		QString uName = p.name; uName[0] = uName[0].toUpper();
//		m_code += "    void set" + uName + "(const " + datalistType(p) + " " + p.name + ") { m_" + p.name + " = " + p.name + "; emit " + p.name + "Changed(); }\n";
//	}
//	void appendSignal(Property p) {
//		m_code += "    void " + p.name + "Changed();\n";
//	}
//	void appendMemValue(Property p) {
//		m_code += "    " + datalistType(p) + " m_" + p.name + ";\n";
//	}
//	int checkClassName(int modelRowId, QString name) {
//		if (modelRowId >= modelSize()) return -2;
//
//		Model m = m_models[modelRowId];
//		for (int i = 0; i < m.classes.size(); i++) {
//			Class c = m.classes[i];
//			if (!c.name.compare(name)) {
//				return i;
//			}
//		}
//		return -1;
//	}
//	int checkPropertyName(int modelRowId, int classRowId, QString name) {
//
//		/* CHECK SIZE OVER FLOW. AND RETURN INTEGER -2 OR -3  */
//		if (modelRowId >= modelSize()) return -2;
//		if (classRowId >= m_models[modelRowId].classes.size()) return -3;
//
//		Class c = m_models[modelRowId].classes[classRowId];
//		for (int i = 0; i < c.properties.size(); i++) {
//			Property p = c.properties[i];
//			if (!p.name.compare(name)) {
//				return i;
//			}
//		}
//		return -1;
//	}
//
//private:
//	static ModelManager *m_instance;
//	ModelManager() {
//		m_code +=
//			"#pragma once\n"
//			"#include <QObject>\n"
//			"#include <QMap>\n"
//			"#include <QHash>\n"
//			"#include <QList>\n\n";
//	}
//
//	QString m_code;
//	QList<Model*> m_models;
//	QXmlStreamWriter *m_xml = nullptr;
//	QString datalistType(Property* p) {
//		if (!p->listType().compare("list")) p->setDataType("QList<" + p->dataType() + "*>");
//		else if (!p->listType().compare("map"))
//			p->setDataType("QMap<" + p->dataType() + ", " + p->valueType() + "*>");
//		else if (!p->listType().compare("hash"))
//			p->setDataType("QHash<" + p->dataType() + ", " + p->valueType() + "*>");
//
//		return p->dataType();
//	}
//};

//ModelManager* ModelManager::m_instance = nullptr;