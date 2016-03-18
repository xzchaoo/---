#include "gameicon.h"
#include <QPixmap>
#include <QGraphicsScene>
#include "GameIconEffectFactory.h"
#include "imageloader.h"
#include "iconmanager.h"
#include "gameconfig.h"

GameIcon::GameIcon(int rowIndex,int colIndex, QRectF boundRect, QGraphicsItem* parent):GameObject(boundRect,parent){
	setFlag (QGraphicsItem::ItemIsFocusable);
	m_rowIndex=rowIndex;
	m_colIndex=colIndex;
	m_isFreezing=false;
	m_index=-1;
	m_iconType=-1;
	m_beFoundMode=false;
	//采用set方法注入 不然构造函数东西有点多
	m_iconLoader=NULL;
	m_iconManager=NULL;
	acceptHoverEvents ();
}

GameIcon*GameIcon::setIconManager(IconManager* iconManager){
	m_iconManager=iconManager;
	m_index=iconManager->getIndex (m_rowIndex,m_colIndex);
	return this;
}

int GameIcon::iconType(){
	return m_iconType;
}

bool GameIcon::isFreezing() const{
	return m_isFreezing;
}

void GameIcon::setFreezing(bool b){
	m_isFreezing=b;
}

void GameIcon::setFreezing(){
	m_isFreezing=true;
}

int GameIcon::index() const{
	return m_index;
}

GameIcon*GameIcon::setIconType(int iconType){
	m_iconType=iconType;
	if(iconType>=0&&iconType<m_iconLoader->size ())
		m_pixmap=m_iconLoader->get(iconType);
	(*m_iconManager->gameIconTypeList ())[m_index]=iconType;
	return this;
}

QPoint GameIcon::rowAndCol(){
	return QPoint(m_rowIndex,m_colIndex);
}

void GameIcon::setRowAndCol(const QPoint& p){
	m_rowIndex=p.x ();
	m_colIndex=p.y ();
	m_index=m_iconManager->getIndex (p.x (),p.y ());
}

int GameIcon::getIndex() const{
	return m_iconManager->getIndex (m_rowIndex,m_colIndex);
}

void GameIcon::setToFreezing(){
	m_iconManager->setToFreezing (this);
}

void GameIcon::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* ){
	painter->drawPixmap (m_boundRect,m_pixmap,m_pixmap.rect ());
}


void GameIcon::mousePressEvent(QGraphicsSceneMouseEvent* event){
	GameObject::mousePressEvent (event);
	if(!m_isFreezing/*event->button()==Qt::leftButton*/){
		setBeFoundMode(false);
		emit iconClickedSignal ();
	}
}

void GameIcon::hide(){
	setVisible (false);
}


void GameIcon::focusInEvent(QFocusEvent* event){
	GameObject::focusInEvent (event);
	if(m_isFreezing)
		return;
//	GameIconEffectFactory::removeAllEffects (this);
	GameIconEffectFactory::addFocusInEffect(this);
}

void GameIcon::focusOutEvent(QFocusEvent* event){
	//移除特效
	//不要调用下GameIconEffectFactory::removeAllEffects (this);
	//因为将GameIcon隐藏起来是以来于它的子项的 等它的子项目动画结束后自动隐藏 子项目也会自动删除
	GameObject::focusOutEvent (event);
	setGraphicsEffect (NULL);
}


void GameIcon::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
	GameObject::hoverEnterEvent (event);
	//if(m_iconManager->choosingStartPointMode())
//		GameIconEffectFactory::addStartPointEffect (this);
	//else
	//	GameIconEffectFactory::addHoverEnterEffect (this);
}


void GameIcon::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
	GameObject::hoverLeaveEvent (event);
	//GameIconEffectFactory::addHoverLeaveEffect (this);
}

void GameIcon::setGameConfig(GameConfig* gc){
	m_gc=gc;
	m_iconLoader=gc->iconLoader ();
}
bool GameIcon::beFoundMode() const
{
	return m_beFoundMode;
}

void GameIcon::setBeFoundMode(bool beFoundMode){
	m_beFoundMode = beFoundMode;
	setAcceptHoverEvents (!beFoundMode);
}

void GameIcon::imitateIconClicked(){
	setFocus ();
	emit iconClickedSignal ();
}


