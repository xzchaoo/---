#ifndef INVERSESPIRALFUNCTION_H
#define INVERSESPIRALFUNCTION_H
#include "animationfunction.h"
#include <QPointF>

class InverseSpiralFunction : public AnimationFunction{
	Q_OBJECT
public:
	//表示绕哪个点进行螺线转
	explicit InverseSpiralFunction(const QPointF& start, const QPointF& end,QObject *parent = 0);
	virtual QVariant process(qreal t);
	virtual bool canHandle(const QByteArray& propertyName) const;
private:
	QPointF m_end;
	qreal m_alpha;
	qreal m_distance;
};

#endif // INVERSESPIRALFUNCTION_H
