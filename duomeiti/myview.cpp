#include "myview.h"
#include "layer.h"
#include "gameicon.h"
#include "gameiconmask.h"
#include "gameconfig.h"
#include <QMouseEvent>

MyView::MyView(QGraphicsScene* s,QWidget* parent):QGraphicsView(s,parent){
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	GameConfig* gc=GameConfig::getInstance ();
	setBackgroundBrush (QPixmap(gc->gets ("/View/background")));
	int r=gc->getInt ("/View/r",155);
	int g=gc->getInt ("/View/g",155);
	int b=gc->getInt ("/View/b",155);
	int a=gc->getInt ("/View/a",65);
	setForegroundBrush (QColor(r,g,b,a));
	setCacheMode(QGraphicsView::CacheBackground);
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

//最后记得移除
void MyView::saveSettings(){
	/*QFile f("c:/1.txt");
	f.open (QIODevice::WriteOnly);
	QTextStream o(&f);
	QList<QGraphicsItem*> list=scene ()->items ();
	QList<QGraphicsItem*>::iterator it;
	for(it=list.begin ();it!=list.end ();++it){
		Layer* lay=(Layer*)(*it);
		QRectF r=lay->boundingRect ();
		o<<lay->pos ().x ()<<" "<<lay->pos ().y ()<<" "<<r.width ()<<" "<<r.height ()<<endl;
	}
	f.close ();*/
}


void MyView::resizeEvent(QResizeEvent* event){
	//设置缩放策略
	QGraphicsView::resizeEvent(event);
	fitInView(sceneRect(), Qt::IgnoreAspectRatio);
}


void MyView::mouseDoubleClickEvent(QMouseEvent* e){
	return;
	QGraphicsScene* s=scene ();
	if(s){
		Layer* lay=new Layer(QRectF(0,0,100,100));
		QPointF p=mapToScene (e->pos ());
		lay->setPos (p);
		s->addItem (lay);
	}
}


void MyView::mousePressEvent(QMouseEvent*e){
	QGraphicsView::mousePressEvent (e);
	//要使用dynamic_cast否则无效...
	QGraphicsItem* obj=this->itemAt (e->pos ());
	GameIconMask* r=dynamic_cast<GameIconMask*>(obj);
	if(r!=NULL){
		//qDebug()<<"点击在蒙版上了"<<endl;
	}else{
		GameIcon* gi=dynamic_cast<GameIcon*>(obj);
		if(gi==NULL||!gi->isVisible ()){
			//qDebug()<<"点在视图上"<<endl;
			emit clickOnView ();
		}else{
			//qDebug()<<"点在icon上"<<endl;
		}
	}
}
