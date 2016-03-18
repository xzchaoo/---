#ifndef SCORESERVICE_H
#define SCORESERVICE_H

#include <QObject>
#include <QTime>
#include "iserializable.h"
#include <QMap>

class GameConfig;

//用于加分逻辑
class ScoreService : public QObject,public ISerializable{
	Q_OBJECT
public:
	explicit ScoreService(QObject *parent = 0);
	void end();
	int score();
	int level();
	virtual void save(QByteArray* b);
	virtual void restore(QByteArray* b);
public slots:
	//表明开始游戏
	void startGameSlot();
	//连接了两个
	void beginHitSlot();
	//表明增加一次连击
	void continueHitSlot();
	void useToolEffectGetScoreSlot(int score);
signals:
	void scoreChangeSignal(int score, int level);
	void awardToolSignal(int toolId, int quantity);
private:
	void award(bool flag);
	//这些静态函数用于指定算分规则 目前还不太完善有待修改
	//每一次连击的分数是时间的次数的函数
	static int f(int n, int rt);
	static int g(int rt);
	static int t(int rt);
	//连击统计
	int m_count;
	int m_score;
	int m_level;
	QTime m_startTime;
	//得分
	int m_beginHitScore;
	int m_continueHitScore;
	int m_scorePerLevel;
	GameConfig* m_gc;
	QMap<int,int> m_awardRate;
	QMap<int,int> m_maxAwardCount;
};

#endif // SCORESERVICE_H
