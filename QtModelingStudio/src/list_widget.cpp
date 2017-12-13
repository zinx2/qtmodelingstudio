#include "list_widget.h"

#include <QDebug>
#include <QDropEvent>
#include <QDragMoveEvent>
#include <QMimeData>

#include "list_widget_item.h"
ListWidget::ListWidget(QWidget *parent)
{
	model = ListModel::instance();
	QList<Object*> q = {
		new Object(0 , -1, Object::PACKAGE, "Exp"),
		new Object(1 , 0 , Object::CLASS, "Class1"),
		new Object(2 , 1 , Object::PROPERTY, "pro1_1", "int"),
		new Object(3 , 1 , Object::PROPERTY, "pro2_1", "QString"),
		new Object(4 , 1 , Object::PROPERTY, "pro3_1", "bool"),
		new Object(5 , 1 , Object::PROPERTY, "pro4_1", "float"),
		new Object(6 , 0 , Object::CLASS, "Class2"),
		new Object(7 , 6 , Object::PROPERTY,"pro1_2", "int"),
		new Object(8 , 6 , Object::PROPERTY,"pro2_2", "QString"),
		new Object(9 , 6 , Object::PROPERTY,"pro3_2", "bool"),
		new Object(10, 0 , Object::CLASS, "Class3"),
		new Object(11, 10, Object::PROPERTY, "pro1_3", "int"),
		new Object(12, 10, Object::PROPERTY, "pro2_3", "QString"),
		new Object(13, 10, Object::PROPERTY, "pro3_3", "bool"),
		new Object(14, 10, Object::PROPERTY, "pro4_3", "float"),
		new Object(15, 10, Object::PROPERTY, "pro5_3", "bool"),
		new Object(16 , -1, Object::PACKAGE, "Exp2"),
		new Object(17 , 16 , Object::CLASS, "Class1"),
		new Object(18 , 17 , Object::PROPERTY, "pro1_21", "int"),
		new Object(19 , 17 , Object::PROPERTY, "pro2_21", "QString"),
		new Object(20 , 17 , Object::PROPERTY, "pro3_21", "bool"),
		new Object(21 , 17 , Object::PROPERTY, "pro4_21", "float"),
		new Object(22 , 16 , Object::CLASS, "Class2"),
		new Object(23 , 22 , Object::PROPERTY,"pro1_22", "int"),
		new Object(24 , 22 , Object::PROPERTY,"pro2_22", "QString"),
		new Object(25 , 22 , Object::PROPERTY,"pro3_22", "bool"),
		new Object(26, 16 , Object::CLASS, "Class3"),
		new Object(27, 26, Object::PROPERTY, "pro1_23", "int"),
		new Object(28, 26, Object::PROPERTY, "pro2_23", "QString"),
		new Object(29, 26, Object::PROPERTY, "pro3_23", "bool"),
		new Object(30, 26, Object::PROPERTY, "pro4_23", "float"),
		new Object(31, 26, Object::PROPERTY, "pro5_23", "bool"),
	};
	for (Object* p : q) {
		model->append(p);
	}

	this->setFixedHeight(800);
	this->setStyleSheet("background-color:orange; color:white");

	this->setDragEnabled(true);
	this->setAcceptDrops(true);
	this->setDragDropMode(QAbstractItemView::InternalMove);
	refresh();
	show();
}
void ListWidget::refresh()
{
	this->clear();
	for (int i = 0; i < model->size(); i++) {
		Object* p = qobject_cast<Object*>(model->objs()[i]);
		ListWidgetItem* item = new ListWidgetItem(p->name());
		item->setIndex(i);
		item->setIcon(QIcon("./img/file.png"));
		this->addItem(item);		
	}	

	for (int i = 0; i < model->size(); i++) {
		Object* p = qobject_cast<Object*>(model->objs()[i]);
		this->setRowHidden(i, p->hidden());
	}
}
ListWidget::~ListWidget()
{

}
void ListWidget::dropEvent(QDropEvent *e)
{
	QListWidgetItem* item = this->itemAt(e->pos());
	ListWidgetItem* m = dynamic_cast<ListWidgetItem*>(item);
	QModelIndexList indexes = this->selectedIndexes();
	model->moveClass(indexes[0].row(), m->index());
	refresh();
}

void ListWidget::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	
	QModelIndexList mList = selected.indexes();
	if (mList.length() > 0)
	{
		//int selectedRow = mList[0].row();
		//qDebug() << "SELECTED : " << selectedRow;
	}		
}

void ListWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
	qDebug() << "DOUBLE PRESSED MOUSE";
	QListWidgetItem* item = this->itemAt(e->pos());
	ListWidgetItem* m = dynamic_cast<ListWidgetItem*>(item); 

	int row = m->index();
	Object* p = qobject_cast<Object*>(model->objs()[row]);
	if (!p->extended())
		model->extend(row);
	else
		model->fold(row);

	refresh();
	this->setCurrentRow(row);
}

void ListWidget::keyPressEvent(QKeyEvent *e)
{	
	int key = e->key();
	switch (key) {
	case Qt::Key_Up: {
		if (this->selectedIndexes().size() > 0) {
			int row = this->currentRow();
			if (row > 0) {
				for (int i = row - 1; i > -1; i--) {
					Object* obj = qobject_cast<Object*>(model->objs()[i]);
					if (!obj->hidden()) {
						this->setCurrentRow(i);
						break;
					}
				}
			}
		}
		else this->setCurrentRow(0);
		break;
	}
	case Qt::Key_Down: {
		if (this->selectedIndexes().size() > 0) {
			int row = this->currentRow();
			if (row < this->count() - 1) {				
				for (int i = row + 1; i < this->count(); i++) {
					Object* obj = qobject_cast<Object*>(model->objs()[i]);
					if (!obj->hidden()) {
						this->setCurrentRow(i);
						break;
					}
				}
			}
		}
		else this->setCurrentRow(0);
		
		break;
	}
	case Qt::Key_Right: {

		int row = this->currentRow();
		Object* p = qobject_cast<Object*>(model->objs()[row]);
		if (!p->extended())
			model->extend(row);

		refresh();
		this->setCurrentRow(row);
		break;
	}
	case Qt::Key_Left: {
		int row = this->currentRow();
		Object* p = qobject_cast<Object*>(model->objs()[row]);
		if (p->extended())
			model->fold(row);

		refresh();
		this->setCurrentRow(row);
		break;
	}
	case Qt::Key_Return | Qt::Key_Return: {
		int row = this->currentRow();
		qDebug() << "SELECTED ROW: " << row;
		break;
	}
	}
	update();
}