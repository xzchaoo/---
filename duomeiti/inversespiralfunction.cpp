#include "inversespiralfunction.h"
#include <QtMath>


static qreal M_TWO_PI=M_PI*2;

InverseSpiralFunction::InverseSpiralFunction(const QPointF& start, const QPointF& end, QObject *parent) :AnimationFunction(true,parent){
	m_end=end;
	m_distance=(start.x()-end.x ())*(start.x ()-end.x ())+(start.y ()-end.y ())*(start.y ()-end.y ());
	m_distance=qSqrt (m_distance);
	m_alpha=qAtan2 (start.y ()-end.y (),start.x ()-end.x ());
}


QVariant InverseSpiralFunction::process(qreal t){
	//m_canGoToEnd=false;
	//return m_end+AnimationInsideFunction::yexingxian (t);
	//动态距离r是时间的函数 要求有 r(0)=r0 r(1)=0; 这样达到缩成一点的效果
	qreal r=m_distance*(1-t);
	qreal x=r*qCos(m_alpha-M_TWO_PI*t);
	qreal y=r*qSin(m_alpha-M_TWO_PI*t);
	return QPointF(x,y)+m_end;
	
			
}

bool InverseSpiralFunction::canHandle(const QByteArray& propertyName) const{
	return propertyName=="pos";
}
