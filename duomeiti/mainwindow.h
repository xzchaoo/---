#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
	class MainWindow;
}

class QGraphicsScene;
class GamePanel;
class GameToolBar;
class MyView;
class MusicPlayer;
class TimeSlot;
class GameTimer;
class ToolManager;
class IconManager;
class ScorePanel;
class ScoreService;
class ControlPanel;
class GameConfig;

//主程序
//主要创建了程序界面上各个Layer 确定它们的位置
//以及建立它们之间的联系
class MainWindow : public QMainWindow{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
signals:
	void saveSettings();
	void startGameSignal();
	void stopGameSignal();
	
	//私有槽
private slots:
	void gameFinishedSlot();
	void stopGameSlot();
	void roundSelectSlot();
	
	void on_startGameAction_triggered();
	void on_stopGameAction_triggered();
	void on_restartGameAction_triggered();
	
	void on_settingDialog_triggered();
	
	void on_aboutAction_triggered();
	void on_guideAction_triggered();
	
	void on_saveViewAction_triggered();
	
	void on_saveAction_triggered();
	
	void on_restoreAction_triggered();
	
	void on_awardToolAction_triggered();
	
	void on_defaultIconAction_triggered();
	
private:
	QString getFile(bool open,const QString& ext);
	void createRoundMenu();
	void createLayers();
	void setupLayers();
	void createActions();
	
	//界面ui qt用
	Ui::MainWindow *ui;
	
	//场景 qt自带的类
	QGraphicsScene* m_scene;
	
	//指中央的游戏面板
	GamePanel* m_gamePanel;
	
	//指左边的道具栏
	GameToolBar* m_gameToolbar;
	
	//视图 与QGraphicsScene 一起使用
	//主要用于呈现QGraphicsScene的内容
	MyView* m_view;
	
	//音乐播放器
	MusicPlayer* m_musicPlayer;
	
	//时间槽
	TimeSlot* m_timeSlot;
	
	//游戏计时器
	GameTimer* m_gameTimer;
	
	//得分面板
	ScorePanel* m_scorePanel;
	
	//初始化参数的map
	//QMap<QString,QObject*> m_initObjectMap;
	
	IconManager* m_iconManager;
	ToolManager* m_toolManager;
	ScoreService* m_scoreService;
	
	bool m_running;
	GameConfig* m_gc;
	
	ControlPanel* m_controlPanel;
	
	QMap<QString,QObject*> m_components;
protected:
	virtual void keyPressEvent(QKeyEvent*);
};



#endif // MAINWINDOW_H
