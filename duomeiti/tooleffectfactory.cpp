#include "tooleffectfactory.h"
#include "icontypedispeltooleffect.h"
#include "BladestormToolEffect.h"
#include "autolinktooleffect.h"
#include "iconhinttooleffect.h"
#include "bombtooleffect.h"
#include "RandomizeIconToolEffect.h"

//
ToolEffect*ToolEffectFactory::toolEffect(int toolId){
	switch(toolId){
	case 0://重新改变图标为位置 不改变类型
		return new IconHintToolEffect();
	case 1://自动连线一对
		return new AutoLinkToolEffect();
	case 2:	//随机消灭在场的一种图标
		return new IconTypeDispelToolEffect();
	case 3://随机改变图标类型 不改变位置
		return new RandomizeIconToolEffect();
	case 4://剑刃风暴 全灭
		return new BladestormToolEffect();
	case 5://炸掉一定区域
		return new BombToolEffect();
	default:
		return NULL;
	}
}

ToolEffectFactory::ToolEffectFactory(QObject *parent) :
	QObject(parent){
}
