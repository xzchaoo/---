#include "scoreservice.h"
#include <QDebug>
#include "gameconfig.h"

ScoreService::ScoreService(QObject *parent) :
	QObject(parent){
	m_score=0;
	m_level=0;
	
	m_gc=GameConfig::getInstance();
	bool ok;
	m_beginHitScore=m_gc->get("/ScoreService/beginHitScore").toInt (&ok);
	m_beginHitScore=ok?m_beginHitScore:1;
	
	m_continueHitScore=m_gc->get("/ScoreService/continueHitScore").toInt (&ok);
	m_continueHitScore=ok?m_continueHitScore:1;
	
	m_scorePerLevel=m_gc->get("/ScoreService/scorePerLevel").toInt (&ok);
	m_scorePerLevel=ok?m_scorePerLevel:100;
	
	int toolCount=m_gc->getInt ("/ToolManager/count",0);

	for(int i=0;i<toolCount;++i){
		QString s=m_gc->gets ("/ScoreService/"+QString::number (i));
		QStringList ss=s.split (",");
		
		if(ss.size ()!=2){//解析失败 采取默认值
			m_awardRate[i]=10;
			m_maxAwardCount[i]=10;
		}else{
			m_awardRate[i]=ss[0].toInt ();
			m_maxAwardCount[i]=ss[1].toInt ();
			
		}
	}
}

int ScoreService::score(){
	return m_score;
}

int ScoreService::level(){
	return m_level;
}

void ScoreService::startGameSlot(){
	m_score=0;
	m_level=0;
	m_startTime=QTime::currentTime ();
}

void ScoreService::beginHitSlot(){
	m_count=2;
	m_score+=m_beginHitScore;
	m_level=m_score/m_scorePerLevel;
	award(false);
	emit scoreChangeSignal(m_score,m_level);
}

void ScoreService::continueHitSlot(){
	++m_count;
	int score=m_count*m_continueHitScore;
	m_score+=score;
	m_level=m_score/m_scorePerLevel;
	award(true);
	emit scoreChangeSignal(m_score,m_level);
}

void ScoreService::useToolEffectGetScoreSlot(int score){
	m_score+=score;
	m_level=m_score/m_scorePerLevel;
	emit scoreChangeSignal (m_score,m_level);
}

//flag为false则表示最大只奖励1个
//flag为true表示随机1~maxAwardCount个
void ScoreService::award(bool flag){
	for(int i=0;i<m_awardRate.size ();++i){
		if(m_awardRate[i]<=0)//不奖励道具
			continue;
		
		if(qrand()%m_awardRate[i]==0){//如果可以奖励
			int quantity=flag?(qrand()%m_maxAwardCount[i]+1):1;
			emit awardToolSignal (i,quantity);
		}
	}
}

int ScoreService::f(int n, int rt){
	return g(rt)*(n-1)+(7-rt/10000)*(n-2)*(1<<(n-1));
}

int ScoreService::g(int rt){
	if(rt>40000)
		return 2;
	if(rt>20000)
		return 4;
	return 8;
}

int ScoreService::t(int rt){
	return 2000-rt/40;
}



void ScoreService::save(QByteArray* b){
	QDataStream s(b,QIODevice::WriteOnly);
	s<<m_score;
}

void ScoreService::restore(QByteArray* b){
	QDataStream s(b,QIODevice::ReadOnly);
	s>>m_score;
	m_level=m_score/m_scorePerLevel;
	emit scoreChangeSignal (m_score,m_level);
}
