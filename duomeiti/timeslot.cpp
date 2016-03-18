#include "timeslot.h"
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include "Animation.h"
#include "gameconfig.h"
#include <QDataStream>

TimeSlot::TimeSlot(QRectF boundRect, QGraphicsItem* parent) :Layer(boundRect,parent){
	//TODO 看能不能用配置文件把它换掉
	GameConfig* gc=GameConfig::getInstance ();
	m_pixmap.load (gc->gets ("/TimeSlot/cao"));
	m_running=false;
	m_curTime=0;
	m_maxTime=60;
}

//画时间槽
//由于是继承了Layer
//所以有一层背景
//需要再draw里画图
void TimeSlot::draw(QPainter* painter){
	//计算剩余时间的比率
	qreal rate=1-m_curTime/m_maxTime;
	//计算相应的颜色起始的地方
	int startX=rate*(m_pixmap.width ()-1);
	painter->drawPixmap (7,7,rate*m_boundRect.width ()-14,m_boundRect.height()-14,m_pixmap,startX,0,1,m_pixmap.height ());
	int sec=(int)m_curTime;
	painter->drawText (7,7,rate*m_boundRect.width (),m_boundRect.height ()-14,Qt::AlignCenter,QString::number(int(m_maxTime-sec)));
}

qreal TimeSlot::curTime() const{
	return m_curTime;
}

void TimeSlot::stopGameSlot(){
	m_running=false;
}

void TimeSlot::setCurTime(qreal arg){
	if(!m_running)
		return;
	m_curTime = arg;
	update();
}

void TimeSlot::startGameSlot(){
	if(m_running)
		return;
	m_running=true;
	m_curTime=0;
	m_maxTime=m_gc->gameTime ();
	m_duration=m_maxTime*1000;
	//动画
	Animation* a=new Animation(this,"curTime");
	a->setValue (qreal(0),qreal(m_maxTime),m_duration)->start (Animation::DeleteWhenStopped);
}


void TimeSlot::save(QByteArray* b){
	QDataStream s(b,QIODevice::WriteOnly);
	s<<m_running<<m_curTime<<m_maxTime;
}

void TimeSlot::restore(QByteArray* b){
	QDataStream s(b,QIODevice::ReadOnly);
	s>>m_running>>m_curTime>>m_maxTime;
	m_duration=1000*(m_maxTime-m_curTime);
	if(m_running){
		Animation* a=new Animation(this,"curTime");
		a->setValue (qreal(m_curTime),qreal(m_maxTime),m_duration)->start (Animation::DeleteWhenStopped);
	}	
}
