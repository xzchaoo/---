#ifndef SPIRALFUNCTION_H
#define SPIRALFUNCTION_H

#include <QObject>
#include "animationfunction.h"
#include <QPointF>

//螺线函数
//用于pos属性
class SpiralFunction : public AnimationFunction{
	Q_OBJECT
public:
	explicit SpiralFunction(const QPointF& start, QObject *parent = 0);
	//强制指定canGoToEnd的值 设置不好可能会导致 对象停在奇怪的位置
	explicit SpiralFunction(const QPointF& start, bool canGoToEnd, QObject* parent=0);
	
	virtual QVariant process(qreal t);
	virtual bool canHandle(const QByteArray& propertyName) const;
private:
	QPointF m_start;
};

#endif // SPIRALFUNCTION_H
