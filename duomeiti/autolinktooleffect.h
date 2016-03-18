#ifndef AUTOLINKTOOLEFFECT_H
#define AUTOLINKTOOLEFFECT_H

#include "tooleffect.h"

//自动连线
//参数由配置文件的AutoLinkToolEffect节决定
class AutoLinkToolEffect : public ToolEffect{
	Q_OBJECT
public:
	explicit AutoLinkToolEffect(QObject *parent = 0);
public:
	virtual void process(IconManager* iconManager);
};

#endif // AUTOLINKTOOLEFFECT_H
