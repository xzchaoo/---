#include "openingshow.h"
#include "Animation.h"
#include "animationgroup.h"
#include "spiralfunction.h"
#include "gameicon.h"
#include "gamepanel.h"
#include "inversespiralfunction.h"
#include "gameconfig.h"

OpeningShow::OpeningShow(int id){
	if(id==0)
		id=qrand()%5+1;
	m_id=id;
}

void OpeningShow::process(QRectF r, IconManager* iconManager){
	this->r=r;
	this->iconManager=iconManager;
	switch(m_id){
	case 1:
		effect1 ();
		break;
	case 2:
		effect2 ();
		break;
	case 3:
		effect3 ();
		break;
	case 4:
		effect4();
		break;
	case 5:
		effect5 ();
		break;
	}
}

void OpeningShow::effect1(){
	AnimationGroup* g=new AnimationGroup(1);
	QList<GameIcon*>& list=*iconManager->gameIconList ();
	int row=iconManager->rowAndCol ().x ();
	int col=iconManager->rowAndCol ().y ();
	qreal width=r.width ()/row;
	qreal height=r.height ()/col;
	QSizeF size(width,height);
	iconManager->setIconSize (size);
	int base=GameConfig::getInstance ()->getInt ("/OpeningShow/base",100);
	int interval=GameConfig::getInstance ()->getInt ("/OpeningShow/interval",10);
	for(int i=1;i<row-1;++i){
		for(int j=1;j<col-1;++j){
			qreal ox=width*i+width/2;
			qreal oy=height*j+height/2;
			GameIcon* gi=list[iconManager->getIndex (i,j)];
			gi->setBoundRect (QRectF(-width/2,-height/2,width,height));
			Animation* a=new Animation(gi,"pos");
			a->setValue (QPointF(ox,300-height/2),QPointF(ox,oy),base+(i*(col-2)+j)*interval,QEasingCurve::InOutCubic)->addTo (g);
			a->setFunction (new SpiralFunction(QPointF(ox,height*i)));
		}
	}
	g->start ();
}

void OpeningShow::effect2(){
	AnimationGroup* g=new AnimationGroup(1);
	
	QPointF centerPoint=QPointF(r.width ()/2,r.height ()/2);
	
	QList<GameIcon*>& list=*iconManager->gameIconList ();
	int row=iconManager->rowAndCol ().x ();
	int col=iconManager->rowAndCol ().y ();
	qreal width=r.width ()/row;
	qreal height=r.height ()/col;
	QSizeF size(width,height);
	iconManager->setIconSize (size);
	int base=GameConfig::getInstance ()->getInt ("/OpeningShow/base",100);
	int interval=GameConfig::getInstance ()->getInt ("/OpeningShow/interval",10);
	QRectF boundRect(-width/2,-height/2,width,height);
	for(int i=1;i<row-1;++i){
		for(int j=1;j<col-1;++j){
			qreal ox=width*i+width/2;
			qreal oy=height*j+height/2;
			GameIcon* gi=list[iconManager->getIndex (i,j)];
			gi->setBoundRect(boundRect);
			Animation* a=new Animation(gi,"pos");
			a->setValue (centerPoint,QPointF(ox,oy),base+(i*(col-2)+j)*interval,QEasingCurve::InOutCubic)->addTo (g);
			a->setFunction (new SpiralFunction(centerPoint));
		}
	}
	g->start ();
}

void OpeningShow::effect3(){
	AnimationGroup* g=new AnimationGroup(1);
	
	QPointF centerPoint=QPointF(r.width ()/2,r.height ()/2);
	
	QList<GameIcon*>& list=*iconManager->gameIconList ();
	int row=iconManager->rowAndCol ().x ();
	int col=iconManager->rowAndCol ().y ();
	qreal width=r.width ()/row;
	qreal height=r.height ()/col;
	QSizeF size(width,height);
	iconManager->setIconSize (size);
	int base=GameConfig::getInstance ()->getInt ("/OpeningShow/base",100);
	int interval=GameConfig::getInstance ()->getInt ("/OpeningShow/interval",10);
	QRectF boundRect(-width/2,-height/2,width,height);
	for(int i=1;i<row-1;++i){
		for(int j=1;j<col-1;++j){
			qreal ox=width*i+width/2;
			qreal oy=height*j+height/2;
			GameIcon* gi=list[iconManager->getIndex (i,j)];
			gi->setBoundRect(boundRect);
			Animation* a=new Animation(gi,"pos");
			a->setValue (centerPoint,QPointF(ox,oy),base+(i*(col-2)+j)*interval,QEasingCurve::InOutCubic)->addTo (g);
			a->setFunction (new InverseSpiralFunction(centerPoint,QPointF(ox,oy)));
		}
	}
	g->start ();
}

