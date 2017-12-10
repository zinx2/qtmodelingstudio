#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qheader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);	

	QAction *actionAdd     = new QAction(QStringLiteral("패키지 생성"), this);
	actionAdd->setIconText(QStringLiteral("패키지 생성"));

	QAction *actionOpen    = new QAction(QStringLiteral("패키지 열기"), this);
	actionOpen->setIconText(QStringLiteral("패키지 열기"));

	QAction *actionSave    = new QAction(QStringLiteral("패키지 저장"), this);
	actionSave->setIconText(QStringLiteral("패키지 저장"));

	QAction *actionRemove = new QAction(QStringLiteral("패키지 삭제"), this);
	actionRemove->setIconText(QStringLiteral("패키지 삭제"));

	QAction *actionExtract = new QAction(QStringLiteral("모델 추출"), this);
	actionExtract->setIconText(QStringLiteral("모델 추출"));

	QAction *actionExit    = new QAction(QStringLiteral("끝내기"), this);	
	actionExit->setIconText(QStringLiteral("끝내기"));
	
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

	QMenu *menuFile = menuBar()->addMenu(QStringLiteral("파일"));
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
