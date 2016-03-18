#include "gametoolbuttoneffectfactory.h"
#include <QGraphicsColorizeEffect>
#include "Animation.h"
#include <QColor>
#include <QPainter>
#include "gametoolbutton.h"

void GameToolButtonEffectFactory::addHoverEnterEffect(GameObject* obj){
	//只管new不用删除
	//因为setGraphicsEffect(NULL)的时候会自动删除
	QGraphicsColorizeEffect*ce =new QGraphicsColorizeEffect();
	obj->setGraphicsEffect (ce);
	Animation* a=new Animation(ce,"color");
	a->setStartValue (QColor(0x00,0x66,0xCC));
	a->setEndValue (QColor(0,0,192,255));
	//animation start的默认参数也会使得animation在结束后删除
	a->start ();
}

//TODO
//这里只是简单设置为NULL
void GameToolButtonEffectFactory::addHoverLeaveEffect(GameObject* obj){
	obj->setGraphicsEffect (NULL);
}

void GameToolButtonEffectFactory::addDisabledEffect(GameObject* obj){
	QGraphicsColorizeEffect* ce=new QGraphicsColorizeEffect();
	ce->setColor (QColor(0,0,0));
	obj->setGraphicsEffect (ce);
}

//TODO
//这里只是简单设置为NULL
void GameToolButtonEffectFactory::addEnabledEffect(GameObject* obj){
	obj->setGraphicsEffect (NULL);
}

void GameToolButtonEffectFactory::addMousePressEffect(GameObject* obj){
	QGraphicsColorizeEffect*ce =new QGraphicsColorizeEffect();
	obj->setGraphicsEffect (ce);
	Animation* a=new Animation(ce,"color");
	a->deleteTargetWhenFinished ();
	a->setValue (QColor(0xcc,0x00,0xcc),QColor(0,0,0),200)->start ();
}

void GameToolButtonEffectFactory::addDisabledPainter(GameObject* obj, QPainter* painter){
	QFont oldFont=painter->font ();
	QFont f("微软雅黑",25);
	painter->setFont (f);
	painter->drawText (obj->boundingRect (),Qt::AlignCenter,"没有存货!");
	painter->setFont (oldFont);
}

void GameToolButtonEffectFactory::addEnabledPainter(GameObject* obj, QPainter* painter){

}

GameToolButtonEffectFactory::GameToolButtonEffectFactory(QObject *parent) :	QObject(parent){
}
