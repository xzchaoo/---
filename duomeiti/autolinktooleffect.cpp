#include "autolinktooleffect.h"
#include "linkservice.h"
#include "iconmanager.h"
#include <QList>
#include "gameicon.h"
#include "gameconfig.h"


AutoLinkToolEffect::AutoLinkToolEffect(QObject *parent) :
	ToolEffect(parent)
{
}


void AutoLinkToolEffect::process(IconManager* iconManager){
	if(!iconManager->running ())
		return;
	LinkService* linkService=iconManager->linkService ();
	QList<int>& gameIconTypeList=*iconManager->gameIconTypeList ();
	QList<GameIcon*> gameIconList=*iconManager->gameIconList ();
	
	int row=iconManager->rowAndCol ().x ();
	int col=iconManager->rowAndCol ().y ();
	int stepLimit=iconManager->stepLimit ();
	
	//自动连线几对
	int count=m_gc->getInt ("/AutoLinkToolEffect/count",1);
	int score=m_gc->getInt ("/AutoLinkToolEffect/score",1);
	for(int i=1;i<row-1;++i)
		for(int j=1;j<col-1;++j){
			int index=iconManager->getIndex (i,j);
			if(gameIconTypeList[index]==-1)
				continue;
			QList<Point> list=linkService->findAllByStartPoint (Point(i,j),stepLimit,1);
			//只找count次
			if(list.size ()){
				gameIconList[index]->imitateIconClicked ();
				gameIconList[iconManager->getIndex (list[0])]->imitateIconClicked ();
				//额外得分
				m_toolEffectScore+=score;
				if(--count<=0){
					return;
				}
			}
		}
}
