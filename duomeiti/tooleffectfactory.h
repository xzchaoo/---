#ifndef TOOLEFFECTFACTORY_H
#define TOOLEFFECTFACTORY_H

#include <QObject>
class ToolEffect;

class ToolEffectFactory : public QObject{
	Q_OBJECT
public:
	static ToolEffect* toolEffect(int toolId);
private:
	explicit ToolEffectFactory(QObject *parent = 0);
};

#endif // TOOLEFFECTFACTORY_H
