#include "iconmanager.h"
#include "gameicon.h"
#include "musicplayer.h"
#include "gameconfig.h"
#include "Animation.h"
#include "imageloader.h"
#include "gamepanel.h"
#include  "chainitem.h"
#include "linkservice.h"
#include "AnimationGroup.h"
#include "spiralfunction.h"
#include "gameiconeffectfactory.h"
#include "linkservice.h"
#include "openingshow.h"

#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QSizeF>
#include <QTextStream>
#include <QTimer>
#include <QGraphicsScene>

IconManager::IconManager(GamePanel* gamePanel){
	m_isUsingTool=false;
	
	m_gamePanel=gamePanel;
	
	//创建 连接 逻辑
	m_linkService=new LinkService(m_gameIconTypeList);
	
	//加载图片 图标图片
	//m_iconLoader=new ImageLoader();
	//m_iconLoader->load ("images/icon");
	
	//冒险岛专用的图片 TODO 目前还没用上
	//m_mxdIconLoader=new ImageLoader();
	//m_mxdIconLoader->load (":/images/mxd");
	
	m_running=false;
	
	m_gc=GameConfig::getInstance ();
	m_musicPlayer=new MusicPlayer();
	m_iconLoader=m_gc->iconLoader ();
	
	m_row=2;
	m_col=2;
}

//last_type表示上一次消除的类型
//每次连击后 自动设置为 其图标的类型 然后等过了持续连击时间后 就又设置为-1
//g1保存上一次点击的图标(不引发消除)
//g2保存本次点击的图标
//g3保存上一次点击的图标(引发消除)
//因此只要 g2,g3,last_type类型一致就可以判断是在连击
void IconManager::iconBeClickedSlot(){
	if(!m_running)
		return;
	
	//本次点击的图标
	GameIcon* clickedGameIcon=(GameIcon*)QObject::sender ();
	if(clickedGameIcon->iconType ()==-1)
		return;
	
	//上一次点击的图标
	GameIcon* lastClickedGameIcon=m_lastClickedGameIcon;

	
	//如果上一次没有点击图标 或者 点击的就是同一个图标 那就 重新设置状态 并且直接返回
	if(lastClickedGameIcon==NULL||lastClickedGameIcon==clickedGameIcon){
		
		m_lastClickedGameIcon=clickedGameIcon;
		m_lastLinkedType=-1;
		return;
	}
	if(m_allowContinueHit){
		if(clickedGameIcon->iconType ()!=lastClickedGameIcon->iconType ()&&clickedGameIcon->iconType ()!=m_lastLinkedType){
			playLinkErrorMusic();
			m_lastClickedGameIcon=clickedGameIcon;
			m_lastLinkedType=-1;
			return;
		}
	}else{
		if(lastClickedGameIcon->iconType ()!=clickedGameIcon->iconType ()){
			playLinkErrorMusic();
			m_lastClickedGameIcon=clickedGameIcon;
			m_lastLinkedType=-1;
			return;
		}
	}
	//如果两者类型不相同那就不能消除了 但是有一种是例外 就是当 本次点击的类型跟上一次消除的类型一样 这时判断是在连消状态
	/*if(lastClickedGameIcon->iconType ()!=clickedGameIcon->iconType ()&&(!m_allowContinueHit||clickedGameIcon->iconType ()!=m_lastLinkedType)){
		playLinkErrorMusic();
		m_lastClickedGameIcon=clickedGameIcon;
		m_lastLinkedType=-1;
		return;
	}*/
	//return;
	
	QPoint p1=lastClickedGameIcon->rowAndCol ();
	QPoint p2=clickedGameIcon->rowAndCol ();
	QList<Point> vs=m_linkService->setBeginPoint (p1)->setEndPoint (p2)->getPassByPoints (m_stepLimit);
	int step=(int)vs.size ()-1;
	if(step==-1){
		playLinkErrorMusic();
		m_lastClickedGameIcon=clickedGameIcon;
		m_lastLinkedType=-1;
		return;
	}
	//否则就是成功了
	//mark标记++
	++m_mark;
	playLinkSuccessMusic();
	createChain(vs);
	
	//判断是不是连击状态
	if(m_allowContinueHit&&clickedGameIcon->iconType ()==m_lastLinkedType)
			emit continueHitSignal ();
	else//否则就是 第一次连击
		emit beginHitSignal ();
	m_lastLinkedType=clickedGameIcon->iconType ();
	//如果允许连击 并且 不是无限连击 就要记得清空标记
	if(m_gc->continueHit ()&&!m_gc->continueHitNoTimeLimit ())
		clearLastTypeLater ();
	//添加特效
	GameIconEffectFactory::addVanishEffect (lastClickedGameIcon);
	GameIconEffectFactory::addVanishEffect (clickedGameIcon);
	
	//lastClickedGameIcon->hide ();
	//clickedGameIcon->hide ();
	//冻结图标
	lastClickedGameIcon->setToFreezing ();
	clickedGameIcon->setToFreezing ();
	//如果能持续连击 就保存m_clickedGameIcon否则设置为NULL(这样每次连击都当做是第一次连击)
	m_lastClickedGameIcon=m_allowContinueHit?clickedGameIcon:NULL;
	
	if(!m_isUsingTool)
		checkGameFinishedSlot ();
}

