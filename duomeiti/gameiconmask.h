#ifndef GAMEICONMASK_H
#define GAMEICONMASK_H

#include "gameobject.h"
#include <QBrush>
#include <QRectF>

class QGraphicsItem;

//一个mask指的是笼罩在icon上的一层
//由于QGrapphicsItem对象是笼罩在icon上的
//所以接受事件时候他们也会收到
//然后在Z顺序上他们也是位于icon之上
//这回导致view里的 click on view判断错误
//因此以后所有笼罩于icon上的东西 都继承这个类
//便于统一判断
class GameIconMask : public GameObject{
	Q_OBJECT
	Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
public:
	explicit GameIconMask(QGraphicsItem* parent);
	explicit GameIconMask(QRectF boundRect, QGraphicsItem *parent);
	QBrush brush() const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
public slots:
	void setBrush(QBrush arg);
private:
	QBrush m_brush;
};

#endif // GAMEICONMASK_H
