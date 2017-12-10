#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qheader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);	

	QAction *actionAdd     = new QAction(QStringLiteral("��Ű�� ����"), this);
	actionAdd->setIconText(QStringLiteral("��Ű�� ����"));

	QAction *actionOpen    = new QAction(QStringLiteral("��Ű�� ����"), this);
	actionOpen->setIconText(QStringLiteral("��Ű�� ����"));

	QAction *actionSave    = new QAction(QStringLiteral("��Ű�� ����"), this);
	actionSave->setIconText(QStringLiteral("��Ű�� ����"));

	QAction *actionRemove = new QAction(QStringLiteral("��Ű�� ����"), this);
	actionRemove->setIconText(QStringLiteral("��Ű�� ����"));

	QAction *actionExtract = new QAction(QStringLiteral("�� ����"), this);
	actionExtract->setIconText(QStringLiteral("�� ����"));

	QAction *actionExit    = new QAction(QStringLiteral("������"), this);	
	actionExit->setIconText(QStringLiteral("������"));
	
	actionAdd->setShortcut(QKeySequence("Ctrl+N"));
	actionOpen->setShortcut(QKeySequence("Ctrl+O"));
	actionSave->setShortcut(QKeySequence("Ctrl+S"));
	actionRemove->setShortcut(QKeySequence("Ctrl+R"));
	actionExtract->setShortcut(QKeySequence("Ctrl+E"));
	actionExit->setShortcut(QKeySequence("Ctrl+Q"));
	
	connect(actionAdd, SIGNAL(triggered()), this, SLOT(onAdd()));
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
	connect(actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
	connect(actionRemove, SIGNAL(triggered()), this, SLOT(onRemove()));
	connect(actionExtract, SIGNAL(triggered()), this, SLOT(onExtract()));
	connect(actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

	QMenu *menuFile = menuBar()->addMenu(QStringLiteral("����"));
	menuFile->addAction(actionAdd);
	menuFile->addAction(actionOpen);
	menuFile->addAction(actionSave);
	menuFile->addAction(actionRemove);
	menuFile->addAction(actionExtract);
	menuFile->addAction(actionExit);
		
	QToolBar *toolbar = addToolBar(tr("&file"));
	toolbar->setMovable(false);

	toolbar->addAction(actionAdd);
	toolbar->addAction(actionOpen);
	toolbar->addAction(actionSave);
	toolbar->addAction(actionRemove);
	toolbar->addAction(actionExtract);
	toolbar->addAction(actionExit);
}
void MainWindow::onAdd()
{
	qDebug() << "ADD";
}
void MainWindow::onOpen()
{
	qDebug() << "OPEN";
}
void MainWindow::onSave()
{
	qDebug() << "SAVE";
}
void MainWindow::onExtract()
{
	qDebug() << "EXTRACT";
}
void MainWindow::onRemove()
{
	qDebug() << "REMOVE";
}
MainWindow::~MainWindow()
{
    delete ui;
}
