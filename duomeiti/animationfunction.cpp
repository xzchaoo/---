#include "animationfunction.h"

AnimationFunction::AnimationFunction(bool canGoToEnd,QObject *parent) :	QObject(parent){
	m_canGoToEnd=canGoToEnd;
}

bool AnimationFunction::canGoToEnd() const{
	return m_canGoToEnd;
}

AnimationFunction::~AnimationFunction(){
}
