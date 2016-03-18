#ifndef RANDOMIZEICONTOOLEFFECT_H
#define RANDOMIZEICONTOOLEFFECT_H

#include "tooleffect.h"

//重新改变场上图标的类型 不会交换位置
class RandomizeIconToolEffect : public ToolEffect{
	Q_OBJECT
public:
	explicit RandomizeIconToolEffect(QObject *parent = 0);
	virtual void process(IconManager* iconManager);
};

#endif // RANDOMIZEICONTOOLEFFECT_H
