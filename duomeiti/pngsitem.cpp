#include "pngsitem.h"
#include "QPainter"
#include <QDebug>
#include <QGraphicsScene>
#include <qsettings>
#include "gameconfig.h"

PngsItem::PngsItem(int id,QRectF boundRect, QGraphicsItem* parent):GameObject(boundRect,parent){
	m_curIndex=0;
	m_id=id;
	m_gc=GameConfig::getInstance ();
	m_imageLoader=m_gc->pngsLoader (m_id);
	m_boundRect=m_imageLoader->get (0).rect ();
}

PngsItem*PngsItem::createPngsItem(QPointF pos, QGraphicsScene* s){
	GameConfig* gc=GameConfig::getInstance ();
	static int id=0;
	if(++id==gc->getInt ("/PngsItem/count",0)+1){
		id=1;
	}
	QString dir=gc->gets ("/PngsItem/path")+"/"+QString::number (id);
	PngsItem* pi=new PngsItem(id,QRectF(0,0,0,0),0);
	
	QSettings set(dir+"/config.txt",QSettings::IniFormat);
	bool ok;
	int dx=set.value ("dx",0).toInt (&ok);
	dx=ok?dx:0;
	int dy=set.value ("dy",0).toInt (&ok);
	dy=ok?dy:0;
	s->addItem (pi);
	pi->setPos (pos-QPointF(dx,dy));
	return pi;
}	

int PngsItem::curIndex() const{
	return m_curIndex;
}

void PngsItem::setCurIndex(int arg){
	if(arg>=m_imageLoader->size ())
		arg=m_imageLoader->size ()-1;
	m_curIndex = arg;
	update();
}


void PngsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* ){
	QPixmap p=m_imageLoader->get (m_curIndex);
	painter->drawPixmap (m_boundRect,p,p.rect ());
	//qDebug()<<m_curIndex<<" "<<m_imageLoader->size ()<<endl;
}

int PngsItem::size() const{
	return m_imageLoader->size ();
}
