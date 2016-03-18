#include "scorepanel.h"
#include <QPainter>
#include <QDebug>
#include "scoreservice.h"
#include "gameconfig.h"

ScorePanel::ScorePanel(QRectF boundRect, QGraphicsItem* parent) :
	Layer(boundRect,parent){
	m_score=0;
	m_level=0;
	m_curKey=0;
	
	m_gc=GameConfig::getInstance ();
	m_numberPixmap=new QPixmap(m_gc->gets ("/ScorePanel/number"));
	m_scorePixmap=new QPixmap (m_gc->gets ("/ScorePanel/score"));
	m_levelPixmap=new QPixmap (m_gc->gets ("/ScorePanel/level"));
	m_nameTextPixmap=new QPixmap(m_gc->gets ("/ScorePanel/name"));
	//m_namePixmap=new QPixmap("images/names/chuxinzhe.png");
	m_namePath=m_gc->gets ("/ScorePanel/namePath");
	m_settings=new QSettings(m_namePath+"/config.txt",QSettings::IniFormat);
	QStringList keys=m_settings->allKeys ();
	foreach(QString key, keys){
		bool ok;
		int level=key.toInt (&ok);
		level=ok?level:0;
		m_levels.push_back (level);
		m_names.push_back (m_settings->value (key).toString ());
	}
	m_namePixmap=new QPixmap();
	m_curKey=-1;
	scoreAndLevelChangedSlot(0,0);
}

void ScorePanel::draw(QPainter* painter){
	//画出"分数"
	int w=70;
	int h=50;
	int nw=30;
	QRectF r(7,7,w,h);
	painter->drawPixmap (r,*m_scorePixmap,m_scorePixmap->rect ());
	//画出得分
	QString score=QString::number (m_score);
	r=QRectF(7+w+7+7,7,nw,h);
	for(int i=0;i<score.size ();++i){
		int n=score.at (i).digitValue ();
		painter->drawPixmap (r,*m_numberPixmap,QRectF(32*n,0,32,54));
		r.translate (nw,0);
	}
	//画出"等级"
	r=QRectF(7,7+h+7,w,h);
	painter->drawPixmap (r,*m_levelPixmap,m_levelPixmap->rect ());
	//画出等级
	QString level=QString::number (m_level);
	r=QRectF(7+w+7+7,7+h+7,nw,h);
	for(int i=0;i<level.size ();++i){
		int n=level.at (i).digitValue ();
		painter->drawPixmap (r,*m_numberPixmap,QRectF(32*n,0,32,54));
		r.translate (nw,0);
	}
	//画出称号
	r=QRectF(7,7+h+7+h+7,w,h);
	painter->drawPixmap (r,*m_nameTextPixmap,m_nameTextPixmap->rect ());
	
	//画出等级
	r=QRectF(7+w+7+7,7+h+7+h+7,4*h,h);
	painter->drawPixmap (r,*m_namePixmap,m_namePixmap->rect ());
}

ScorePanel::~ScorePanel(){
	delete m_numberPixmap;
	delete m_scorePixmap;
	delete m_levelPixmap;
	delete m_nameTextPixmap;
	delete m_namePixmap;
}

void ScorePanel::scoreAndLevelChangedSlot(int score, int level){
	m_score=score;
	m_level=level;
	int key=0;
	int max=0;
	for(int i=0;i<m_levels.size ();++i)
		if(level>=m_levels[i]&&m_levels[i]>max){
			key=i;
			max=m_levels[i];
		}
	if(key!=m_curKey){
		delete m_namePixmap;
		m_namePixmap=new QPixmap(m_namePath+"/"+m_names[key]);
		m_curKey=key;
	}
	update ();
}
