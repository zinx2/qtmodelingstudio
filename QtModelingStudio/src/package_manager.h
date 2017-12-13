#pragma once
#include <QXmlSimpleReader>
#include <QXmlStreamWriter>
#include "item_model.h"

#define FILE_XML "package.xml"
#define FILE_HEADER "model.h"

//struct Class {
//	QString name;
//	QList<Proto> properties;
//};
//
//struct Package {
//	QString dir;
//	QString name;
//	QList<Class> classes;
//};

class PackageManager : public QObject {
	Q_OBJECT
public:
	static PackageManager* instance() {
		if (m_instance == nullptr) m_instance = new PackageManager();
		return m_instance;
	}
	~PackageManager() {
		delete m_xml;
	}

	void generate(int id) 
	{
		ListModel* listModel = ListModel::instance();		
		Proto* package = listModel->iterate(id);
		if (package->type() != Object::TYPE::PACKAGE)
			return;

		QFile::remove(package->dir() + FILE_XML);
		QFile fXML(package->dir() + FILE_XML);
		if (fXML.open(QFile::WriteOnly | QFile::Text)) {

			if (m_xml != nullptr)
				delete m_xml;

			m_xml = new QXmlStreamWriter(&fXML);
			m_xml->setAutoFormatting(true);
			m_xml->writeStartDocument();
			m_xml->writeStartElement("package");
			m_xml->writeAttribute("name", package->name());
		}		

		int packageRowId = listModel->getRowId(id);
		int offset = packageRowId + package->offset();
		for (int i = packageRowId+1; i < offset; i++)
		{
			if (listModel->objs()[i]->type() == Object::TYPE::CLASS) 
			{
				m_code += "class " + listModel->objs()[i]->name() + " : public QObject {\n";
				m_xml->writeStartElement("class");
				m_xml->writeAttribute("name", listModel->objs()[i]->name());

				m_code += "  Q_OBJECT\n";
				for (int j = i + 1; j < offset; j++) 
				{
					if (listModel->objs()[j]->type() != Object::TYPE::PROPERTY) break;					
					appendProperty(listModel->objs()[j]);
				}

				m_code += "\n  public:\n";
				for (int j = i + 1; j < offset; j++)
				{
					if (listModel->objs()[j]->type() != Object::TYPE::PROPERTY) break;										
					appendValue(listModel->objs()[j]);
				}

				m_code += "\n  public slots:\n";
				for (int j = i + 1; j < offset; j++)
				{
					if (listModel->objs()[j]->type() != Object::TYPE::PROPERTY) break;
					appendSlot(listModel->objs()[j]);
				}

				m_code += "\n  signals:\n";
				for (int j = i + 1; j < offset; j++)
				{
					if (listModel->objs()[j]->type() != Object::TYPE::PROPERTY) break;
					appendSignal(listModel->objs()[j]);
				}

				m_code += "\n  private:\n";
				for (int j = i + 1; j < offset; j++)
				{
					if (listModel->objs()[j]->type() != Object::TYPE::PROPERTY) break;
					appendMemValue(listModel->objs()[j]);
				}

				m_code += "};\n\n";
				m_xml->writeEndElement();
			}			
		}		

		/* Write Models. */
		QFile *fHeader = new QFile;
		QString hName = package->dir() + FILE_HEADER;
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

protected:

	void appendProperty(Proto* p) {

		QString uName = p->name(); uName[0] = uName[0].toUpper();

		m_code += "    Q_PROPERTY(" + datalistType(p) + " " + p->name()
			+ " READ " + p->name()
			+ (!p->isReadOnly() ? " WRITE set" + uName : "")
			+ " NOTIFY " + p->name() + "Changed)\n";

		m_xml->writeStartElement("property");
		m_xml->writeAttribute("name", p->name());

		/*if (!p->listType().compare("map") || !p->listType().compare("hash")) {
			m_xml->writeAttribute("keyType", p->dataType());
			m_xml->writeAttribute("valueType", p->valueType());
		}*/

		m_xml->writeAttribute("dataType", p->dataType());
		m_xml->writeAttribute("listType", p->listType());
		m_xml->writeAttribute("readOnly", p->isReadOnly() ? "true" : "false");
		m_xml->writeEndElement();
	}
	void appendValue(Proto* p) {
		m_code += "    " + datalistType(p) + " " + p->name() + "() const { return m_" + p->name() + "; }\n";
	}
	void appendSlot(Proto* p) {
		QString uName = p->name(); uName[0] = uName[0].toUpper();
		m_code += "    void set" + uName + "(const " + datalistType(p) + " " + p->name() + ") { m_" + p->name() + " = " + p->name() + "; emit " + p->name() + "Changed(); }\n";
	}
	void appendSignal(Proto* p) {
		m_code += "    void " + p->name() + "Changed();\n";
	}
	void appendMemValue(Proto* p) {
		m_code += "    " + datalistType(p) + " m_" + p->name() + ";\n";
	}

private:
	static PackageManager *m_instance;
	PackageManager() {
		m_code +=
			"#pragma once\n"
			"#include <QObject>\n"
			/*"#include <QMap>\n"
			"#include <QHash>\n"*/
			"#include <QList>\n\n";
	}

	QString m_code;
	QList<Proto*> m_packages;
	QXmlStreamWriter *m_xml = nullptr;
	QString datalistType(Proto* p) {
		if (!p->listType().compare("list")) 
			p->setDataType("QList<" + p->dataType() + "*>");
		//else if (!p->listType().compare("map"))
		//	p->setDataType("QMap<" + p->dataType() + ", " + p->valueType() + "*>");
		//else if (!p->listType().compare("hash"))
		//	p->setDataType("QHash<" + p->dataType() + ", " + p->valueType() + "*>");

		return p->dataType();
	}
};