void IconManager::clearLastTypeLater(){
	QTimer* t=new QTimer();
	t->setProperty ("lastLinkedType",m_lastLinkedType);
	t->setProperty ("mark",m_mark);
	t->setSingleShot (true);
	connect(t,SIGNAL(timeout()),this,SLOT(clearLastTypeSlot()));
	t->start (m_gc->continueHitInterval());
}

void IconManager::clearLastTypeSlot(){
	QTimer* t=qobject_cast<QTimer*>(sender());
	int mark=t->property ("mark").toInt ();
	int lastLinkedType=t->property ("lastLinkedType").toInt ();
	if(mark==m_mark&&lastLinkedType==m_lastLinkedType)
		m_lastLinkedType=-1;
	t->deleteLater ();
}

void IconManager::imitateIconClicked(int x, int y){
	if(getIndex (x,y)<m_gameIconList.size ())
		m_gameIconList[getIndex (x,y)]->imitateIconClicked ();
}

LinkService*IconManager::linkService() const{
	return m_linkService;
}

bool IconManager::running() const{
	return m_running;
}

int IconManager::stepLimit() const{
	return m_stepLimit;
}

QSizeF IconManager::iconSize() const{
	return m_iconSize;
}

void IconManager::setIconSize(QSizeF size){
	m_iconSize=size;
}


void IconManager::playLinkErrorMusic(){
	if(!m_gc->noMusicWhenHitFail ())
		m_musicPlayer->play (m_gc->gets ("/IconManager/errorMusic"));
}

void IconManager::playLinkSuccessMusic(){
	m_musicPlayer->play(m_gc->gets ("/IconManager/successMusic"));
}

int IconManager::getIndex(int row, int col){
	return row*m_col+col;
}

//随机化每个图标的类型(图像)
IconManager*IconManager::createIcons(){
	this->m_gameIconList.reserve (m_row*m_col);
	this->m_gameIconTypeList.reserve (m_row*m_col);
	//设置连接逻辑的大小和数组源
	this->m_linkService->setSize (m_row,m_col);
	
	//产生每个图标的类型
	//posList用于保存还没有分配类型的位置
	QList<QPoint> posList;
	for(int i=0;i<m_row;++i)
		for(int j=0;j<m_col;++j)
			//因为是有外围的 所以 是从1~m_row-1 1~m_col-1
			if( i>=1 && i<m_row-1 && j>=1 && j<m_col-1){
				posList.push_back (QPoint(i,j));
				
				//先占位置
				m_gameIconList.push_back (NULL);
				m_gameIconTypeList.push_back (-1);
				
				/*
				int iconType=qrand()%m_gc->iconTypes ();
				GameIcon* gi=new GameIcon(i,j,QRectF(0,0,0,0),m_gamePanel);
				gi->setGameConfig (m_gc);
				m_gameIconList.push_back (gi);
				m_gameIconTypeList.push_back (iconType);
				
				gi->setIconManager (this)->setIconType (iconType);
				//将gi的clicked信号发送到iconBeClicked 当图标被点击的时候...
				connect(gi,SIGNAL(iconClickedSignal()),this,SLOT(iconBeClickedSlot()));
				//存起来
*/
			}else{
				//外围也要占位置
				m_gameIconList.push_back (NULL);
				m_gameIconTypeList.push_back (-1);
			}
	
	while(posList.size ()>0){
		int iconType=qrand()%m_gc->iconTypes ();

		int r=qrand()%posList.size ();
		
		QPoint p=posList[r];
		int index=getIndex (p);
		posList[r]=posList.last ();
		posList.removeLast ();
		GameIcon* gi=new GameIcon(p.x (),p.y (),QRectF(0,0,0,0),m_gamePanel);
		gi->setGameConfig (m_gc);
		m_gameIconList[index]=gi;
		m_gameIconTypeList[index]=iconType;
		gi->setIconManager (this)->setIconType (iconType);
		connect(gi,SIGNAL(iconClickedSignal()),this,SLOT(iconBeClickedSlot()));
	
		if(posList.size ()>0){
			r=qrand()%posList.size ();
			QPoint p=posList[r];
			index=getIndex (p);
			posList[r]=posList.last ();
			posList.removeLast ();
			GameIcon* gi=new GameIcon(p.x (),p.y (),QRectF(0,0,0,0),m_gamePanel);
			gi->setGameConfig (m_gc);
			m_gameIconList[index]=gi;
			m_gameIconTypeList[index]=iconType;
			gi->setIconManager (this)->setIconType (iconType);
			connect(gi,SIGNAL(iconClickedSignal()),this,SLOT(iconBeClickedSlot()));
		}
	}
	return this;
}

