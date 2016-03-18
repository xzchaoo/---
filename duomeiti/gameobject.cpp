#include "gameobject.h"
#include "gameconfig.h"

GameObject::GameObject(QRectF boundRect, QGraphicsItem *parent) :
	QObject(),QGraphicsItem(parent)
{
	m_boundRect=boundRect;
	setAcceptHoverEvents (true);
	m_gc=GameConfig::getInstance ();
	//设置允许属性 可以考虑去掉
	//this->setFlag (QGraphicsObject::ItemIsFocusable);
	//this->setFlag (QGraphicsObject::ItemIsMovable);
	//this->setFlag (QGraphicsObject::ItemIsSelectable);
}

void GameObject::setBoundRect(QRectF boundRect){
	this->m_boundRect=boundRect;
	update ();
}


QRectF GameObject::boundingRect() const{
	return m_boundRect;
}
