#ifndef GAMEICONEFFECTFACTORY_H
#define GAMEICONEFFECTFACTORY_H

#include <QObject>

class GameIcon;

class GameIconEffectFactory : public QObject{
	Q_OBJECT
public:
	//添加消失效果
	static void addVanishEffect(GameIcon* gi);
	//添加得到焦点效果
	static void addFocusInEffect(GameIcon* gi);
	//添加找到的效果
	static void addFindEffect(GameIcon* gi);
	static void removeAllEffects(GameIcon* gi);
	//增加鼠标悬浮时候的效果
	static void addHoverEnterEffect(GameIcon* gi);
	static void addHoverLeaveEffect(GameIcon* gi);
	static void addStartPointEffect(GameIcon* gi);
private:
	explicit GameIconEffectFactory(QObject *parent = 0);
};

#endif // GAMEICONEFFECTFACTORY_H
