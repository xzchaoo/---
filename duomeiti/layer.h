#ifndef LAYER_H
#define LAYER_H
#include "gameobject.h"
#include <QGraphicsItem>


class Layer :public GameObject{
	Q_OBJECT
public:
	Layer( QRectF boundRect, QGraphicsItem* parent=0);
public:
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	virtual void draw(QPainter* painter){}
};

#endif // LAYER_H
