#ifndef SCOREPANEL_H
#define SCOREPANEL_H

#include "layer.h"
#include <QSettings>

class QPixmap;
class ScoreService;

class ScorePanel : public Layer {
	Q_OBJECT
public:
	explicit ScorePanel(QRectF boundRect, QGraphicsItem* parent=0);
	virtual void draw(QPainter* painter);
	~ScorePanel();
public slots:
	void scoreAndLevelChangedSlot(int score, int level);
private:
	//表示得分
	int m_score;
	//等级
	int m_level;
	//数字图片
	QPixmap* m_numberPixmap;
	QPixmap* m_scorePixmap;
	QPixmap* m_levelPixmap;
	QPixmap* m_nameTextPixmap;
	QPixmap* m_namePixmap;
	QSettings* m_settings;
	QList<int> m_levels;
	QStringList m_names;
	int m_curKey;
	QString m_namePath;
};

#endif // SCOREPANEL_H
