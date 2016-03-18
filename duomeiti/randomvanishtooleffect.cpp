#include "randomvanishtooleffect.h"
#include <QList>
#include "gameicon.h"
#include "iconmanager.h"

RandomVanishToolEffect::RandomVanishToolEffect(int base, QObject *parent) :
	ToolEffect(parent){
	if(base<2)
		base=2;
	m_base=base;
}


void RandomVanishToolEffect::process(IconManager* iconManager){
	QList<GameIcon*>& list=*iconManager->gameIconList ();
	int count=0;
	for(int i=0;i<list.size ();++i){
		GameIcon* gi=list[i];
		if(gi==NULL||gi->isFreezing ())
			continue;
		//几率消灭
		if(qrand()%m_base==0){
			iconManager->setToFreezing (gi);
			++count;
		}
	}
	//计算得分
	m_toolEffectScore=count*(qrand()%1000+100);
}
