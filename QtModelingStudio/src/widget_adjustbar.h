#pragma once
#include "wrapped_widget.h"
class WidgetAdjustbar : public WWidget
{
	Q_OBJECT
public:
	explicit WidgetAdjustbar(Qt::Orientation type, QWidget *parent = 0);
signals:
	void adjust(QMouseEvent *event);
protected:
	//void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	//bool event(QEvent * e);


	//void	hoverEnter(QHoverEvent * event);
	//void	hoverLeave(QHoverEvent * event);
	//void	hoverMove(QHoverEvent * event);

private:
	QVBoxLayout* mainVBox;
	QWidget* mainWidget;
	Qt::Orientation ori = Qt::Vertical;
};