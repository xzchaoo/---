#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H

#include <QObject>
#include <QColor>
#include <QList>
#include <QMap>

#include "basicconfig.h"
#include "iserializable.h"

class GameToolBar;
class IconManager;
class GameToolButton;
class MusicPlayer;
class ImageLoader;
class ToolEffect;
class GameConfig;

class ToolManager : public QObject,public ISerializable{
	Q_OBJECT
public:
	explicit ToolManager(GameToolBar* tb,QObject *parent = 0);
	bool running()const;
	void save(QByteArray* b);
	void restore(QByteArray* b);
signals:
	void useToolEffectGetScoreSignal(int score);
	void useToolSignal (ToolEffect* toolEffect);
	void checkGameFinishedSignal();
	//请求IconManager进入 选择起点的模式
public slots:
	void startGameSlot();
	void stopGameSlot();
	void keyPressed(int keyCode);
	//增加quantity个道具toolId 
	void awardToolSlot(int toolId, int quantity);
private slots:
	void useToolSlot(GameToolButton* btn);
private:
	void createButtons();
	GameToolBar* m_gameToolbar;
	MusicPlayer* m_musicPlayer;
	ImageLoader* m_toolPixmapLoader;
	QList<GameToolButton*> m_gameButtonList;
	QMap<int,GameToolButton*> m_buttonMap;
	bool m_running;
	GameConfig* m_gc;
	int m_maxQuantity;
};

#endif // TOOLMANAGER_H
