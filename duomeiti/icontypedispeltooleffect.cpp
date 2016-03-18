#include "icontypedispeltooleffect.h"
#include <QList>
#include "gameicon.h"
#include "pixmapitem.h"
#include "qpixmap.h"
#include "Animation.h"
#include "iconmanager.h"
#include "gameiconeffectfactory.h"
#include <QDebug>
#include "gameconfig.h"
#include "animationgroup.h"

IconTypeDispelToolEffect::IconTypeDispelToolEffect(QObject *parent) :
	ToolEffect(parent){
}


//400毫秒内旋转两圈减淡消失
void IconTypeDispelToolEffect::process(IconManager* iconManager){
	//TODO 需要获得游戏图标总类数


	QList<GameIcon*>& gameIcoList=*iconManager->gameIconList ();
	QList<bool> remain;
	int iconTypes=m_gc->iconTypes ();
	for(int i=0;i<iconTypes;++i)
		remain.push_back (false);
	
	//先跑一遍找出有剩余的类型
	for(int i=0;i<gameIcoList.size ();++i){
		GameIcon* gi=gameIcoList[i];
		if(gi==NULL||gi->isFreezing ())
			continue;
		remain[gi->iconType ()]=true;
	}
	
	QList<int> remainType;
	for(int i=0;i<remain.size ();++i)
		if(remain[i])
			remainType.push_back (i);
	//生成随机数
	int r=qrand()%remainType.size ();
	r=remainType[r];
	
	//移除剩余数量为0的
	
	//平行动画组
	
	AnimationGroup* ag=new AnimationGroup(1);
	
	//统计消灭的图标数量 加分的时候有用到
	int count=0;
	//最多消灭的图标数量
	int maxCount=m_gc->getInt ("/IconTypeDispelToolEffect/count",-1);
	if(maxCount==-1)
		maxCount=70862045;//很大的数字 表示无穷大
	
	for(int i=0;i<gameIcoList.size ()&&count<maxCount;++i){
		GameIcon* gi=gameIcoList[i];
		//跳过非法的
		if(gi==NULL||gi->isFreezing ())
			continue;
		
		if(gi->iconType ()==r){
			//GameIconEffectFactory::addVanishEffect (gi);
			iconManager->setToFreezing (gi);
			++count;
			//动画特效
			Animation* a=new Animation(gi,"rotation");
			a->setValue (qreal(0),qreal(720),400)->addTo (ag);
			a=new Animation(gi,"opacity");
			a->setValue (qreal(1),qreal(0),400)->addTo (ag);
			a=new Animation(gi,"boundRect");
			a->setValue (gi->boundingRect (),QRectF(0,0,0,0))->addTo (ag);
		}
	}
	m_musicPlayer->play (m_gc->gets("/toolmusic/path")+"/dispel.wav");
	ag->start ();
	//计算使用道具得分
	m_toolEffectScore=m_gc->getInt ("/IconTypeDispelToolEffect/score",1)*count;
}


/*
QRectF boundRect=gi->boundingRect ();
QRectF r(-boundRect.width ()/4,-boundRect.height ()/4,boundRect.width ()/2,boundRect.height ()/2);
PixmapItem* pi=new PixmapItem(QPixmap(":/images/mxd/5.png"),r,gi);
pi->setPos (boundRect.width ()/2,boundRect.height ()/2);
Animation* a=new Animation(pi,"rotation");
a->setValue(0,3600,3000)
->newAnimation (gi,"opacity")->setValue (qreal(1),qreal(0))->startAll (Animation::DeleteWhenStopped);
connect(a,SIGNAL(finished()),gi,SLOT(hide()));
*/
