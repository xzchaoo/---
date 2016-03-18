#include "layer.h"

#include <QGraphicsItemGroup>
#include <QObject>
#include "gameconfig.h"
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

Layer::Layer(QRectF boundRect, QGraphicsItem* parent):GameObject(boundRect,parent){
}


void Layer::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* ){
	QPainter& g=*painter;
	QRectF r=m_boundRect;
	int x=0;
	int y=0;
	int w=r.width ()-14;
	int h=r.height ()-14;
	QPixmap p(m_gc->gets ("/Layer/window"));
	//左上角
	g.drawPixmap (x,y,7,7,p,0,0,7,7);
	//中上线
	g.drawPixmap (x+7,y,w,7,p,7,0,50,7);
	//右上角
	g.drawPixmap (x+7+w,y,7,7,p,57,0,7,7);
	//右中线
	g.drawPixmap (x+7+w,y+7,7,h,p,57,7,7,50);
	//右下角
	g.drawPixmap (x+7+w,y+7+h,7,7,p,57,57,7,7);
	//中下线
	g.drawPixmap (x+7,y+7+h,w,7,p,7,57,50,7);
	//左下角
	g.drawPixmap (x,y+7+h,7,7,p,0,57,7,7);
	//左中线
	g.drawPixmap (x,y+7,7,h,p,0,7,7,50);
	//画中间部分
	g.drawPixmap (x+7,y+7,w,h,p,7,7,50,50);
	draw(painter);
}
