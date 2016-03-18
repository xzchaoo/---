#include "tooleffect.h"
#include "gameicon.h"
#include "pixmapitem.h"
#include "Animation.h"
#include "AnimationGroup.h"
#include "iconmanager.h"
#include "gameconfig.h"

ToolEffect::ToolEffect(QObject *parent) :
	QObject(parent){
	m_toolEffectScore=0;
	m_musicPlayer=NULL;
	m_gc=GameConfig::getInstance ();
}

/*
void ToolEffect::process(IconManager* iconManager){
	QList<GameIco*>& gameIcoList=*iconManager->gameIconList ();
	for(int i=0;i<gameIcoList.size ();++i){
		GameIco* gi=gameIcoList[i];
		if(gi==NULL)
			continue;
		if(gi->iconType ()<3||gi->iconType ()==-1)
			continue;
		iconManager->setToFreezing (gi);
		QRectF boundRect=gi->boundingRect ();
		QRectF r(-boundRect.width ()/4,-boundRect.height ()/4,boundRect.width ()/2,boundRect.height ()/2);
		PixmapItem* pi=new PixmapItem(QPixmap(":/images/mxd/5.png"),r,gi);
		pi->setPos (boundRect.width ()/2,boundRect.height ()/2);
		Animation* a=new Animation(pi,"rotation");
		a->setValue(0,3600,3000)
		->newAnimation (gi,"opacity")->setValue (qreal(1),qreal(0))->startAll (Animation::DeleteWhenStopped);
		connect(a,SIGNAL(finished()),gi,SLOT(removeClickEffect()));
		m_toolEffectScore=100;
	}
}
*/


int ToolEffect::toolEffectScore() const{
	return m_toolEffectScore;
}

ToolEffect::~ToolEffect(){
}

void ToolEffect::setMusicPlayer(MusicPlayer* mp){
	m_musicPlayer=mp;
}