void IconManager::clearOldState(){
	//删除旧的图标
	for(int i=0;i<m_gameIconList.size ();++i){
		GameIcon* gi=(GameIcon*)m_gameIconList[i];
		if(gi!=NULL){
			gi->scene ()->removeItem (gi);
			//gi->deleteLater ();
			delete gi;
		}
	}
	m_gameIconList.clear ();
	m_gameIconTypeList.clear ();
}

void IconManager::setupNewState(){
	m_isUsingTool=false;
	
	//重新设置初始值
	m_lastClickedGameIcon=NULL;
	m_lastLinkedType=-1;
	
	//重新读取游戏设置
	m_allowContinueHit=m_gc->continueHit ();
	m_row=m_gc->rowAndCol ().x ()+2;
	m_col=m_gc->rowAndCol ().y ()+2;
	m_stepLimit=m_gc->limitStep ();
	m_remain=(m_row-2)*(m_col-2);
	
}



QPointF IconManager::getCenterPoint(GameIcon* gi){
	return getCenterPoint(Point(gi->rowAndCol ()));
}

QPointF IconManager::getCenterPoint(Point p){
	return QPointF(p.x*m_iconSize.width ()+m_iconSize.width ()/2,p.y*m_iconSize.height ()+m_iconSize.height ()/2);
}

void IconManager::setToFreezing(GameIcon* gi){
	if(gi->isFreezing ())
		return;
	gi->setIconType (-1);
	gi->setFreezing ();
	m_gameIconTypeList[gi->index ()]=-1;
	--m_remain;
}

//缩放图标 使得它们刚好充满(其实是留有一个外框) 给定的矩形r
void IconManager::fitTheRect(QRectF r){
	OpeningShow giosa(m_gc->openingShowId ());
	giosa.process (r,this);
	this->m_running=true;
}

void IconManager::useToolSlot(ToolEffect* te){
	if(!m_running)
		return;
	m_isUsingTool=true;
	te->process (this);
	m_isUsingTool=false;
}


void IconManager::createChain(const QList<Point>& vs){
	if(!m_running)
		return;
	
	AnimationGroup* ag=new AnimationGroup(1);
	//vs.size非0
	int size=vs.size ()-1;
	qreal opa=1.0/size;
	int dura=400/size;
	for(int i=0;i<size;++i){
		QPointF pf1=getCenterPoint (vs[i]);
		QPointF pf2=getCenterPoint (vs[i+1]);
		if(vs[i].x==vs[i+1].x){
			QRectF re(-10,-10,20,qAbs(pf1.y ()-pf2.y ())+20);
			ChainItem* r=new ChainItem(re,m_gamePanel);
			r->setPos (pf1.y()<pf2.y ()?pf1:pf2);
			r->setOpacity (0);
			Animation* a=new Animation(r,"opacity");
			a->setValue(qreal(0),qreal(opa*(i+1)),dura*(i+1))->addTo (ag);
			a->deleteTargetWhenFinished ();
		}else{
			QRectF re(-10,-10,qAbs(pf1.x ()-pf2.x ())+20,20);
			ChainItem* r=new ChainItem(re,m_gamePanel);
			r->setPos (pf1.x ()<pf2.x ()?pf1:pf2);
			r->setOpacity (0);
			Animation* a=new Animation(r,"opacity");
			a->setValue(qreal(0),qreal(opa*(i+1)),dura*(i+1))->addTo (ag);
			a->deleteTargetWhenFinished ();
		}
	}
	ag->start ();
}

