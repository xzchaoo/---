#ifndef GAMETOOLBUTTONEFFECTFACTORY_H
#define GAMETOOLBUTTONEFFECTFACTORY_H

#include <QObject>
class GameToolButton;
class QPainter;
class GameObject;

//1个用于添加特效的类
class GameToolButtonEffectFactory : public QObject{
	Q_OBJECT
public:
	static void addHoverEnterEffect(GameObject* obj);
	static void addHoverLeaveEffect(GameObject* obj);
	static void addDisabledEffect(GameObject* obj);
	static void addEnabledEffect(GameObject* obj);
	static void addMousePressEffect(GameObject* obj);
	static void addDisabledPainter(GameObject* obj,QPainter* painter);
	static void addEnabledPainter(GameObject* obj, QPainter* painter);
private:
	explicit GameToolButtonEffectFactory(QObject *parent = 0);
};

#endif // GAMETOOLBUTTONEFFECTFACTORY_H
