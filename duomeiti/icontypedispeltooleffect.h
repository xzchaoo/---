#ifndef ICONTYPEDISPELTOOLEFFECT_H
#define ICONTYPEDISPELTOOLEFFECT_H

#include "tooleffect.h"

//随机消除当前还在场上的某一个种类的全部图标
//改进: 最多消灭几个图标 可以由配置文件决定
class IconTypeDispelToolEffect : public ToolEffect{
	Q_OBJECT
public:
	explicit IconTypeDispelToolEffect(QObject *parent = 0);
public:
	virtual void process(IconManager* iconManager);
};

#endif // ICONTYPEDISPELTOOLEFFECT_H
