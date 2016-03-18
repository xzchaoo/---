#include "bladestormtooleffect.h"
#include "animationgroup.h"
#include "Animation.h"
#include "gameicon.h"
#include <QRectF>
#include "iconmanager.h"
#include "GamePanel.h"
#include "inversespiralfunction.h"
#include "spiralfunction.h"
#include "GameIconEffectFactory.h"
#include "gameconfig.h"


BladestormToolEffect::BladestormToolEffect(QObject *parent) :
	ToolEffect(parent){
}

void BladestormToolEffect::process(IconManager* iconManager){
	QList<GameIcon*>& gameIconList=*iconManager->gameIconList ();
	GamePanel* gamePanel=iconManager->gamePanel();
	QPointF centerPoint=gamePanel->boundingRect ().center ();
	
	int count=0;
	AnimationGroup* ag=new AnimationGroup(1);
	for(int i=0;i<gameIconList.size ();++i){
		GameIcon* gi=gameIconList[i];
		if(gi==NULL||gi->isFreezing ())
			continue;
		++count;
		iconManager->setToFreezing (gi);
		
		Animation* a=new Animation(gi,"pos");
		a->setValue (gi->pos (),centerPoint,1000+10*i)->setFunction (new SpiralFunction(gi->pos (),true))->addTo (ag);
		a=new Animation(gi,"rotation");
		a->setValue (qreal(0),qreal(360),1000+10*i)->addTo (ag);
		a=new Animation(gi,"boundRect");
		a->setValue (gi->boundingRect (),QRectF(0,0,0,0),1000+10*i)->addTo (ag);
		GameIconEffectFactory::addVanishEffect (gi);
		//connect(a,SIGNAL(finished()),gi,SLOT(hide()));
	}
	m_musicPlayer->play (m_gc->gets("/toolmusic/path")+"/quanmie.wav");
	ag->start();
	m_toolEffectScore=count*m_gc->getInt ("/BladestormToolEffect/score",1);
}
