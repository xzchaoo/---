#ifndef ANIMATIONFUNCTION_H
#define ANIMATIONFUNCTION_H

#include <QObject>
#include <QVariant>


//AnimationFunction用于指导Animation的产生的移动路径
//这是个抽象类
//可以自己尝试改变不同的初始化参数 产生很奇特的效果
class AnimationFunction : public QObject{
	Q_OBJECT
public:
	explicit AnimationFunction(bool canGoToEnd, QObject *parent = 0);
	//这个是时间的函数 根据时间t 返回值 指导动画的进行
	virtual QVariant process(qreal t)=0;
	//表示是否可以处理这种属性
	virtual bool canHandle(const QByteArray& propertyName)const=0;
	bool canGoToEnd()const;
	virtual ~AnimationFunction();
protected:
	//表示函数是否可以移动到最终的终点
	//因为要构造出以任意一点为起点 任意一点为终点的曲线是很麻烦的
	//所以考虑动画进行了80%左右 就切换成 直线移动 这样比较好实现
	//如果函数自己能保证go to end 那么 就为true 否则为false
	//默认是false
	bool m_canGoToEnd;
};

#endif // ANIMATIONFUNCTION_H
