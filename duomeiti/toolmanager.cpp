#include "toolmanager.h"
#include "gametoolbar.h"
#include "gametoolbutton.h"
#include "Animation.h"
#include <QDebug>
#include "musicplayer.h"
#include "imageloader.h"
#include "tooleffectfactory.h"
#include "tooleffect.h"
#include "gametool.h"
#include "gametoolbuttoneffectfactory.h"
#include <QTimer>
#include "gameconfig.h"
#include "gameconfig.h"

ToolManager::ToolManager(GameToolBar* gameToolbar,QObject *parent) :QObject(parent){
	m_toolPixmapLoader=new ImageLoader();
	m_gc=GameConfig::getInstance ();
	m_toolPixmapLoader->load (m_gc->gets("/ToolManager/path"));
	m_maxQuantity=m_gc->getInt ("/ToolManager/maxQuantity",100);
	m_gameToolbar=gameToolbar;
	m_running=false;
	m_musicPlayer=new MusicPlayer();
	createButtons ();
}


bool ToolManager::running() const{
	return m_running;
}

void ToolManager::save(QByteArray* b){
	QDataStream s(b,QIODevice::WriteOnly);
	s<<(qint32)m_gameButtonList.size ();
	for(int i=0;i<m_gameButtonList.size ();++i){
		GameToolButton* gtb=m_gameButtonList[i];
		s<<m_running<<(qint32)gtb->quantity ();
	}
}

void ToolManager::restore(QByteArray* b){
	QDataStream s(b,QIODevice::ReadOnly);
	qint32 size;
	s>>size;
	for(int i=0;i<size&&i<m_gameButtonList.size ();++i){
		qint32 quantity;
		s>>m_running>>quantity;
		GameToolButton* gtb=m_gameButtonList[i];
		gtb->setQuantity (quantity);
	}
}

void ToolManager::startGameSlot(){
	m_running=true;
	GameToolButton* gtb=m_buttonMap.find (0).value ();
	gtb->setCanUse (false);
	QTimer* t=new QTimer();
	t->setSingleShot (true);
	
	connect(t,SIGNAL(timeout()),gtb,SLOT(setCanUse()));
	connect(t,SIGNAL(timeout()),t,SLOT(deleteLater()));
	
	t->start (5000);
}

void ToolManager::stopGameSlot(){m_running=false;}

void ToolManager::keyPressed(int keyCode){
	if(!m_running)
		return;
	if(keyCode==96)
		keyCode=0;
	else{
		keyCode-=Qt::Key_0;
	}
	//负数自动溢出
	if(keyCode>=m_gameButtonList.size ())
		return;
	
	GameToolButton* b=m_gameButtonList[keyCode];
	if(b->quantity ()>0&&b->canUse ()){
		GameToolButtonEffectFactory::addMousePressEffect (b);
		b->sendUseToolSignal ();
	}
}

void ToolManager::awardToolSlot(int toolId, int quantity){
	if(quantity<=0)
		return;
	
	GameToolButton* g=m_buttonMap[toolId];
	if(g==NULL){
		return;
	}
	
	quantity=g->quantity ()+quantity;
	
	quantity=quantity>m_maxQuantity?m_maxQuantity:quantity;
	g->setQuantity (quantity);
}

void ToolManager::createButtons(){
	//TODO 这里考虑直接写死了
	int margin=7;
	int height=(m_gameToolbar->boundingRect ().height ()-7*7)/6;
	
	//获取按钮个数
	int count=m_gc->getInt ("/ToolManager/count",0);
	
	//中心竖线
	int cx=m_gameToolbar->boundingRect ().width ()/2;
	int ox=cx-255/2;
	
	for(int i=0;i<count;++i){
		QString s=m_gc->gets ("/ToolManager/"+QString::number (i));
		QStringList ss=s.split (",");
		int toolId=ss[0].toInt ();
		QString pixId=ss[1];
		GameToolButton* gb=new GameToolButton(this,m_toolPixmapLoader->get (pixId),toolId,QRectF(ox,margin+(height+margin)*i,255,70),m_gameToolbar);
		m_gameButtonList.push_back (gb);
		m_buttonMap.insert (toolId,gb);
		//将消息转发出去
		connect(gb,SIGNAL(useToolSignal(GameToolButton*)),this,SLOT(useToolSlot(GameToolButton*)));
	}
	
}

//btn请求使用道具 toolId
void ToolManager::useToolSlot(GameToolButton* btn){
	if(!m_running)
		return;
	int toolId=btn->gameTool ()->toolId ();
	
	ToolEffect* toolEffect=ToolEffectFactory::toolEffect (toolId);
	if(toolEffect){
		toolEffect->setMusicPlayer (m_musicPlayer);
		emit useToolSignal (toolEffect);
		int score=toolEffect->toolEffectScore ();//获得使用道具的得分
		delete toolEffect;
		emit useToolEffectGetScoreSignal(score);//道具得分的消息
		emit checkGameFinishedSignal();//检查游戏是否完成
	}else{
		//qDebug()<<"无效按钮id = "<<toolId<<endl;
	}
	
	/*
	QPointF c=btn->mapToScene (btn->boundingRect ().center ());
	PixmapItem* p=new PixmapItem(QPixmap(":/images/pg.png"),QRectF(),0);
	btn->scene ()->addItem (p);
	Animation* a=new Animation(p,"pos",false);
	a->setValue (c,btn->parentItem ()->sceneBoundingRect ().center (),300)->newAnimation ("boundRect")
			->setValue (QRectF(-50,-50,0,0),QRectF(-50,-50,100,100))->startAll (Animation::DeleteWhenStopped);
	connect(a,SIGNAL(finished()),p,SLOT(deleteLater()));
	
	*/
}


