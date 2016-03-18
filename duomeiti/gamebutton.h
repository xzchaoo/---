#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H
#include "gameobject.h"
#include <QPixmap>

//右下角的按钮
class GameButton : public GameObject{
	Q_OBJECT
public:
	explicit GameButton(QRectF boundRect,const QPixmap& pix,QGraphicsItem *parent = 0);
private:
	QPixmap m_pixmap;
signals:
	void click();
public slots:
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
};

#endif // GAMEBUTTON_H
