#include "gameiconeffectfactory.h"
#include "gameicon.h"
#include "pixmapitem.h"
#include "Animation.h"
#include <QGraphicsColorizeEffect>
#include <QGraphicsRectItem>
#include "gameiconmask.h"
#include <QBrush>
#include <QGraphicsScene>
#include "gameconfig.h"

//注意中心点的位置
void GameIconEffectFactory::addVanishEffect(GameIcon* gi){
	if(gi==NULL)//不可能发生的
		exit(0);
	if(gi->isFreezing ()||!gi->isVisible ())
		return;
	
	GameConfig* gc=GameConfig::getInstance ();
	
	QRectF boundRect=gi->boundingRect ();
	QRectF r(-boundRect.width ()/4,-boundRect.height ()/4,boundRect.width ()/2,boundRect.height ()/2);
	
	int count=gc->getInt ("/GameIconEffectFactory/count",0);
	if(count==0)
		return;
	
	int rand=qrand()%count;
	QString path=gc->gets("/GameIconEffectFactory/addVanishEffectPixmap")+QString::number (rand)+".png";
	PixmapItem* pi=new PixmapItem(QPixmap(path),r);
	
	gi->scene ()->addItem (pi);
	pi->setPos (gi->scenePos ());//boundRect.width ()/2,boundRect.height ()/2);
	Animation* a=new Animation(pi,"rotation");
	a->deleteTargetWhenFinished ()->setValue(qreal(0),qreal(360),400)->start ();
	//这里采用这种方式 就可以避免 特效提前被删除而导致无法调用hide!
	//a->start ();
	connect(a,SIGNAL(destroyed()),gi,SLOT(hide()));
	//gi->hide ();
	//return;
}

void GameIconEffectFactory::addFocusInEffect(GameIcon* gi){
	if(gi==NULL)
		exit(0);
	if(gi->isFreezing ())
		return;
	QGraphicsColorizeEffect* ce=new QGraphicsColorizeEffect();
	Animation* a=new Animation(ce,"color");
	a->setValue (QColor(0,0,0),QColor(0x00,0x66,0xcc),400)->start ();
	gi->setGraphicsEffect (ce);
}

void GameIconEffectFactory::addFindEffect(GameIcon* gi){
	if(gi==NULL)
		exit(0);
	GameIconMask* m=new GameIconMask(gi->boundingRect (),gi);
	m->setBrush (QBrush(QColor(0xff,0x00,0xff)));
	m->setOpacity (0.5);
	gi->setBeFoundMode (true);
}

void GameIconEffectFactory::removeAllEffects(GameIcon* gi){
	exit(0);
	if(gi==NULL)
		exit(0);
	//QList<QGraphicsItem*> list=gi->childItems ();
	//删除所有字节点 gameicon的子节点都是用于产生特效的 得到焦点之后全部删掉
//	for(int i=list.size ()-1;i>=0;--i)
	//	delete list[i];
	gi->setGraphicsEffect (NULL);
}

void GameIconEffectFactory::addHoverLeaveEffect(GameIcon* gi){
	exit(0);
	if(gi->hasFocus ())
		return;
	//removeAllEffects (gi);
}

void GameIconEffectFactory::addStartPointEffect(GameIcon* gi){
	if(gi==NULL)
		exit(0);
	QGraphicsItem* fi=gi->scene ()->focusItem ();
	if(fi!=NULL)
		fi->clearFocus ();
	GameIconMask* r=new GameIconMask(gi->boundingRect (),gi);
	r->setAcceptedMouseButtons (0);
	r->setOpacity (0.5);
	r->setBrush (Qt::red);
}

void GameIconEffectFactory::addHoverEnterEffect(GameIcon* gi){
	exit(0);
	if(gi==NULL)
		exit(0);
	return;
	if(gi->hasFocus ())
		return;
	GameIconMask* r=new GameIconMask(gi->boundingRect (),gi);
	r->setAcceptedMouseButtons (0);
	r->setOpacity (0.3);
	r->setBrush (Qt::green);
}

GameIconEffectFactory::GameIconEffectFactory(QObject *parent) :
	QObject(parent){
}




//添加阴影


//AnimationGroup* ag=new AnimationGroup(0);

/*
 * QParallelAnimationGroup* g=new QParallelAnimationGroup();
QGraphicsOpacityEffect* oe=new QGraphicsOpacityEffect();
oe->setOpacity (0.65);
//oe->setOpacityMask (QPixmap(":/images/pg.png").scaled (48,48));
this->setGraphicsEffect (oe);
(new Animation(oe,"opacity"))->setValue (qreal(1),qreal(0.65),300)->addTo (g);
g->start (Animation::DeleteWhenStopped);
*/

//QGraphicsDropShadowEffect* be=new QGraphicsDropShadowEffect();
//QParallelAnimationGroup* g=new QParallelAnimationGroup();

//	  Animation* a=new Animation(be,"color");
//	a->setValue (QColor(255,255,255),QColor(0,66,255,255),1000)->addTo (ag->newP ());
//
//ag->newP ()->add (a);
//->addTo (ag->newP ());
//->
//newAnimation ("blurRadius")->setValue (qreal(0),qreal(3))->
//newAnimation ("offset")->setValue (qreal(0),qreal(10))->
//;//		addTo (g);
//ag->newP ()->add (a);
//g->start ();
//QParallelAnimationGroup* g2=new QParallelAnimationGroup();

//	Animation* a2=new Animation(be,"color");
//	a2->setValue (QColor(0,66,255,255),QColor(255,255,255,0),1000)->addTo (ag->newP ());//->addTo (ag->newP ());//->
// newAnimation ("blurRadius")->setValue (qreal(3),qreal(0))->
//  newAnimation ("offset")->setValue (qreal(10),qreal(0))->
//;//	  addTo (g2);
//ag->newP ()->add (a2);
// this->setGraphicsEffect (be);
//connect (g,SIGNAL(finished()),g2,SLOT(start()));
//sg->addAnimation (g);
//ssg->addAnimation (g2);
//ag->start ();
/*
QGraphicsBlurEffect* be=new QGraphicsBlurEffect();
be->setBlurHints (QGraphicsBlurEffect::QualityHint);
QPropertyAnimation* ani=new QPropertyAnimation(be,"blurRadius",this);
ani->setDuration (300);
ani->setStartValue (qreal(0));
ani->setEndValue (qreal(3));
ani->start (QAbstractAnimation::DeleteWhenStopped);
this->setGraphicsEffect (be);
*/
