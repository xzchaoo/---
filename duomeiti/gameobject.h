#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QGraphicsItem>

class GameConfig;
//所有游戏对象的基类
//都具备的属性
//位置 大小 旋转 透明度 区域大小
class GameObject : public QObject, public QGraphicsItem{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
	//因为父类的pos属性是final的 无法继承
	//所以要自己写一个
	//位置
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)
	//边界大小
	Q_PROPERTY(QRectF boundRect READ boundingRect WRITE setBoundRect )
	//旋转角度
	Q_PROPERTY(qreal  rotation READ rotation WRITE setRotation )
	//透明度
	Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
public:
	explicit GameObject(QRectF m_boundRect, QGraphicsItem *parent = 0);
	//提供设置boundRect的方法
	virtual void setBoundRect(QRectF boundRect);
	virtual QRectF boundingRect() const;
protected:
	QRectF m_boundRect;
	GameConfig* m_gc;
};

#endif // GAMEOBJECT_H
