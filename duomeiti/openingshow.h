#ifndef OPENINGSHOW_H
#define OPENINGSHOW_H
#include <QObject>
#include "iconmanager.h"
#include "animationfunction.h"

//内置了开局动画
class OpeningShow : public QObject{
	Q_OBJECT
public:
	OpeningShow(int id);
	virtual void process(QRectF r, IconManager* iconManager);
private:
	int m_id;
	QRectF r;
	IconManager* iconManager;
	
	void effect1();
	void effect2();
	void effect3();
	void effect4();
	void effect5();
};

//从中点螺旋到目标位置
class Function4:public AnimationFunction{
public:
	Function4(const QPointF& centerPoint, const QPointF& end,QObject* parent=0);
	virtual QVariant process(qreal t);
	virtual bool canHandle(const QByteArray& propertyName) const;
private:
	QPointF m_centerPoint;
	qreal m_alpha;
	qreal m_distance;
	
};

#endif// OPENINGSHOW_H
