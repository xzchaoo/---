#include "chainitem.h"

#include <QPainterPath>
#include <Qpainter>
#include <QStyleOptionGraphicsItem>
#include <QPainterPath>
#include <QtMath>
#include "gameconfig.h"

ChainItem::ChainItem(QRectF boundRect, QGraphicsItem *parent) :
	GameObject(boundRect,parent){
	GameConfig* gc=GameConfig::getInstance ();
	int r=gc->getInt ("/ChainItem/r",0);
	int g=gc->getInt ("/ChainItem/g",0);
	int b=gc->getInt ("/ChainItem/b",0);
	int a=gc->getInt ("/ChainItem/a",0);
	m_clr=QColor(r,g,b,a);
}

void ChainItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
	painter->fillRect (m_boundRect,m_clr);
}
