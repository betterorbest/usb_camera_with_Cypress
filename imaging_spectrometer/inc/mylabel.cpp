#include "mylabel.h"
#include "qevent.h"
MyLabel::MyLabel(QWidget* parent)
	:QLabel(parent)
{

}

void MyLabel::mouseDoubleClickEvent(QMouseEvent* e)
{
	emit currentPos(e->x(), e->y());
}