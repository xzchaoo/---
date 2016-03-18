#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H
#include "layer.h"

class GameButton;

//右下角的控制区
class ControlPanel : public Layer{
	Q_OBJECT
public:
	explicit ControlPanel(QRectF boundRect, QGraphicsItem* parent=0);
private:
	void createButtons();
	GameButton* m_start;
	GameButton* m_restart;
	GameButton* m_stop;
signals:
	void startGameSignal();
	void restartGameSignal();
	void stopGameSignal();
public slots:
	void startGameSlot();
	void restartGameSlot();
	void stopGameSlot();
};

#endif // CONTROLPANEL_H
