#ifndef ICONHINTTOOLEFFECT_H
#define ICONHINTTOOLEFFECT_H
#include "tooleffect.h"


class IconHintToolEffect : public ToolEffect{
	Q_OBJECT
public:
	explicit IconHintToolEffect(QObject *parent = 0);
	virtual void process(IconManager* iconManager);
};

#endif // ICONHINTTOOLEFFECT_H
