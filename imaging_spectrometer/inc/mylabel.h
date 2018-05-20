#ifndef MYLABEL_H
#define MYLABEL_H

#include <QtWidgets/QLabel>

class MyLabel : public QLabel
{
	Q_OBJECT
public:
	MyLabel(QWidget* parent = 0);

protected:
	void mouseDoubleClickEvent(QMouseEvent* e);

signals:
	void currentPos(int x, int y);
};

#endif