#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "layer.h"


//作为游戏中央的面板 东西有待添加
class GamePanel : public Layer{
	Q_OBJECT
public:
	GamePanel(QRectF m_boundRectct, QGraphicsItem* parent=0);
	~GamePanel();
private:
};

#endif // GAMEPANEL_H
