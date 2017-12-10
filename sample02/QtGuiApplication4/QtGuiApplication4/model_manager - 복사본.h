#pragma once
#include <QObject>
#include <QList>
#include <QMap>
#include <QFile>
#include <QXmlSimpleReader>
#include <QXmlStreamWriter>

#define FILE_XML "model.xml"
#define FILE_HEADER "model.h"

struct Property {
	QString name;
	QString dataType;
	QString valueType;
	QString listType;
	bool isReadOnly = false;
};

struct Class {
	QString name;
	QList<Property> properties;
};

struct Model {
	QString dir;
	QString name;
	QList<Class> classes;
};

class ModelManager : public QObject {
	Q_OBJECT
public:
	static ModelManager* instance() {
		if (m_instance == nullptr) m_instance = new ModelManager();
		return m_instance;
	}
	~ModelManager() {
		delete m_xml;
	}

	int modelSize() { return m_models.size(); }
	void generate(int modelRowId) {

		if (modelRowId >= modelSize()) return;

		Model m = m_models[modelRowId];

		QFile::remove(m.dir+FILE_XML);
		QFile fXML(m.dir+ FILE_XML);
		if (fXML.open(QFile::WriteOnly | QFile::Text)) {			
			
			if (m_xml != nullptr) 
				delete m_xml;

			m_xml = new QXmlStreamWriter(&fXML);
			m_xml->setAutoFormatting(true);
			m_xml->writeStartDocument();
			m_xml->writeStartElement("model");
			m_xml->writeAttribute("name", m.name);
		}

		/* Create Models. */
		for (Class c : m.classes) appendClass(c);
		m_xml->writeEndElement();

		/* Write Models. */
		QFile *fHeader = new QFile;
		QString hName = m.dir + FILE_HEADER;
		fHeader->setFileName(hName);
		fHeader->open(QIODevice::WriteOnly);

		QByteArray contetns; 
		contetns.append(m_code);
		fHeader->write(contetns);
		fHeader->close();

		m_xml->writeEndDocument();
		fXML.close();

		m_code = "";		
	}
	bool addModel(QString dir, QString name) {
		
		if (name.isEmpty()) 
			return false;
		
		/* WHEN DIR IS EMPTY, DON'T APPEND '/'. */
		dir = dir.isEmpty() ? "" : dir + "/";
		Model m = { dir, name };
		m.classes.append({ "Service", {} });
		m_models.append(m);
		emit modelChanged();
		return true;
	}
	void removeModel(int modelRowId) {
		if (modelRowId >= modelSize()) {
			m_models.removeAt(modelRowId);
			emit modelChanged();
		}
	}
	bool addProperty(int modelRowId, int classRowId, Property p) {
		int checkNum = checkPropertyName(modelRowId, classRowId, p.name);
		if (checkNum == -1) {
			m_models[modelRowId].classes[classRowId].properties.append(p);
			emit propertyChanged();
			return true;
		}
		return false;
	}
	bool removeProperty(int modelRowId, int classRowId, QString name) {
		int checkNum = checkPropertyName(modelRowId, classRowId, name);
		if (checkNum > -1) {
			m_models[modelRowId].classes[classRowId].properties.removeAt(checkNum);
			emit propertyChanged();
			return true;
		}
		return false;
	}
	bool modifyProperty(int modelRowId, int classRowId, Property p) {
		int checkNum = checkPropertyName(modelRowId, classRowId, p.name);
		if (checkNum > -1) {
			m_models[modelRowId].classes[classRowId].properties[checkNum] = p;
			emit propertyChanged();
			return true;
		}
		return false;
	}
	bool addClass(int modelRowId, Class c) {
		int checkNum = checkClassName(modelRowId, c.name);
		if (checkNum == -1 ) {
			int size = m_models[modelRowId].classes.size();
			m_models[modelRowId].classes.insert(size-1, c);
			emit classChanged();
			return true;
		}
		return false;
	}
	bool removeClass(int modelRowId, QString name) {
		int checkNum = checkClassName(modelRowId, name);
		if (checkNum > -1) {
			m_models[modelRowId].classes.removeAt(checkNum);
			emit classChanged();
			return true;
		}
		return false;
	}
	bool modifyClassPosition(int modelRowId, int fromClassRowId, int toClassRowId) {

		/* IF IT WOULD BE THE FOLLOWING CASE, PLEASE NO MODIFY THE POSITION.
				1. WHEN TARGET IS SERVICE CLASS.
				2. WHEN TARGET ROW IS THE ROW THAT SERVICE IS POSITIONED. */
		
		if (modelSize() == 0) 
			return false;
		
		int size = m_models[modelRowId].classes.size();			
		if (fromClassRowId == size - 1 || toClassRowId == size -1) 
			return false;

		m_models[modelRowId].classes.move(fromClassRowId, toClassRowId);
		emit classChanged();
		return true;
	}
	bool modifyClass(int rowId, Class c) {
		for (int i = 0; i < m_models[rowId].classes.size(); i++) {
			if (!c.name.compare(m_models[rowId].classes[i].name)) {
				m_models[rowId].classes[i] = c;
				emit classChanged();
				return true;
			}
		}
		return false;
	}
	bool parse(QString filePath) {
		QFile fXML(filePath);
		if (fXML.open(QFile::ReadOnly | QFile::Text)) {
			QXmlStreamReader xml(&fXML);
			xml.readNextStartElement();
			QString xmlName = xml.name().toString();
			if (xmlName == "model") {
				Model m; m.name = xml.attributes().value("name").toString();

				Class c;								
				while (xml.readNext() && !xml.atEnd()) {
					xmlName = xml.name().toString();
					if (!xmlName.compare("class")) {
						if (!c.name.isEmpty()) {
							m.classes.append(c); c.properties.clear();
						}
						c.name = xml.attributes().value("name").toString();						
					}
					else if (!xmlName.compare("property")) {
						Property p;
						p.name = xml.attributes().value("name").toString();
						if (!p.name.isEmpty()) {
							p.dataType = xml.attributes().value("dataType").toString();
							p.isReadOnly = !xml.attributes().value("isReadOnly").toString().compare("true") ? true : false;
							p.listType = xml.attributes().value("listType").toString();
							p.valueType = xml.attributes().value("valueType").toString();
							c.properties.append(p);
						}
					}
				}
				m_models.append(m);				
				fXML.close();
				return true;
			}	
			fXML.close();
		}
		return false;
	}

signals:
	void modelChanged();
	void classChanged();
	void propertyChanged();

protected:
	void appendClass(Class c) {
		m_code += "class " + c.name + " : public QObject {\n";
		m_xml->writeStartElement("class");
		m_xml->writeAttribute("name", c.name);

		m_code += "  Q_OBJECT\n";
		for (Property p : c.properties) appendProperty(p);

		m_code += "\n  public:\n";
		for (Property p : c.properties) appendValue(p);

		m_code += "\n  public slots:\n";
		for (Property p : c.properties) appendSlot(p);

		m_code += "\n  signals:\n";
		for (Property p : c.properties) appendSignal(p);

		m_code += "\n  private:\n";
		for (Property p : c.properties) appendMemValue(p);

		m_code += "};\n\n";
		m_xml->writeEndElement();
	}
	void appendProperty(Property p) {

		QString uName = p.name; uName[0] = uName[0].toUpper();

		m_code += "    Q_PROPERTY(" + datalistType(p) + " " + p.name
			+ " READ " + p.name
			+ (!p.isReadOnly ? " WRITE set" + uName : "")
			+ " NOTIFY " + p.name + "Changed)\n";

		m_xml->writeStartElement("property");
		m_xml->writeAttribute("name", p.name);

		if (!p.listType.compare("map") || !p.listType.compare("hash")) {
			m_xml->writeAttribute("keyType", p.dataType);
			m_xml->writeAttribute("valueType", p.valueType);
		}

		m_xml->writeAttribute("dataType", p.dataType);
		m_xml->writeAttribute("listType", p.listType);
		m_xml->writeAttribute("readOnly", p.isReadOnly ? "true" : "false");
		m_xml->writeEndElement();
	}
	void appendValue(Property p) {
		m_code += "    " + datalistType(p) + " " + p.name + "() const { return m_" + p.name + "; }\n";
	}
	void appendSlot(Property p) {
		QString uName = p.name; uName[0] = uName[0].toUpper();
		m_code += "    void set" + uName + "(const " + datalistType(p) + " " + p.name + ") { m_" + p.name + " = " + p.name + "; emit " + p.name + "Changed(); }\n";
	}
	void appendSignal(Property p) {
		m_code += "    void " + p.name + "Changed();\n";
	}
	void appendMemValue(Property p) {
		m_code += "    " + datalistType(p) + " m_" + p.name + ";\n";
	}
	int checkClassName(int modelRowId, QString name) {
		if (modelRowId >= modelSize()) return -2;

		Model m = m_models[modelRowId];
		for (int i = 0; i < m.classes.size(); i++) {
			Class c = m.classes[i];
			if (!c.name.compare(name)) {
				return i;
			}
		}
		return -1;
	}
	int checkPropertyName(int modelRowId, int classRowId, QString name) {

		/* CHECK SIZE OVER FLOW. AND RETURN INTEGER -2 OR -3  */
		if (modelRowId >= modelSize()) return -2;	
		if (classRowId >= m_models[modelRowId].classes.size()) return -3;

		Class c = m_models[modelRowId].classes[classRowId];
		for (int i = 0; i < c.properties.size(); i++) {
			Property p = c.properties[i];
			if (!p.name.compare(name)) {
				return i;
			}
		}
		return -1;
	}

private:
	static ModelManager *m_instance;
	ModelManager() {
		m_code +=
			"#pragma once\n"
			"#include <QObject>\n"
			"#include <QMap>\n"
			"#include <QHash>\n"
			"#include <QList>\n\n";
	}

	QString m_code;
	QList<Model> m_models;
	QXmlStreamWriter *m_xml = nullptr;
	QString datalistType(Property p) {
		if (!p.listType.compare("list")) p.dataType = "QList<" + p.dataType + ">";
		else if (!p.listType.compare("map"))
			p.dataType = "QMap<" + p.dataType + ", " + p.valueType + ">";
		else if (!p.listType.compare("hash"))
			p.dataType = "QHash<" + p.dataType + ", " + p.valueType + ">";

		return p.dataType;
	}
};

//ModelManager* ModelManager::m_instance = nullptr;