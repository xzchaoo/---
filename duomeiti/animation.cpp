#include "animation.h"
#include "animationfunction.h"
#include "animationgroup.h"
#include <QPointF>

Animation::Animation(QObject* target, const QByteArray& pix):QPropertyAnimation(target,pix){
	m_next=0;
	m_function=NULL;
}

Animation*Animation::startAll(QAbstractAnimation::DeletionPolicy policy){
	Animation* a=this;
	while(a){
		a->start (policy);
		a=a->m_next;
	}
	return this;
}

Animation*Animation::start(QAbstractAnimation::DeletionPolicy policy){
	QPropertyAnimation::start (policy);
	return this;
}

Animation*Animation::setLoopCount(int count){
	QPropertyAnimation::setLoopCount (count);
	return this;
}

Animation*Animation::setEasingCurve(const QEasingCurve& easing){
	QPropertyAnimation::setEasingCurve (easing);
	return this;
}

Animation*Animation::setFunction(AnimationFunction* af){
	if(af){
		//这些函数是一次性的 用完就删除
		m_function=af;
		connect(this,SIGNAL(destroyed()),af,SLOT(deleteLater()));
	}
	return this;
}

Animation*Animation::setDuration(int dura){
	QPropertyAnimation::setDuration (dura);
	return this;
}

Animation*Animation::setEndValue(const QVariant& v){
	QPropertyAnimation::setEndValue (v);
	return this;
}

Animation*Animation::setStartValue(const QVariant& v){
	QPropertyAnimation::setStartValue (v);
	return this;
}

Animation*Animation::setValue(const QVariant& start, const QVariant& end, int duration, const QEasingCurve& easing){
	return setStartValue (start)->setEndValue (end)->setDuration (duration)->setEasingCurve (easing);
}

Animation*Animation::setValue(const QVariant& start, const QVariant& end, int duration){
	return setStartValue (start)->setEndValue (end)->setDuration (duration)->setEasingCurve (this->easingCurve ());
}

Animation*Animation::setValue(const QVariant& start, const QVariant& end){
	return setStartValue (start)->setEndValue (end)->setDuration (this->duration ())->setEasingCurve (this->easingCurve ());
}

Animation*Animation::addTo(AnimationGroup* g){
	return addTo(g->m_group);
}

Animation*Animation::deleteTargetWhenFinished(){
	connect (this,SIGNAL(destroyed()),targetObject(),SLOT(deleteLater()));
	return this;
}

Animation*Animation::addTo(QAnimationGroup* g){
	Animation* a=this;
	while(a){
		g->addAnimation (a);
		a=a->m_next;
	}
	return this;
}

void Animation::updateCurrentTime(int currentTime){
	//如果设置了动画函数 并且 可以处理当前属性
	if(m_function&&m_function->canHandle (propertyName())){
		int dura = duration();
		//如果持续时间为0
		//那么完成度就为1
		//函数参数currentTime应该是表示当前过了多少时间
		//还要对dura周期模
		const qreal progress = ((dura == 0) ? 1 : ((((currentTime - 1) % dura) + 1) / qreal(dura)));
		qreal easedProgress = easingCurve().valueForProgress(progress);
		//进行校正
		//这个easedProgress表示当前时间的函数点的百分比
		//因为有的easingcurve是先慢后快的
		//单纯用时间作为指标的话 就是线性变化
		//利用它就可以产生突然加速/减速的效果
		//根据帮助文档 返回值 可能大于1 或 小于0 需要进行修正即可
		if (easedProgress > 1.0)
			easedProgress -= 1.0;
		 else if (easedProgress < 0) 
			easedProgress += 1.0;
		//如果函数可以到终点 或 时间不足80%
		//就按照函数产生路径
		//否则交由默认函数去产生路径
		if(m_function->canGoToEnd ()||progress<0.8){
			QPointF pt=m_function->process (easedProgress).toPointF ();
			updateCurrentValue(pt);
			emit valueChanged(pt);
			return;
		}
	}
	//否则只能让调用默认函数了
	QPropertyAnimation::updateCurrentTime (currentTime);
}


