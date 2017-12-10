#pragma once
#include <QListWidget>
#include "item_model.h"

class ListWidget : QListWidget {
	Q_OBJECT
public:
	explicit ListWidget(QWidget *parent = Q_NULLPTR);
	~ListWidget();
protected:
	void dropEvent(QDropEvent *e) override;
	void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
	void mouseDoubleClickEvent(QMouseEvent *e);
	void refresh();
	void keyPressEvent(QKeyEvent *e);

private:
	ListModel* model;
	int selectedRow;	

};
