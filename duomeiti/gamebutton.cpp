#include "gamebutton.h"
#include <QPainter>
#include "gametoolbuttoneffectfactory.h"

GameButton::GameButton(QRectF boundRect, const QPixmap& pix, QGraphicsItem* parent):GameObject(boundRect,parent){
	m_pixmap=pix;
}


void GameButton::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
	painter->drawPixmap (m_boundRect,m_pixmap,m_pixmap.rect ());
}


void GameButton::mousePressEvent(QGraphicsSceneMouseEvent* event){
	GameObject::mousePressEvent (event);
	GameToolButtonEffectFactory::addMousePressEffect (this);
	emit click ();
}


void GameButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
	GameObject::hoverEnterEvent (event);
	GameToolButtonEffectFactory::addHoverEnterEffect (this);
}

void GameButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
	GameObject::hoverLeaveEvent (event);
	GameToolButtonEffectFactory::addHoverLeaveEffect (this);
}
