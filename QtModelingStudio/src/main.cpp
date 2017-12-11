#include "mainwindow.h"
#include <QApplication>


#include "widget_explorer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	//WidgetExplorer* widgetExplorer = new WidgetExplorer;
	//widgetExplorer->show();

    return a.exec();
}
