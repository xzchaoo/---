#include "bombtooleffect.h"
#include "iconmanager.h"
#include <QList>
#include "gameicon.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "gameiconmask.h"
#include <QPen>
#include <QBrush>
#include <QGraphicsEllipseItem>
#include "Animation.h"
#include "animationgroup.h"
#include <QGraphicsItem>
#include "gameiconeffectfactory.h"
#include "pixmapitem.h"
#include "pngsitem.h"
#include "gameconfig.h"

BombToolEffect::BombToolEffect(QObject *parent) :
	ToolEffect(parent){
}



void BombToolEffect::process(IconManager* iconManager){
	
	QList<GameIcon*>& list=*iconManager->gameIconList ();
	QList<GameIcon*> remain;
	for(int i=0;i<list.size ();++i){
		if(list[i]==NULL||list[i]->isFreezing ())
			continue;
		remain.push_back (list[i]);
	}
	GameIcon* gi=remain[qrand()%remain.size ()];
	
	
	PngsItem* pi=PngsItem::createPngsItem (gi->scenePos (),gi->scene ());
	
	int minw=m_gc->getInt ("/BombToolEffect/minWidth",3);
	int maxw=m_gc->getInt ("/BombToolEffect/maxWidth",8);
	
	int minh=m_gc->getInt ("/BombToolEffect/minHeight",3);
	int maxh=m_gc->getInt ("/BombToolEffect/maxHeight",8);
	
	maxw-=minw;
	maxw=maxw<=0?1:maxw;
	maxh-=minh;
	maxh=maxh<=0?1:maxh;
	
	qreal width=(minw+qrand()%maxw)*gi->boundingRect ().width ();
	qreal height=(minh+qrand()%maxh)*gi->boundingRect ().height ();
	
	QGraphicsEllipseItem* m=gi->scene ()->addEllipse (gi->boundingRect ()+QMarginsF(width/2,height/2,width/2,height/2));
	
	m->setPos (gi->scenePos ());
	
	m_musicPlayer->play (m_gc->gets("/toolmusic/path")+"/bomb.mp3");
	
	Animation* a;
	
	a=new Animation(pi,"curIndex");
	a->setValue (0,pi->size (),m_gc->getInt ("/BombToolEffect/duration",1000))->deleteTargetWhenFinished ()->start ();
	
	QList<QGraphicsItem*> colliding=gi->scene ()->items (m->sceneBoundingRect (),Qt::ContainsItemShape);
	int count=0;
	for(int i=0;i<colliding.size ();++i){
		GameIcon* gi=dynamic_cast<GameIcon*>(colliding[i]);
		if(gi==NULL||gi->isFreezing ())
			continue;
		GameIconEffectFactory::addVanishEffect (gi);
		iconManager->setToFreezing (gi);
		++count;
	}
	delete m;
	m_toolEffectScore=count*m_gc->getInt ("/BombToolEffect/score",3);
}
