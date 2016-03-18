#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QTimer>

class GameConfig;

//用于游戏计时器
//提供了更多功能
//不过目前还没用到太多功能
class GameTimer : public QTimer{
	Q_OBJECT
public:
	explicit GameTimer(QObject *parent = 0);
	GameTimer* setLoopCount(int loopCount);
	int loopCount();
	int curLoopCount();
	GameTimer* setInterval (int interval);
	GameTimer* startTimer();
	GameTimer* pause();
	GameTimer* recover();
signals:
	void finishedSignal();
public slots:
	GameTimer* start();
private slots:
	void addTimeSlot();
private:
	int m_loopCount;
	int m_curLoopCount;
	GameConfig* m_gc;
};

#endif // GAMETIMER_H
