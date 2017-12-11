#pragma once
#include "qheader.h"
class ModelEditor : public QTableWidget
{
	Q_OBJECT
public:
	explicit ModelEditor(QWidget *parent = 0);

	public slots:
	void onCellEntered(int, int);
	void onCellClicked(int, int);
	void onCellPressed(int, int);
	void onCellDoubleClicked(int, int);
	void onCellActivated(int, int);
	void onCellChanged(int, int);

	void onItemClicked(QTableWidgetItem *);
};