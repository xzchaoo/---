#include "gametoolbutton.h"
#include "gametool.h"
#include "gametoolbuttoneffectfactory.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "toolmanager.h"

GameToolButton::GameToolButton(ToolManager* toolManager, const QPixmap& toolPixmap, int toolId, QRectF boundRect, QGraphicsItem* parent)
	:GameObject(boundRect,parent){
	//接受悬浮事件
	acceptHoverEvents ();
	
	m_canUse=true;
	
	m_quantity=1;
	
	//保存ToolManager指针
	m_toolManager=toolManager;
	
	//TODO
	//GameToolButton的构造函数只传toolid而不用pixmap
	//因为pixmap是和toolid绑定的
	//应该另外搞一个东西来辅助
	//创建相关联的工具
	m_gameTool=new GameTool(toolPixmap,toolId);
	
}

void GameToolButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* ){
	//画出道具图像
	QPixmap* p=m_gameTool->toolPixmap();
	painter->drawPixmap (m_boundRect,*p,p->rect ());
	if(m_quantity==0)
		GameToolButtonEffectFactory::addDisabledPainter (this,painter);
	else{
		QFont oldFont=painter->font ();
		QFont f("微软雅黑",25);
		painter->setFont (f);
		painter->drawText (m_boundRect,Qt::AlignCenter,QString::number(m_quantity));
		painter->setFont (oldFont);
	}
	//	GameToolButtonEffectFactory::addEnabledPainter (this,painter);
		
}

int GameToolButton::quantity() const{
	return m_quantity;
}

void GameToolButton::sendUseToolSignal(){
	if(m_canUse&&m_quantity>0&&m_toolManager->running ()){
		--m_quantity;
		if(m_quantity==0)
			GameToolButtonEffectFactory::addDisabledEffect (this);
		emit useToolSignal (this);
	}
}

void GameToolButton::setQuantity(int q){
	if(q<0)
		return;
	m_quantity=q;
	if(q>0){
		GameToolButtonEffectFactory::addEnabledEffect (this);
		m_canUse=true;
	}else{
		GameToolButtonEffectFactory::addDisabledEffect (this);
		m_canUse=false;
	}
	update();
}

GameToolButton::~GameToolButton(){
	delete m_gameTool;
}

GameTool*GameToolButton::gameTool() const{
	return m_gameTool;
}

void GameToolButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
	GameObject::hoverEnterEvent(event);
	if(!m_quantity||!m_canUse)
		return;
	GameToolButtonEffectFactory::addHoverEnterEffect (this);
}

void GameToolButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
	GameObject::hoverLeaveEvent(event);
	if(!m_quantity||!m_canUse)
		return;
	GameToolButtonEffectFactory::addHoverLeaveEffect (this);
}


void GameToolButton::mousePressEvent(QGraphicsSceneMouseEvent* event){
	GameObject::mousePressEvent (event);
	if(!m_quantity||event->button ()!=Qt::LeftButton||!m_canUse)
		return;
	//按下的特效
	GameToolButtonEffectFactory::addMousePressEffect (this);
	this->sendUseToolSignal ();
	/*if(--m_quantity==0){
		GameToolButtonEffectFactory::addDisabledEffect (this);
	}else{
		GameToolButtonEffectFactory::addMousePressEffect (this);
	}*/
	//emit useToolSignal (this);
}
bool GameToolButton::canUse() const
{
	return m_canUse;
}

void GameToolButton::setCanUse(bool canUse){
	m_canUse = canUse;
	if(!canUse)
		GameToolButtonEffectFactory::addDisabledEffect (this);
	else
		GameToolButtonEffectFactory::addEnabledEffect (this);
	update();
}





//添加阴影

/*
AnimationGroup* ag=new AnimationGroup(0);

 * QParallelAnimationGroup* g=new QParallelAnimationGroup();
QGraphicsOpacityEffect* oe=new QGraphicsOpacityEffect();
oe->setOpacity (0.65);
//oe->setOpacityMask (QPixmap(":/images/pg.png").scaled (48,48));
this->setGraphicsEffect (oe);
(new Animation(oe,"opacity"))->setValue (qreal(1),qreal(0.65),300)->addTo (g);
g->start (Animation::DeleteWhenStopped);

QGraphicsDropShadowEffect* be=new QGraphicsDropShadowEffect();
 //QParallelAnimationGroup* g=new QParallelAnimationGroup();
 
  Animation* a=new Animation(be,"color");
a->setValue (QColor(255,255,255),QColor(0,66,255,255),1000)->addTo (ag->newP ());
//
//ag->newP ()->add (a);
//->addTo (ag->newP ());
//->
		//newAnimation ("blurRadius")->setValue (qreal(0),qreal(3))->
		//newAnimation ("offset")->setValue (qreal(0),qreal(10))->
//;//		addTo (g);
//ag->newP ()->add (a);
//g->start ();
//QParallelAnimationGroup* g2=new QParallelAnimationGroup();
                                                               
Animation* a2=new Animation(be,"color");
a2->setValue (QColor(0,66,255,255),QColor(255,255,255,0),1000)->addTo (ag->newP ());//->addTo (ag->newP ());//->
	 // newAnimation ("blurRadius")->setValue (qreal(3),qreal(0))->
	//  newAnimation ("offset")->setValue (qreal(10),qreal(0))->
//;//	  addTo (g2);
//ag->newP ()->add (a2);
this->setGraphicsEffect (be);
//connect (g,SIGNAL(finished()),g2,SLOT(start()));
//sg->addAnimation (g);
//ssg->addAnimation (g2);
ag->start ();*/
