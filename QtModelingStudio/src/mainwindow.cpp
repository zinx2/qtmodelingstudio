#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qheader.h"
#include "package_manager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);	
	d = Design::instance();
	m = ViewModel::instance();
	db = new DBManager();
	db->selectDB();
	for (Explorer* project : m->projects())
		db->modifyExtended(project->id(), 0);
	
    QAction *actionAdd     = new QAction(QStringLiteral("패키지 추가"), this);
    actionAdd->setIconText(QStringLiteral("패키지 추가"));

    QAction *actionOpen    = new QAction(QStringLiteral("패키지 열기"), this);
    actionOpen->setIconText(QStringLiteral("패키지 열기"));

    QAction *actionSave = new QAction(QStringLiteral("패키지 저장"), this);
    actionSave->setIconText(QStringLiteral("패키지 저장"));

	QAction *actionRemove = new QAction(QStringLiteral("패키지 제거"), this);
    actionRemove->setIconText(QStringLiteral("패키지 제거"));

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

	frameExplorer = ui->widget_explorer;
	frameInfo = ui->widget_info;
	frameEditor = ui->widget_editor;
	frameVAdjustbar = ui->widget_vadjustbar;
	
	d->setMenubarWidth(this->menuBar()->width()); d->setMenubarHeight(this->menuBar()->height());
	d->setToolbarWidth(toolbar->width()); d->setToolbarHeight(toolbar->height());
	d->setStatusbarWidth(statusBar()->width()); d->setStatusbarHeight(statusBar()->height());
	d->setTitleBarHeight(this->style()->pixelMetric(QStyle::PM_TitleBarHeight, 0, this));

	m->setMessage("Ready.");
	connect(this, SIGNAL(messageChanged()), qApp, SLOT(quit()));

}
void MainWindow::initialize()
{
	d->setWindowWidth(700);	d->setWindowHeight(700);
	d->setExplorerWidth(300); d->setExplorerHeight(d->windowHeight() - d->menubarHeight() - d->toolbarHeight());
	d->setBorderFixedSize(8);
	d->setInfoWidth(d->windowWidth() - d->borderFixedSize());
	d->setEditorWidth(d->windowWidth() - d->borderFixedSize()); d->setEditorHeight(d->windowHeight() - d->infoHeight());
	this->setMinimumSize(d->windowWidth(), d->windowHeight());

	frameExplorer->setGeometry(0, 0, d->explorerWidth(), d->explorerHeight());
	//frameExplorer->setStyleSheet("background-color:#ff0000");
	widgetExplorer = new WidgetExplorer(frameExplorer);
	QVBoxLayout* vBoxExplorer = new QVBoxLayout(frameExplorer);
	vBoxExplorer->setMargin(0);
	vBoxExplorer->addWidget(widgetExplorer);
	frameExplorer->setLayout(vBoxExplorer);

	frameVAdjustbar->setGeometry(d->explorerWidth(), 0, d->borderFixedSize(), d->explorerHeight());
	widgetVAdjustbar = new WidgetAdjustbar(Qt::Vertical, frameVAdjustbar);
	//widgetVAdjustbar->setStyleSheet("background-color:#0000ff");
	QVBoxLayout* vBoxVAdjust = new QVBoxLayout(frameVAdjustbar);
	vBoxVAdjust->setMargin(0);
	vBoxVAdjust->addWidget(widgetVAdjustbar);
	frameVAdjustbar->setLayout(vBoxVAdjust);

	frameInfo->setGeometry(d->explorerWidth() + d->borderFixedSize(), 0, d->infoWidth(), d->infoHeight());
	frameInfo->setStyleSheet("background-color:#003333");
	widgetInfo = new WidgetInfo(frameInfo);
	QVBoxLayout* vBoxInfo = new QVBoxLayout(frameInfo);
	vBoxInfo->setMargin(0);
	vBoxInfo->addWidget(widgetInfo);
	frameInfo->setLayout(vBoxInfo);

	frameEditor->setGeometry(d->explorerWidth() + d->borderFixedSize(), d->infoHeight(), d->editorWidth(), d->editorHeight());
	frameEditor->setStyleSheet("background-color:#006600");
	widgetEditor = new WidgetEditor(frameEditor);
	QVBoxLayout* vBoxEditor = new QVBoxLayout(frameEditor);
	vBoxEditor->setMargin(0);
	vBoxEditor->addWidget(widgetEditor);
	frameEditor->setLayout(vBoxEditor);

	qDebug() << d->menubarHeight();
	qDebug() << d->menubarWidth();
	qDebug() << d->toolbarHeight();
	qDebug() << d->toolbarWidth();

	resize();
	connect(widgetVAdjustbar, SIGNAL(adjust(QMouseEvent*)), this, SLOT(onAdjust(QMouseEvent*)));
	m_initialized = true;
}
void MainWindow::resize()
{
	int x = 0; int y = 0; int w = 0; int h = 0;
	QRect g;

	g = frameExplorer->geometry();
	x = 0;
	y = g.y();
	w = d->explorerWidth();
	h = d->windowHeight() - d->menubarHeight() - d->toolbarHeight(); d->setExplorerHeight(h);
	frameExplorer->setGeometry(x, y, w, h);
	widgetExplorer->setGeometry(0, 0, w, h);	

	g = frameVAdjustbar->geometry();
	x = g.x();
	y = g.y();
	w = d->borderFixedSize(); // geo.width();
	h = d->windowHeight() - d->menubarHeight() - d->toolbarHeight(); d->setExplorerHeight(h);
	frameVAdjustbar->setGeometry(x, y, w, h);
	widgetVAdjustbar->setGeometry(0, 0, w, h);

	g = frameInfo->geometry();
	x = g.x();
	y = g.y();
	w = d->windowWidth() - d->explorerWidth() - d->borderFixedSize(); // geo.width();
	h = d->infoHeight();
	frameInfo->setGeometry(x, y, w, h);
	widgetInfo->setGeometry(0, 0, w, h);

	g = frameEditor->geometry();
	x = g.x();
	y = g.y();
	w = d->windowWidth() - d->explorerWidth() - d->borderFixedSize(); // geo.width();
	h = d->explorerHeight() - d->infoHeight();
	frameEditor->setGeometry(x, y, w, h);
	widgetEditor->setGeometry(0, 0, w, h);
}
void MainWindow::resizeEvent(QResizeEvent* e)
{
	if (!m_initialized) {
		initialize();
		return;
	}

	QSize newSize = e->size();
	QSize oldSize = e->oldSize();
	d->setWindowWidth(newSize.width());
	d->setWindowHeight(newSize.height());

	resize();
}
void MainWindow::onAdjust(QMouseEvent* e)
{
	QRect g = frameVAdjustbar->geometry();
	int currentX = frameVAdjustbar->geometry().x();
	int movedX = e->x();

	int updatedX = currentX + movedX;
	if (d->windowWidth() - 50 > updatedX && updatedX > 50) {
		frameVAdjustbar->setGeometry(updatedX, g.y(), g.width(), g.height());

		int x = 0; int y = 0; int w = 0; int h = 0;
		x = 0; 
		y = g.y();
		w = g.width() + updatedX - d->borderFixedSize(); d->setExplorerWidth(w);
		h = g.height();
		frameExplorer->setGeometry(x, y, w, h);
		widgetExplorer->setGeometry(0, 0, w, h);

		g = frameInfo->geometry();
		x = g.x() + movedX;
		y = g.y();
		w = g.width() - movedX; d->setInfoWidth(w);
		h = g.height();
		frameInfo->setGeometry(x, y, w, h);

		g = frameEditor->geometry();
		x = g.x() + movedX;
		y = g.y();
		w = g.width() - movedX; d->setEditorWidth(w);
		h = g.height();
		frameEditor->setGeometry(x, y, w, h);
	}
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{

}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

}
void MainWindow::onAdd()
{
	qDebug() << "ADD";
	m->setMessage("Select Directory to add.");
	QString path = QFileDialog::getSaveFileName(this, "Save File...", QDir::currentPath(), "Package (*.xml)");

	/* UPDATE DATABASE. */
	QStringList temp = path.split("/");
	QString name = temp[temp.length() - 1];
	if (!db->insertDB(name, path)) {
		m->setMessage("Can't insert the data to DB.");
		return;
	}

	m->setDir(path);
	qDebug() << path;
}
void MainWindow::onOpen()
{
	qDebug() << "OPEN";
	//m->setMessage("Select Directory to open.");
	//QString path = QFileDialog::getOpenFileName(this, "Open Package File...", QDir::currentPath(), "Package (*.xml)");

	//if (path.isEmpty()) {
	//	m->setMessage("Canceled.");
	//	return;
	//}
	//m->setDir(path);
}
void MainWindow::onSave()
{
	qDebug() << "SAVE";
}
void MainWindow::onExtract()
{
	qDebug() << "EXTRACT";
	PackageManager::instance()->generate(0);
}
void MainWindow::onRemove()
{
	qDebug() << "REMOVE";
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStatusChanged()
{
	statusBar()->showMessage(m->message());
}