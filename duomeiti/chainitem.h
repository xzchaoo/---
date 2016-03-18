#ifndef CHAINITEM_H
#define CHAINITEM_H

#include "gameobject.h"
#include <QSizeF>

//表示连接两个图标时出现的阴影
//本来想做成锁链效果 不过还没有实现
class ChainItem : public GameObject{
	Q_OBJECT
public:
	explicit ChainItem(QRectF m_boundRect, QGraphicsItem *parent=0);
	//画自己
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
private:
	//阴影的颜色 默认是黑色
	QColor m_clr;
};

#endif // CHAINITEM_H
