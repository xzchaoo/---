#include "gametimer.h"
#include "gameconfig.h"

GameTimer::GameTimer(QObject *parent) :
	QTimer(parent){
	connect(this,SIGNAL(timeout()),this,SLOT(addTimeSlot()));
	m_curLoopCount=0;
	m_loopCount=1;
	m_gc=GameConfig::getInstance ();
}

GameTimer*GameTimer::setLoopCount(int loopCount){
	m_loopCount=loopCount;
	return this;
}

int GameTimer::loopCount(){
	return m_loopCount;
}

int GameTimer::curLoopCount(){
	return m_curLoopCount;
}

GameTimer*GameTimer::setInterval(int interval){
	QTimer::setInterval (interval);
	return this;
}

GameTimer*GameTimer::start(){
	m_curLoopCount=0;
	QTimer::start (m_gc->gameTime ()*1000);
	return this;
}

GameTimer*GameTimer::startTimer(){
	m_curLoopCount=0;
	QTimer::start (m_gc->gameTime ());
	return this;
}

GameTimer*GameTimer::pause(){
	stop ();
	return this;
}

GameTimer*GameTimer::recover(){
	QTimer::start ();
	return this;
}

void GameTimer::addTimeSlot(){
	if(++m_curLoopCount==m_loopCount){
		this->stop ();
		emit finishedSignal ();
	}
}
