#ifndef GAMETOOLBAR_H
#define GAMETOOLBAR_H
#include "layer.h"

//一个ToolBar表示左边的一块按钮区域
//里面放了游戏可以使用的道具
class GameToolBar : public Layer{
	Q_OBJECT
public:
	GameToolBar(QRectF m_boundRect, QGraphicsItem* parent=0);
	~GameToolBar();
};

#endif // GAMETOOLBAR_H
