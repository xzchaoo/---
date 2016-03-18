#include "animationgroup.h"
#include "animation.h"

//假设没有错误
AnimationGroup::AnimationGroup(int t){
	if(t==SequentialGroup)
		m_group=new QSequentialAnimationGroup();
	else// if(t==ParallelGroup)
		m_group=new QParallelAnimationGroup();
	//动画完成删除自己
	connect(m_group,SIGNAL(destroyed()),this,SLOT(deleteLater()));
}

AnimationGroup*AnimationGroup::add(Animation* a) {
	a->addTo (m_group);
	return this;
}

AnimationGroup*AnimationGroup::newP(){
	AnimationGroup* pag=new AnimationGroup(ParallelGroup);
	pag->m_parent=this;
	this->add (pag);
	return pag;
}


AnimationGroup*AnimationGroup::add(AnimationGroup* g){
	this->m_group->addAnimation (g->m_group);
	return this;
}

AnimationGroup*AnimationGroup::newS(){
	AnimationGroup* sag=new AnimationGroup(SequentialGroup);
	sag->m_parent=this;
	this->add (sag);
	return sag;
}

AnimationGroup*AnimationGroup::parent(){
	return m_parent;
}

AnimationGroup::~AnimationGroup(){
}

AnimationGroup*AnimationGroup::start(){
	//注意析构函数里就不要再删除了... 否则有你好受
	m_group->start (QAnimationGroup::DeleteWhenStopped);
	return this;
}
