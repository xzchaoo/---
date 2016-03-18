#ifndef GAMETOOLBUTTON_H
#define GAMEBTOOLBUTTON_H

#include "gameobject.h"
#include <QPixmap>
#include <QRectF>

class GameTool;
class ToolManager;
class QGraphicsColorizeEffect;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QGraphicsSceneHoverEvent;
class QGraphicsSceneMouseEvent;


//GameToolButtonEffectFactory这个工厂用于辅助GameToolButton产生一些效果
//道具按钮与GameTool搭配使用
class GameToolButton: public GameObject{
	Q_OBJECT
public:
	GameToolButton(ToolManager* toolManager,const QPixmap& toolPixmap, int toolId, QRectF boundRect, QGraphicsItem* parent=0);
	~GameToolButton();
	GameTool* gameTool()const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	int quantity()const;
	void sendUseToolSignal();
	void setQuantity(int q);
	bool canUse() const;
	void setCanUse(bool canUse);
signals:
	void clicked();
	void useToolSignal(GameToolButton* btn);
public slots:
	void setCanUse(){
		m_canUse=true;
	}
protected:
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	//所关联的tool manager
	ToolManager* m_toolManager;
	//按钮所关联的道具
	GameTool* m_gameTool;
	//表示有几个道具
	int m_quantity;
	//能否使用
	bool m_canUse;
};

#endif // GAMETOOL_H
