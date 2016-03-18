#ifndef BLADESTORMTOOLEFFECT_H
#define BLADESTORMTOOLEFFECT_H

#include <QObject>
#include "tooleffect.h"

//所有的道具特效 继承ToolEffect 重写process
//Bladestorm(剑刃风暴)特效
//消灭场上所有图标
//属于非常稀有的道具
class BladestormToolEffect : public ToolEffect{
	Q_OBJECT
public:
	explicit BladestormToolEffect(QObject *parent = 0);
public:
	virtual void process(IconManager* IconManager);
};

#endif // BLADESTORMTOOLEFFECT_H
