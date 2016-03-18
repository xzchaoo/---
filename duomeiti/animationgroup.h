#ifndef ANIMATIONGROUP_H
#define ANIMATIONGROUP_H

#include <QAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

class Animation;

//封装好了的AnimationGroup动画组
//动画完成后AnimationGroup会删除自己
//千万不要继续引用它!
class AnimationGroup:public QObject {
	Q_OBJECT
	//友元声明
	friend class Animation;
public:
	enum AnimationGroupType{SequentialGroup=0,ParallelGroup=1};
	//构造函数 表示构造顺序组还是平行组
	AnimationGroup(int t);
	//添加一个动画到组里
	AnimationGroup* add(Animation* a);
	//添加一个动画组到组里
	AnimationGroup* add(AnimationGroup* m_group);
	//新建一个平行组
	//因为函数听常用的 所以名字尽量短
	AnimationGroup* newP();
	//新建一个顺序组
	AnimationGroup* newS();
	//开始
	AnimationGroup* start();
	//返回父动画组 比如A动画组里包含了B动画组 那么B的parent就返回A
	AnimationGroup* parent();
	~AnimationGroup();
private:
	//内部实现是依靠一个QAnimationGroup
	QAnimationGroup* m_group;
	AnimationGroup* m_parent;
};

#endif // ANIMATIONGROUP_H
