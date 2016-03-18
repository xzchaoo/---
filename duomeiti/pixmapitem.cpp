#include "pixmapitem.h"
#include <QPainter>
#include <QDebug>

PixmapItem::PixmapItem(const QPixmap& pix, QRectF boundRect, QGraphicsItem* parent) :
	GameIconMask(boundRect,parent),m_pixmap(pix){
	m_shapeType=Rectangle;
}

void PixmapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* ){
	//将图形缩放到对应的矩形里
	painter->drawPixmap (m_boundRect,m_pixmap,m_pixmap.rect ());
}

void PixmapItem::setShapeType(PixmapItem::Type t){
	m_shapeType=t;
}


QPainterPath PixmapItem::shape() const{
	QPainterPath path;
	if(m_shapeType==Rectangle)
		path.addRect (m_boundRect);
	else{
		path.addEllipse (m_boundRect);
	}return path;
}