IconManager::~IconManager(){
	//其他东西不是由IconManager管理 不要删除!
	delete m_linkService;
	//delete m_iconLoader;
	//delete m_mxdIconLoader;
	delete m_musicPlayer;
}

QList<int>*IconManager::gameIconTypeList(){
	return &m_gameIconTypeList;
}

GamePanel*IconManager::gamePanel(){
	return m_gamePanel;
}

void IconManager::checkGameFinishedSlot(){
	if(m_remain==0){
		m_running=false;
		emit gameFinishedSignal ();
	}
}

QList<GameIcon*>*IconManager::gameIconList(){
	return &m_gameIconList;
}

void IconManager::stopGameSlot(){
	m_running=false;
}

void IconManager::clickOnViewSlot(){
	if(!m_running)
		return;
	//qDebug()<<"测试"<<endl;
	m_lastClickedGameIcon=NULL;
	m_lastLinkedType=-1;
}


void IconManager::startGameSlot(){
	if(m_running)
		return;
	clearOldState();
	setupNewState();
	createIcons ();
	fitTheRect (m_gamePanel->boundingRect ());
}


//因为是将二维数组拉成一维数组来做的
//获得row,col对应的索引值
int IconManager::getIndex(Point p){
	return p.x*m_col+p.y;
}

QPoint IconManager::rowAndCol() const{
	return QPoint(m_row,m_col);
}
//同上 用QPoint表示 在二维数组中的位置
int IconManager::getIndex(QPoint p){
	return p.x()*m_col+p.y();
}

void IconManager::save(QByteArray* b){
	QDataStream s(b,QIODevice::WriteOnly);
	//保存基本信息
	
	s<<m_gc->curImagePath ();
	
	s<<m_running
	<<m_row<<m_col
	<<m_lastLinkedType<<m_allowContinueHit
	<<m_stepLimit<<m_remain<<m_iconSize;
	
	//保存每个图标的信息
	for(int i=1;i<m_row-1;++i)
		for(int j=1;j<m_col-1;++j){
			GameIcon* gi=m_gameIconList[getIndex(i,j)];
			//保存gi的状态
			s<<gi->isFreezing ()<<gi->iconType ();
		}
}

void IconManager::restore(QByteArray* b){
	
	clearOldState();
	
	QDataStream s(b,QIODevice::ReadOnly);
	
	m_lastClickedGameIcon=NULL;
	//读取基本信息
	QString path;
	s>>path;
	m_gc->loadIconFromPath (path);
	s>>m_running
	>>m_row>>m_col
	>>m_lastLinkedType>>m_allowContinueHit
	>>m_stepLimit>>m_remain>>m_iconSize;
	m_linkService->setSize (m_row,m_col);
	
	qreal width=m_iconSize.width ();
	qreal height=m_iconSize.height ();
	QRectF r(-width/2,-height/2,width,height);
	
	for(int i=0;i<m_row;++i)
		for(int j=0;j<m_col;++j)
			if( i>=1 && i<m_row-1 && j>=1 && j<m_col-1){
				GameIcon* gi=new GameIcon(i,j,r,m_gamePanel);
				gi->setPos (i*width+width/2,j*height+height/2);
				gi->setIconManager (this);
				gi->setGameConfig (m_gc);
				bool isFreezing;
				int iconType;
				s>>isFreezing>>iconType;
				gi->setFreezing (isFreezing);
				m_gameIconTypeList.push_back (iconType);
				gi->setIconType (iconType);
				m_gameIconList.push_back (gi);
				connect(gi,SIGNAL(iconClickedSignal()),this,SLOT(iconBeClickedSlot()));
			}else{
				m_gameIconList.push_back (NULL);
				m_gameIconTypeList.push_back (-1);
			}
}
