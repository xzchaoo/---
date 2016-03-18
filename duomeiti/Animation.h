#ifndef ANIMATION_H
#define ANIMATION_H

#include <QPropertyAnimation>
#include <QAnimationGroup>

class AnimationFunction;
class AnimationGroup;

//尝试封装一个Animation
//注意在动画过程中自己创建的对象要自己删除!
//TODO 有待完善
class Animation:public QPropertyAnimation{
	Q_OBJECT
public:
	//动画的构造函数 需要指定 对target对象的pix属性进行修改 useMyFunction表示是不是使用我自定义的函数
	Animation(QObject* target, const QByteArray& pix);
	//添加到一个组g里 效果与 g->add(...); 一样 只是主被动而已
	Animation* addTo(QAnimationGroup* g);
	Animation* addTo(AnimationGroup* g);
	//删除target当动画完成时 动画常常要创建一些 一次性的东西 利用这个函数删除它们
	Animation* deleteTargetWhenFinished();
	//setValue的重载版本 方便熟悉的用户,相当于是依次调用了setStartValue setEndValue setDuration setEasingCurve这些函数
	//如果使用了动画函数 并且 动画函数 不能 goToEnd 那么 初始值和默认值必须设置 否则不能正确移动
	Animation* setValue(const QVariant& start, const QVariant& end);
	Animation* setValue(const QVariant& start, const QVariant& end,int duration);
	Animation* setValue(const QVariant& start, const QVariant& end,int duration,const QEasingCurve& easing);
	Animation* setStartValue (const QVariant& v);
	Animation* setEndValue (const QVariant& v);
	//设置动画持续时间
	Animation* setDuration (int dura);
	//设置动画速度弧线
	Animation* setEasingCurve(const QEasingCurve& easing);
	//设置动画函数 对象的变化 将会按照函数对象指示
	//动画完成后自动删除当前绑定的函数对象
	Animation* setFunction(AnimationFunction* af);
	//动画循环几次
	Animation* setLoopCount (int count);
public slots:
	//开始动画
	Animation* start(DeletionPolicy policy=DeleteWhenStopped);
	//开始全部动画 效果与start相同
	Animation* startAll(DeletionPolicy policy=DeleteWhenStopped);
protected:
	//重写这个 实现自己的位置函数
	virtual void updateCurrentTime(int currentTime);
private:
	//动画链
	Animation* m_next;
	AnimationFunction* m_function;
};

#endif // ANIMATION_H
