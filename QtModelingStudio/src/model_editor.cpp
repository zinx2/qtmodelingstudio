#include "model_editor.h"

ModelEditor::ModelEditor(QWidget *parent)
{
	setRowCount(10);
	setColumnCount(5);
	setHorizontalHeaderLabels({"No", "Name", "Data Type", "List Type", "Read Only"});

	QLabel* lb = new QLabel("hahah");
	setCellWidget(0, 0, lb);		

	//QCheckBox* chb = new QCheckBox(this);
	//chb->setEnabled(false);
	////chb->setCheckable(false);
	////chb->setDisabled(true);
	//chb->setAcceptDrops(false);
	//chb->setDown(false);
	
	//setCellWidget(0, 1, chb);

	QPushButton* btn = new QPushButton(this);
	setCellWidget(0, 2, btn);

	QComboBox* cb = new QComboBox(this);
	setCellWidget(0, 3, cb);

	connect(this, SIGNAL(cellEntered(int, int)), this, SLOT(onCellEntered(int, int)));
	connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(onCellClicked(int, int)));
	connect(this, SIGNAL(cellChanged(int, int)), this, SLOT(onCellChanged(int, int)));
	/*connect(this, SIGNAL(cellPressed(int, int)), this, SLOT(onCellPressed(int, int)));
	connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(onCellDoubleClicked(int, int)));
	connect(this, SIGNAL(cellActivated(int, int)), this, SLOT(onCellActivated(int, int)));
	connect(this, SIGNAL(cellChanged(int, int)), this, SLOT(onCellChanged(int, int)));*/
	//connect(this, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(onItemClicked(QTableWidgetItem *)));
}

void ModelEditor::onCellEntered(int row, int column)
{
	qDebug() << "CELL ENTERED.";
}
void ModelEditor::onCellClicked(int row, int column)
{
	qDebug() << "CELL CLICKED.";
}
void ModelEditor::onCellPressed(int row, int column)
{
	qDebug() << "CELL PRESSED.";
}
void ModelEditor::onCellDoubleClicked(int row, int column)
{
	qDebug() << "CELL DOUBLE CLICKED.";
}
void ModelEditor::onCellActivated(int row, int column)
{
	qDebug() << "CELL ACTIVATED.";
}
void ModelEditor::onCellChanged(int row, int column)
{
	qDebug() << "CELL CHANGED.";
}
void ModelEditor::onItemClicked(QTableWidgetItem * item)
{
	qDebug() << "ITEM CLICKED.";
}

