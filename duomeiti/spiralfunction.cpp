#include "spiralfunction.h"
#include <qtmath>
const qreal M_TWO_PI=M_PI*2;

//这个螺线可以保证走到终点 所以传true给父类
SpiralFunction::SpiralFunction(const QPointF& start, QObject *parent) :AnimationFunction(false,parent){
	m_start=start;
}

SpiralFunction::SpiralFunction(const QPointF& start, bool canGoToEnd, QObject* parent):AnimationFunction(canGoToEnd,parent){
	m_start=start;
}


QVariant SpiralFunction::process(qreal t){
	t*=5;
	qreal r=20*(5-t);
	qreal x=r*qCos(M_TWO_PI*t);
	qreal y=r*qSin(M_TWO_PI*t);
	return QPointF(x,y)+m_start;
}

//这个螺线目前只处理pos属性
bool SpiralFunction::canHandle(const QByteArray& propertyName) const{
	return propertyName=="pos";
}
