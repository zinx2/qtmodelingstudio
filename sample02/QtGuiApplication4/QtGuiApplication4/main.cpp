#include "QtGuiApplication4.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "model_manager.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QDir>
#include <QDateTime>
//#include "model.h"
//#include "abstract_list_model.h"

#include "list_widget.h"
#include <QListWidget>
#include "q_w.h"
//ModelManager* ModelManager::m_instance = nullptr;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//ListView* v = new ListView;
	QWidget* mw = new QWidget;
	mw->setLayout(new QHBoxLayout);
	ListWidget* v = new ListWidget;
	mw->layout()->addWidget(v);
	
	//ApplicationData data;
	//QQuickWidget *view = new QQuickWidget;
	//view->setSource(QUrl::fromLocalFile("C:/Users/fifa3/source/repos/QtGuiApplication4/QtGuiApplication4/Test1.qml"));
	//view->rootContext()->setContextProperty("applicationData", &data);
	//view->show();

	//QWd *  q = QWd::instance();
	//q->setQuick(view);
	//q->show();
	//QWd * q = new QWd(view);

	//view->show();
	//v->;
	/*AbstractListModel m;
	QList<Proto*> q = {	
		new Proto(0 , -1, Proto::PACKAGE, "Exp"),
		new Proto(1 , 0 , Proto::CLASS, "Class1"),
		new Proto(2 , 1 , Proto::PROPERTY, "pro1_1"),
		new Proto(3 , 1 , Proto::PROPERTY, "pro2_1"),
		new Proto(4 , 1 , Proto::PROPERTY, "pro3_1"),
		new Proto(5 , 1 , Proto::PROPERTY, "pro4_1"),
		new Proto(6 , 0 , Proto::CLASS, "Class2"),
		new Proto(7 , 6 , Proto::PROPERTY,"pro1_2"),
		new Proto(8 , 6 , Proto::PROPERTY,"pro2_2"),
		new Proto(9 , 6 , Proto::PROPERTY,"pro3_2"),
		new Proto(10, 0 , Proto::CLASS, "Class3"),
		new Proto(11, 10, Proto::PROPERTY, "pro1_3"),
		new Proto(12, 10, Proto::PROPERTY, "pro2_3"),
		new Proto(13, 10, Proto::PROPERTY, "pro3_3"),
		new Proto(14, 10, Proto::PROPERTY, "pro4_3"),
		new Proto(15, 10, Proto::PROPERTY, "pro5_3"),
		new Proto(16 , -1, Proto::PACKAGE, "Exp2"),
		new Proto(17 , 16 , Proto::CLASS, "Class1"),
		new Proto(18 , 17 , Proto::PROPERTY, "pro1_21"),
		new Proto(19 , 17 , Proto::PROPERTY, "pro2_21"),
		new Proto(20 , 17 , Proto::PROPERTY, "pro3_21"),
		new Proto(21 , 17 , Proto::PROPERTY, "pro4_21"),
		new Proto(22 , 16 , Proto::CLASS, "Class2"),
		new Proto(23 , 22 , Proto::PROPERTY,"pro1_22"),
		new Proto(24 , 22 , Proto::PROPERTY,"pro2_22"),
		new Proto(25 , 22 , Proto::PROPERTY,"pro3_22"),
		new Proto(26, 16 , Proto::CLASS, "Class3"),
		new Proto(27, 26, Proto::PROPERTY, "pro1_23"),
		new Proto(28, 26, Proto::PROPERTY, "pro2_23"),
		new Proto(29, 26, Proto::PROPERTY, "pro3_23"),
		new Proto(30, 26, Proto::PROPERTY, "pro4_23"),
		new Proto(31, 26, Proto::PROPERTY, "pro5_23"),
	};

	QList<Proto*> q1 = {
		new Proto(0 , -1, Proto::PACKAGE, "Exp"),
		new Proto(1 , 0 , Proto::CLASS, "Class1"),		
		new Proto(2 , 0 , Proto::CLASS, "Class2"),
		new Proto(3 , 0 , Proto::CLASS, "Class3"),
		new Proto(4 , 0 , Proto::CLASS, "Class4"),
		new Proto(5 , 0 , Proto::CLASS, "Class5"),
		new Proto(6 , 1 , Proto::PROPERTY, "prop1_1"),
		new Proto(7 , 1 , Proto::PROPERTY, "prop2_1"),
		new Proto(8 , 1 , Proto::PROPERTY, "prop3_1"),
		new Proto(9 , 1 , Proto::PROPERTY, "prop4_1"),
		new Proto(10 , 2 , Proto::PROPERTY, "prop1"),
		new Proto(11 , 2 , Proto::PROPERTY, "prop2"),
		new Proto(12 , 2 , Proto::PROPERTY, "prop3"),
		new Proto(13 , 2 , Proto::PROPERTY, "prop4"),
	};

	for (Proto* p : q) {
		m.append(p);
	}

	int count = 0;
	for (Proto* p : m.objs()) {
		if (p->type() == Proto::CLASS)
			qDebug() << count << "  " << p->name() << " " << p->parent() << "/" << p->id() << " /" << p->offset();
		else if (p->type() == Proto::PROPERTY)
			qDebug() << count << "      " << p->name() << " " << p->parent() << "/" << p->id() << " /" << p->offset();
		else
			qDebug() << count << p->name() << " " << p->parent() << "/" << p->id() << " /" << p->offset();
		count++;
	}

	m.move(17, 26);
	m.append(new Proto(33, 16, Proto::CLASS, "Class004"));
	m.append(new Proto(34, -1, Proto::PROPERTY, "pro4"));
	m.append(new Proto(32, -1, Proto::PACKAGE, "Exp3"));
	m.append(new Proto(35, 16, Proto::CLASS, "Class005"));
	m.append(new Proto(36, 35, Proto::PROPERTY, "prop1_0041"));
	m.append(new Proto(37, 35, Proto::PROPERTY, "prop2_0042"));
	m.append(new Proto(38, 35, Proto::PROPERTY, "prop3_0043"));
	m.append(new Proto(39, 35, Proto::PROPERTY, "prop4_0044"));

	m.remove(39);
	m.append(new Proto(40, 2, Proto::PROPERTY, "prop3_0023"));
	m.append(new Proto(39, 2, Proto::PROPERTY, "prop4_0024"));



	m.remove(35);
	m.remove(33);
	m.remove(26);
	m.remove(16);
	m.remove(10);

	count = 0;
	qDebug() << " ";
	qDebug() << " ";
	for (Proto* p : m.objs()) {
		if(p->type() == Proto::CLASS)
			qDebug() << count << "  " << p->name() << " " << p->parent() << "/" <<p->id() << " /" << p->offset();
		else if(p->type() == Proto::PROPERTY)
			qDebug() << count << "      " << p->name() << " " << p->parent() << "/" << p->id() << " /" << p->offset();
		else
			qDebug() << count << p->name() << " " << p->parent() << "/" << p->id() << " /" << p->offset();
		count++;
	}*/

	//QList<int> t = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	//QList<int> A = t.mid(0, 0);
	//QList<int> B = t.mid(0, 7);
	//QList<int> C = t.mid(7, 3);
	//QList<int> D = t.mid(10, 2);
	//QList<int> E = t.mid(12, t.size()-12);

	
	/*for (int x : A) qDebug() << x;
	for (int x : B) qDebug() << x;
	for (int x : C) qDebug() << x;
	for (int x : D) qDebug() << x;
	for (int x : E) qDebug() << x;*/

	/*t.clear();
	t.append(A);
	t.append(D);
	t.append(C);
	t.append(B);
	t.append(E);*/
	//t.move(4, 1);
	//for (int x : t) qDebug() << x;


	//Model* m = new Model(0, "Explorer", "model");
	//Class* c1 = new Class(1, "Explorer1", "class");
	//m->appendClass(c1);
	//Property* p1 = new Property(2, "id", "property");
	//p1->setDataType("int");
	//c1->appendProperty(p1);

	//Property* p2 = new Property(3, "name", "property");
	//p2->setDataType("QString");
	//c1->appendProperty(p2);

	//Property* p3 = new Property(4, "qlist", "property");
	//p3->setDataType("QString");
	//p3->setListType("list");
	//c1->appendProperty(p3);

	//Property* p4 = new Property(5, "qmap", "property");
	//p4->setDataType("int");
	//p4->setValueType("QString");
	//p4->setListType("map");
	//c1->appendProperty(p4);

	//Property* p5 = new Property(6, "qhash", "property");
	//p5->setDataType("bool");
	//p5->setValueType("QString");
	//p5->setListType("hash");
	//c1->appendProperty(p5);
	//
	//Class* c2 = new Class(7, "Explorer2", "class");
	//m->appendClass(c2);

	////m->modifyClassPosition(0, 6);
	//
	//qDebug() << m->name();


	//QtGuiApplication4 w;
	//w.show();

	//Explorer1 e;
	//e.setId(9999);
	//qDebug() << e.id();


	/*QList<Class> css = {
		{ "Explorer1",{ { "id", "int", "", "none", true },{ "name", "QString", "", "list", false },{ "isVisible", "bool", "QString", "map", false } } },
		{ "Explorer2",{ { "id", "int", "", "none", true },{ "name", "QString", "", "list", false },{ "isVisible", "bool", "QString", "map", false } } },
		{ "Explorer3",{ { "id", "int", "", "none", true },{ "name", "QString", "", "list", false },{ "isVisible", "bool", "QString", "map", false } } },
		{ "Explorer4",{ { "id", "int", "", "none", true },{ "name", "QString", "", "list", false },{ "isVisible", "bool", "QString", "map", false } } },
		{ "Service",{ { "id", "int", "", "none", true },{ "name", "QString", "", "list", false },{ "isVisible", "bool", "QString", "map", false } } }
	};*/
	
	//ModelManager* m = ModelManager::instance();  
	/*클래스추가성공테스트*/ //m->addModel("", "Test");
	/*클래스추가성공테스트*/ //m->addClass(0, css[0]);
	/*클래스추가성공테스트*/ //m->addClass(0, css[1]);
	/*클래스추가성공테스트*/ //m->addClass(0, css[2]);
	/*클래스추가성공테스트*/ //m->addClass(0, css[3]);
	/*클래스추가실패테스트*/ //m->addClass(1, css[1]);
	/*클래스추가실패테스트*/ //m->addClass(1, css[2]);

	//m->parse("model.xml");
	/*클래스추가실패테스트*/ //m->addClass(0, { "Explorer4",{ { "id", "int", "", "none", true },{ "name", "QString", "", "list", false },{ "isVisible", "bool", "QString", "map", false } } });
	/*클래스추가성공테스트*/ //m->addClass(0, { "Explorer5",{ { "id", "int", "", "none", true },{ "name", "QString", "", "list", false },{ "isVisible", "bool", "QString", "map", false } } });
	/*클래스삭제실패테스트*/ //m->removeClass(0, "Explorer0");
	///*클래스삭제성공테스트*/ m->removeClass(0, "Explorer5");
	/*프로퍼티수정실패테스트*/ //m->modifyProperty(0, 1, { "name1", "QString", "", "" });
	/*프로퍼티수정성공테스트*/ //m->modifyProperty(0, 1, { "name", "float", "", "" });
	/*프로퍼티추가실패테스트*/ //m->addProperty(0, 1, { "name", "int", "", "" });
	/*프로퍼티추가성공테스트*/ //m->addProperty(0, 1, { "name5", "char", "", "" });
	/*프로퍼티추가실패테스트*/ //m->removeProperty(0, 1, "name666");
	///*프로퍼티추가성공테스트*/ m->removeProperty(0, 1, "name5");

	/*클래스위치변경실패테스트*/ //m->modifyClassPosition(0, 0, 4);
	/*클래스위치변경실패테스트*/ //m->modifyClassPosition(0, 4, 2);
	/*클래스위치변경성공테스트*/ //m->modifyClassPosition(0, 1, 3);

	/*모델생성실패테스트*/ //m->generate(1);
	/*모델생성성공테스트*/ //m->generate(0);



	//QDir d;
	//qDebug() << d.path();
	//QString fileName = "service.xml";
		//QFileDialog::getSaveFileName(this, tr("Save Bookmark File"),
	//		QDir::currentPath(),
	//		tr("XBEL Files (*.xbel *.xml)"));

	//QFile::remove(fileName);
	//	QFile file(fileName);
	//	//file.open(QFile::WriteOnly | QFile::Text);
	//	
	//	file.open(QFile::ReadWrite | QFile::Text);

	//	QXmlStreamWriter xml(&file);
	//	xml.setAutoFormatting(true);
	//	xml.writeStartDocument();
	//	xml.writeStartElement("model");

	//	xml.writeStartElement("class");
	//	xml.writeAttribute("name", "care");		

	//	xml.writeStartElement("property");
	//	xml.writeAttribute("name", "id");
	//	xml.writeAttribute("type", "int");
	//	xml.writeAttribute("list", "none");
	//	xml.writeEndElement();

	//	xml.writeStartElement("property");
	//	xml.writeAttribute("name", "name");
	//	xml.writeAttribute("type", "QString");
	//	xml.writeAttribute("list", "list");
	//	xml.writeEndElement();

	//	xml.writeEndElement();


	//	xml.writeStartElement("class");
	//	xml.writeAttribute("name", "care");

	//	xml.writeStartElement("property");
	//	xml.writeAttribute("name", "id");
	//	xml.writeAttribute("type", "int");
	//	xml.writeAttribute("list", "none");
	//	xml.writeEndElement();

	//	xml.writeStartElement("property");
	//	xml.writeAttribute("name", "name");
	//	xml.writeAttribute("type", "QString");
	//	xml.writeAttribute("list", "list");
	//	xml.writeEndElement();

	//	xml.writeEndElement();
	//	xml.writeEndDocument();

		//QXmlStreamReader xml(&file);
		
		//if (xml.readNextStartElement()) {
			//if (xml.name() == "xml" && xml.attributes().value("version") == "1.0") {
				//Q_ASSERT(xml.isStartElement() && xml.name() == "xml");
				/*while (xml.readNextStartElement()) {
					if (xml.name() == "model") {
						xml.readNextStartElement();
						if (xml.name() == "class") {
							qDebug() << xml.attributes().value("name").toString();
						}
					}
				}*/
			//}
			/*else {
				xml.raiseError(QObject::tr("The file isn't an XML version 1.0 file."));
			}*/
		//}
			
		//if (xml.error()) return;
		
		
		
		//file.close();




	//if (!file.open(QFile::WriteOnly | QFile::Text)) {
	//	QMessageBox::warning(this, tr("QXmlStream Bookmarks"),
	//		tr("Cannot write file %1:\n%2.")
	//		.arg(fileName)
	//		.arg(file.errorString()));
	//	return;
	//}

	//XbelWriter writer(treeWidget);
	//if (writer.writeFile(&file))
	//	statusBar()->showMessage(tr("File saved"), 2000);

	return a.exec();
}
