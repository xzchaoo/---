#ifndef GAMEICON_H
#define GAMEICON_H
#include "gameobject.h"
#include <QPainter>

class ImageLoader;
class IconManager;

//游戏中央的图标
class GameIcon:public GameObject{
	Q_OBJECT
	friend class GameIconState;
public:
	//构造函数
	//第几行 第几列 边界矩形 icon加载器 父项
	GameIcon(int rowIndex,int colIndex, QRectF boundRect,  QGraphicsItem* parent);
	GameIcon* setIconManager(IconManager* iconManager);
	//一个type和一个图标对应 可以看做是一个图标的id 表明这个对象将显示哪张图
	GameIcon* setIconType(int iconType);
	//获得行和列索引 以一个QPoint的形式
	QPoint rowAndCol();
	void setRowAndCol(const QPoint& p);
	//交换位置 实际上是交换 图标和类型而已就行了
	int getIndex()const;
	//将icon设置成freezing状态 则它就不能再触发一些事件
	//因为按钮消失是渐变的,需要一定时间,这段期间就通过它来拒绝外界发来的信息
	void setToFreezing();
	//获得图标的类型 只有类型相同的图标才能相消
	int iconType();
	bool isFreezing()const;
	void setFreezing(bool b);
	void setFreezing();
	int index()const;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
	bool beFoundMode() const;
	void setBeFoundMode(bool beFoundMode);
	void imitateIconClicked();
public slots:
	void hide();
	//模拟被点击
signals://信号
	void iconClickedSignal();
protected:
	virtual void focusInEvent(QFocusEvent* event);
	virtual void focusOutEvent(QFocusEvent* event);
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
private:
	//是否处于被找到的状态
	//如果是的话 当鼠标悬浮的时候不改变 被找到的状态
	//而当点击了图标之后才会清除该状态
	bool m_beFoundMode;
	//拉成一维数组后的索引
	int m_index;
	int m_rowIndex;
	int m_colIndex;
	int m_iconType;
	ImageLoader* m_iconLoader;
	IconManager* m_iconManager;
	QPixmap m_pixmap;
	bool m_isFreezing;
	
	// IGameConfigAware interface
public:
	virtual void setGameConfig(GameConfig* gc);
};

#endif // GAMEICON_H