void OpeningShow::effect4(){
	AnimationGroup* g=new AnimationGroup(1);
	QPointF centerPoint=QPointF(r.width ()/2,r.height ()/2);
	QList<GameIcon*>& list=*iconManager->gameIconList ();
	int row=iconManager->rowAndCol ().x ();
	int col=iconManager->rowAndCol ().y ();
	qreal width=r.width ()/row;
	qreal height=r.height ()/col;
	QSizeF size(width,height);
	iconManager->setIconSize (size);
	int base=GameConfig::getInstance ()->getInt ("/OpeningShow/base",100);
	int interval=GameConfig::getInstance ()->getInt ("/OpeningShow/interval",10);
	QRectF boundRect(-width/2,-height/2,width,height);
	for(int i=1;i<row-1;++i){
		for(int j=1;j<col-1;++j){
			qreal ox=width*i+width/2;
			qreal oy=height*j+height/2;
			QPoint dest(ox,oy);
			GameIcon* gi=list[iconManager->getIndex (i,j)];
			gi->setBoundRect(boundRect);
			gi->setPos (centerPoint);
			Animation* a=new Animation(gi,"pos");
			a->setValue (centerPoint,dest,base+(i*(col-2)+j)*interval,QEasingCurve::InOutCubic)->addTo (g);
			a->setFunction (new Function4(centerPoint,dest));
		}
	}
	g->start ();
}

void OpeningShow::effect5(){
	AnimationGroup* g=new AnimationGroup(1);
	QList<GameIcon*>& list=*iconManager->gameIconList ();
	int row=iconManager->rowAndCol ().x ();
	int col=iconManager->rowAndCol ().y ();
	qreal width=r.width ()/row;
	qreal height=r.height ()/col;
	QSizeF size(width,height);
	iconManager->setIconSize (size);
	int base=GameConfig::getInstance ()->getInt ("/OpeningShow/base",100);
	int interval=GameConfig::getInstance ()->getInt ("/OpeningShow/interval",10);
	QRectF boundRect(-width/2,-height/2,width,height);
	
	for(int i=1;i<row-1;++i){
		QPointF start(width*i+height/2,height*col);
		for(int j=1;j<col-1;++j){
			qreal ox=width*i+width/2;
			qreal oy=height*j+height/2;
			QPoint dest(ox,oy);
			GameIcon* gi=list[iconManager->getIndex (i,j)];
			gi->setBoundRect(boundRect);
			gi->setPos (start);
			Animation* a=new Animation(gi,"pos");
			a->setValue (start,dest,base+(i*(col-2)+j)*interval,QEasingCurve::OutBounce)->addTo (g);
		}
	}
	
	g->start ();
}


static qreal M_TWO_PI=M_PI*2;

Function4::Function4(const QPointF& centerPoint, const QPointF& end, QObject* parent):AnimationFunction(true,parent){
	m_centerPoint=centerPoint;
	m_distance=(centerPoint.x()-end.x ())*(centerPoint.x ()-end.x ())+(centerPoint.y ()-end.y ())*(centerPoint.y ()-end.y ());
	m_distance=qSqrt (m_distance);
	m_alpha=qAtan2 (end.y ()-centerPoint.y (),end.x ()-centerPoint.x ());
}

QVariant Function4::process(qreal t){
	qreal r=m_distance*(t);
	qreal x=r*qCos(m_alpha+M_TWO_PI*t);
	qreal y=r*qSin(m_alpha+M_TWO_PI*t);
	return QPointF(x,y)+m_centerPoint;
}

bool Function4::canHandle(const QByteArray& propertyName) const{
	return propertyName=="pos";
}

