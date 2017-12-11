#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget_explorer.h"
#include "widget_editor.h"
#include "widget_info.h"
#include "widget_adjustbar.h"
#include "design.h"
#include "model.h"
#include "db_manager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void resize();
	void initialize();	

	public slots:
	void onAdd();
	void onOpen();
	void onSave();
	void onExtract();
	void onRemove();
	void onAdjust(QMouseEvent*);
	void onStatusChanged();

protected:
	void resizeEvent(QResizeEvent* event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

private:
	Design* d;
	ViewModel* m;
	DBManager* db;
    Ui::MainWindow *ui;
	bool m_initialized = false;
	
	QWidget* frameExplorer;
	QWidget* frameVAdjustbar;
	QWidget* frameInfo;
	QWidget* frameEditor;

	WidgetExplorer* widgetExplorer;
	WidgetInfo* widgetInfo;
	WidgetEditor* widgetEditor;
	WidgetAdjustbar* widgetVAdjustbar;
};

#endif // MAINWINDOW_H
