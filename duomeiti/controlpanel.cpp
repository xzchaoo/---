#include "controlpanel.h"
#include "gamebutton.h"
#include <QApplication>
#include "gameconfig.h"

ControlPanel::ControlPanel(QRectF boundRect, QGraphicsItem* parent):Layer(boundRect,parent){
	createButtons ();
}

void ControlPanel::createButtons(){
	int marginLeft=(m_boundRect.width ()-200)/2;
	int marginTop=20;
	
	m_start=new GameButton(QRectF(marginLeft,marginTop,200,100),QPixmap(m_gc->gets ("/ControlPanel/kaishi")),this);
	connect(m_start,SIGNAL(click()),this,SLOT(startGameSlot()));
	
	m_restart=new GameButton(QRectF(marginLeft,marginTop*2+100,200,100),QPixmap(m_gc->gets ("/ControlPanel/chongkai")),this);
	connect(m_restart,SIGNAL(click()),this,SLOT(restartGameSlot()));
	
	m_stop=new GameButton(QRectF(marginLeft,marginTop*3+200,200,100),QPixmap(m_gc->gets ("/ControlPanel/jieshu")),this);
	connect(m_stop,SIGNAL(click()),this,SLOT(stopGameSlot()));
	
	GameButton* about=new GameButton(QRectF(marginLeft,marginTop*4+300,200,100),QPixmap(m_gc->gets ("/ControlPanel/about")),this);
}

void ControlPanel::startGameSlot(){
	emit startGameSignal ();
}

void ControlPanel::restartGameSlot(){
	emit restartGameSignal ();
}

void ControlPanel::stopGameSlot(){
	emit stopGameSignal ();
}

