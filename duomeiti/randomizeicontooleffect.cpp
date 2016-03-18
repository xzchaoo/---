#include "randomizeicontooleffect.h"
#include "iconmanager.h"
#include "gameicon.h"
#include <QList>
#include <QDebug>
#include "animationgroup.h"
#include "Animation.h"
#include "inversespiralfunction.h"
#include "spiralfunction.h"
#include "gameconfig.h"

RandomizeIconToolEffect::RandomizeIconToolEffect(QObject *parent) :
	ToolEffect(parent){
}


//TODO
void RandomizeIconToolEffect::process(IconManager* iconManager){
	m_musicPlayer->play (m_gc->gets("/toolmusic/path")+"/random.wav");
	QList<GameIcon*>& list=*iconManager->gameIconList ();
	int iconTypes=m_gc->iconTypes ();
	for(int i=0;i<list.size ();++i){
		if(list[i]==NULL||list[i]->isFreezing ())
			continue;
		list[i]->setIconType (qrand()%iconTypes);
	}
	m_toolEffectScore=m_gc->getInt ("/RandomizeIconToolEffect/score",0);
}
