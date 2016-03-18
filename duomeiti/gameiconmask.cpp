#include "gameiconmask.h"
#include <QPainter>

GameIconMask::GameIconMask(QGraphicsItem* parent):GameObject(parent==0?QRectF(0,0,0,0):parent->boundingRect (),parent){}

GameIconMask::GameIconMask(QRectF boundRect, QGraphicsItem *parent) :
	GameObject(boundRect,parent){
}

QBrush GameIconMask::brush() const{
	return m_brush;
}

void GameIconMask::setBrush(QBrush arg){
	m_brush = arg;
}


void GameIconMask::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
	//现在只是简单的画出矩形而已
	painter->fillRect (m_boundRect,m_brush);
}
