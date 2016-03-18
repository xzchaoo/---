#ifndef RANDOMVANISHTOOLEFFECT_H
#define RANDOMVANISHTOOLEFFECT_H

#include "tooleffect.h"

//一定几率(1/m_base)直接让某个图标消失的 道具效果
//类会保证m_base>=2
//基本没用到这个类 考虑删除
class RandomVanishToolEffect : public ToolEffect{
	Q_OBJECT
public:
	explicit RandomVanishToolEffect(int base, QObject *parent = 0);
	virtual void process(IconManager* iconManager);
private:
	int m_base;
};

#endif // RANDOMVANISHTOOLEFFECT_H
