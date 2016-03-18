#include "iconhinttooleffect.h"
#include "iconmanager.h"
#include <QList>
#include "gameicon.h"
#include <QDebug>
#include <QTextStream>
#include "gameconfig.h"

IconHintToolEffect::IconHintToolEffect(QObject *parent) :
	ToolEffect(parent)
{
}

void IconHintToolEffect::process(IconManager* iconManager){
	QList<GameIcon*>& list=*iconManager->gameIconList ();
	QList<int>& iconType=*iconManager->gameIconTypeList ();
	
	int row=iconManager->rowAndCol ().x ()-2;
	int col=iconManager->rowAndCol ().y ()-2;
	bool ok;
	int count=m_gc->get ("/IconHintToolEffect/count").toInt (&ok);
	count=ok?count:100;
	for(int i=0;i<count;++i){
		int x1=qrand()%row+1;
		int y1=qrand()%col+1;
		int x2=qrand()%row+1;
		int y2=qrand()%col+1;
		
		int p1=iconManager->getIndex (x1,y1);
		int p2=iconManager->getIndex (x2,y2);
		
		GameIcon* g1=list[p1];
		GameIcon* g2=list[p2];
		list[p1]=g2;
		list[p2]=g1;
		
		int t=iconType[p1];
		iconType[p1]=iconType[p2];
		iconType[p2]=t;
		
		
		QPointF pf1=iconManager->getCenterPoint (g1);
		g1->setPos (iconManager->getCenterPoint (g2));
		g2->setPos (pf1);
		
		QPoint p=g1->rowAndCol ();
		g1->setRowAndCol (g2->rowAndCol ());
		g2->setRowAndCol (p);
		
	}
	m_toolEffectScore=m_gc->get ("/IconHintToolEffect/score").toInt (&ok);
	m_toolEffectScore=ok?m_toolEffectScore:0;
}
