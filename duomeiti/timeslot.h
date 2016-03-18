#ifndef TIMESLOT_H
#define TIMESLOT_H
#include "layer.h"
#include <QPixmap>
#include <QDebug>
#include "iserializable.h"

class QGraphicsItem;

//时间槽
class TimeSlot : public Layer,public ISerializable{
	Q_OBJECT
	//这个属性主要用于动画修改curTime值 达到逐渐缩短的效果
	//之所以是qreal类型而不是int类型也是由于这个原因
	Q_PROPERTY(qreal curTime READ curTime WRITE setCurTime )
public:
	explicit TimeSlot(QRectF boundRect, QGraphicsItem* parent=0);
	//画出槽
	virtual void draw(QPainter* painter);
	//获取当前时间
	qreal curTime() const;
	virtual void save(QByteArray* b);
	virtual void restore(QByteArray* b);
public slots:
	//玩家已经进行完游戏 或 要求停止游戏
	void stopGameSlot();
	//设置期那时间
	void setCurTime(qreal arg);
	//开始走时间
	void startGameSlot();
private:
	//时间槽图像渐变颜色(图片)
	QPixmap m_pixmap;
	//当前时间
	qreal m_curTime;
	//最大时间
	qreal m_maxTime;
	int m_duration;
	bool m_running;
};
#endif // TIMESLOT_H
