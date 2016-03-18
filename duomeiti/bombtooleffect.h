#ifndef BOMBTOOLEFFECT_H
#define BOMBTOOLEFFECT_H

#include "tooleffect.h"

//炸掉一定区域的图标
//参数由配置文件的BombToolEffect节决定
class BombToolEffect : public ToolEffect{
	Q_OBJECT
public:
	explicit BombToolEffect(QObject *parent = 0);
	virtual void process(IconManager* iconManager);
};

#endif // BOMBTOOLEFFECT_H
