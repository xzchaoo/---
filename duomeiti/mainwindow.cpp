#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "myview.h"
#include "GamePanel.h"
#include "gametoolbar.h"
#include "musicplayer.h"
#include "timeslot.h"
#include "gametimer.h"
#include "toolmanager.h"
#include "scorepanel.h"
#include "scoreservice.h"
#include "iconmanager.h"
#include "iconmanager.h"
#include "toolmanager.h"
#include "settingdialog.h"
#include "gameconfig.h"
#include "controlpanel.h"
#include "gamesaveandrestore.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <ctime>
#include <QDebug>
#include <QFileDialog>
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);
	m_gc=GameConfig::getInstance ();
	m_musicPlayer=new MusicPlayer(m_gc);
	if(m_gc->playBGMOnStartup ())
		m_musicPlayer->play (m_gc->gets ("/MainWindow/bgm"));
	m_running=false;
	createRoundMenu();
	//创建面板
	createLayers ();
	//建立面板之间的联系
	setupLayers();
	//创建信号槽 
	createActions();
	
	qsrand (time(0));
}

MainWindow::~MainWindow(){
	delete ui;
	delete m_scene;
	delete m_view;
	delete m_musicPlayer;
	delete m_gameTimer;
	m_gc->saveConfig ();
	delete m_gc;
	//有一些东西由场景管理负责删除 就不要在这里删除了 否则会出错!
}

void MainWindow::gameFinishedSlot(){
	m_running=false;
	if(!m_gc->noInformationWhenStop ()){
		QString title=m_gc->gets ("/MainWindow/finishTitle");
		QString msg=m_gc->gets ("/MainWindow/finishMsg");
		msg=msg.arg (m_scoreService->score ());
		QMessageBox::information (this,title,msg,QMessageBox::Ok);
	}
}

void MainWindow::stopGameSlot(){
	m_running=false;
	emit stopGameSignal ();
	if(!m_gc->noInformationWhenStop ()){
		QString title=m_gc->gets ("/MainWindow/stopTitle");
		QString msg=m_gc->gets("/MainWindow/stopMsg");
		msg=msg.arg (m_scoreService->score ());
		QMessageBox::information (this,title,msg,QMessageBox::Ok);
	}
}

void MainWindow::on_startGameAction_triggered(){
	if(m_running)
		return;
	m_running=true;
	emit startGameSignal();
}

void MainWindow::createLayers(){
	
	//创建一个场景
	 m_scene= new QGraphicsScene (0,0,1366,768);
	 m_components.insert ("m_scene",m_scene);
	 
	 m_gameToolbar=new GameToolBar(QRectF(0,0,285,710));
	 m_gameToolbar->moveBy (0,40);
	 m_components.insert ("m_gameToolbar",m_gameToolbar);
	 m_scene->addItem (m_gameToolbar);
	 
	 //创建游戏中央的layer
	m_gamePanel=new GamePanel(QRectF(0,0,740,710));
	m_gamePanel->setPos (290,40);
	m_components.insert ("m_gamePanel",m_gamePanel);
	m_scene->addItem (m_gamePanel);
	

	//场景
	m_view=new MyView(m_scene);
	m_view->resize (1366,768);
	m_components.insert ("m_view",m_view);
	//将其设置为中心部件
	setCentralWidget (m_view);
	
	//创建时间槽
	m_timeSlot=new TimeSlot(QRectF(0,0,750,40));
	m_timeSlot->setPos (290,0);
	m_components.insert ("m_timeSlot",m_timeSlot);
	m_scene->addItem (m_timeSlot);

	
	//创建ScorePanel
	m_scorePanel=new ScorePanel(QRectF(0,0,320,200));
	m_scorePanel->setPos (1040,40);
	m_components.insert ("m_scorePanel",m_scorePanel);
	m_scene->addItem (m_scorePanel);
	
	m_controlPanel=new ControlPanel(QRectF(0,0,320,500));
	m_controlPanel->setPos (1040,250);
	m_components.insert ("m_controlPanel",m_controlPanel);
	m_scene->addItem (m_controlPanel);
	
	//创建计时器
	m_gameTimer=new GameTimer();
	m_components.insert ("m_gameTimer",m_gameTimer);
	
	m_scoreService=new ScoreService();
	m_components.insert ("m_scoreService",m_scoreService);
	
	m_iconManager=new IconManager(m_gamePanel);
	m_components.insert ("m_iconManager",m_iconManager);
	
	m_toolManager=new ToolManager(m_gameToolbar);
	m_components.insert ("m_toolManager",m_toolManager);
	
	
}

void MainWindow::setupLayers(){
}

void MainWindow::createActions(){
	//下面的槽的连接顺序是按照游戏流程来的
	//除了内置的信号和槽外 信号和槽的名字尽量加上 Signal Slot
	
	
	//游戏开始 玩家点击菜单 然后利用MainWindow发出startGameSignal信号
	//通知iconManager开始放置图标
	connect(this,SIGNAL(startGameSignal()),m_iconManager,SLOT(startGameSlot()));
	//开始时间槽
	connect(this,SIGNAL(startGameSignal()),m_timeSlot,SLOT(startGameSlot()));
	//开始计时器
	connect(this,SIGNAL(startGameSignal()),m_gameTimer,SLOT(start()));
	//只有游戏启动后才允许使用道具
	connect(this,SIGNAL(startGameSignal()),m_toolManager,SLOT(startGameSlot()));
	
	//开始连击或持续连击的时候通知m_scoreService
	connect (m_iconManager,SIGNAL(beginHitSignal()),m_scoreService,SLOT(beginHitSlot()));
	connect (m_iconManager,SIGNAL(continueHitSignal()),m_scoreService,SLOT(continueHitSlot()));
	
	//当得分有变化的时候通知scorePanel
	connect(m_scoreService,SIGNAL(scoreChangeSignal(int,int)),m_scorePanel,SLOT(scoreAndLevelChangedSlot(int,int)));
	
	//当选择使用道具的时候 通知iconManager
	//根据道具的效果会消灭一些图标
	connect(m_toolManager,SIGNAL(useToolSignal(ToolEffect*)),m_iconManager,SLOT(useToolSlot(ToolEffect*)));
	
	//游戏道具效果完之后产生新的得分 通知scorePanel
	//scorePanel又会发出scoreChangeSignal通知scorePanel
	connect(m_toolManager,SIGNAL(useToolEffectGetScoreSignal(int)),m_scoreService,SLOT(useToolEffectGetScoreSlot(int)));
	
	//使用道具后 检查是否结束
	//如果是正在使用道具过程中游戏结束了 iconManager最好不好发出 游戏完成 的信号
	//否则这次道具使用完的分数还没有加到最后结果上去
	//每当道具使用完之后 toolManager就会发出信号让iconManager检查游戏是否完成
	connect(m_toolManager,SIGNAL(checkGameFinishedSignal()),m_iconManager,SLOT(checkGameFinishedSlot()));
	
	//计时器 时间到了就发信号过来 stopGameSlot
	//然后stopGameSlot发出stopGameSignal信号
	//在stopGameSlot槽中有会发出stopGameSignal
	//暗示着还没有完成游戏
	connect(m_gameTimer,SIGNAL(finishedSignal()),this,SLOT(stopGameSlot()));
	

	//要求停止游戏
	//玩家点了菜单中的停止游戏 或 计时器时间到
	connect(this,SIGNAL(stopGameSignal()),m_iconManager,SLOT(stopGameSlot()));
	connect(this,SIGNAL(stopGameSignal()),m_toolManager,SLOT(stopGameSlot()));
	connect(this,SIGNAL(stopGameSignal()),m_timeSlot,SLOT(stopGameSlot()));
	connect(this,SIGNAL(stopGameSignal()),m_gameTimer,SLOT(stop()));

	//玩家 完成 游戏
	connect(m_iconManager,SIGNAL(gameFinishedSignal()),m_toolManager,SLOT(stopGameSlot()));
	connect(m_iconManager,SIGNAL(gameFinishedSignal()),m_timeSlot,SLOT(stopGameSlot()));
	connect(m_iconManager,SIGNAL(gameFinishedSignal()),m_gameTimer,SLOT(stop()));
	connect(m_iconManager,SIGNAL(gameFinishedSignal()),this,SLOT(gameFinishedSlot()));
	
	//用于告诉iconmanager 鼠标是点击在视图上还是在图标上
	//如果是在视图上 那么要清空一些信息
	//比如下一次连击就要重新开始了
	connect(m_view,SIGNAL(clickOnView()),m_iconManager,SLOT(clickOnViewSlot()));
	
	//开发阶段
	connect (this,SIGNAL(saveSettings()),m_view,SLOT(saveSettings()));
	//奖励道具
	connect(m_scoreService,SIGNAL(awardToolSignal(int,int)),m_toolManager,SLOT(awardToolSlot(int,int)));
	
	
	//右下角面板
	connect(m_controlPanel,SIGNAL(startGameSignal()),this,SLOT(on_startGameAction_triggered()));
	connect(m_controlPanel,SIGNAL(stopGameSignal()),this,SLOT(on_stopGameAction_triggered()));
	connect(m_controlPanel,SIGNAL(restartGameSignal()),this,SLOT(on_restartGameAction_triggered()));
	
}


void MainWindow::on_stopGameAction_triggered(){
	if(!m_running)
		return;
	m_running=false;
	emit stopGameSignal ();
	if(!m_gc->noInformationWhenStop ()){
		QString title=m_gc->gets ("/MainWindow/stopGameActionTitle");
		QString msg=m_gc->gets ("/MainWindow/stopGameActionMsg");
		QMessageBox::information (this,title,msg,QMessageBox::Ok);
	}
}

//用于打开控制面板
void MainWindow::on_settingDialog_triggered(){
	SettingDialog d(this);
	//将窗口阻塞住
	d.exec ();
	if(!m_gc->playBGMOnStartup ())
		m_musicPlayer->stop ();
}

void MainWindow::keyPressEvent(QKeyEvent* e){
	QMainWindow::keyPressEvent (e);
	m_toolManager->keyPressed (e->key ());
}

//重开游戏
void MainWindow::on_restartGameAction_triggered(){
	emit stopGameSignal ();
	emit startGameSignal ();
}

void MainWindow::on_aboutAction_triggered(){
	QMessageBox::about (this,"关于",m_gc->gets ("about"));
}

void MainWindow::on_guideAction_triggered(){
		QMessageBox::about (this,"关于",m_gc->gets ("guide"));
	/*//QMessageBox::about (this,"连连看",m_gc->gets ("guide"));
		QString content = m_gc->gets("guide");
		QString title ="连连看";
		//QMessageBox::about(this,title,content);
		QMessageBox.about(this,title,content);*/
}

void MainWindow::roundSelectSlot(){
	emit stopGameSignal ();
	QAction* a=(QAction*)sender();
	m_gc->loadRound(a->data ().toInt ());
	emit startGameSignal ();
}

void MainWindow::createRoundMenu(){
	QList< Pair<int,QString> > roundList=m_gc->rounds ();
	for(int i=0;i<roundList.size ();++i){
		QAction* a=ui->m_guanqiaMenu->addAction(roundList[i].second);
		a->setData (roundList[i].first);
		connect(a,SIGNAL(triggered()),this,SLOT(roundSelectSlot()));
	}
}

//截图
void MainWindow::on_saveViewAction_triggered(){
	QString fileName=getFile (false,".png");
	if(fileName.isNull ())
		return;
	int w=m_view->rect ().width ();
	int h=m_view->rect ().height ();
	QPixmap p(w,h);
	QPainter pa(&p);
	m_view->render (&pa);
	p.save (fileName);
	
}

void MainWindow::on_saveAction_triggered(){
	QString fileName=getFile (false,".dat");
	if(fileName.isNull ())
		return;
	
	GameSaveAndRestore g;
	ISerializable* is;
	for(QMap<QString,QObject*>::iterator i=m_components.begin ();i!=m_components.end ();++i){
		if((is=dynamic_cast<ISerializable*>(i.value ()))==NULL)
			continue;
		is->save (g.getRawData (i.key ()));
	}
	
	
	g.save (fileName);
}

void MainWindow::on_restoreAction_triggered(){
	QString fileName=getFile (true,".dat");
	if(fileName.isNull ())
		return;
	
	GameSaveAndRestore g;
	if(!g.restore (fileName)){
		QMessageBox::critical (this,"文件不正确!","文件不正确!");
		return;
	}
	
	ISerializable* is;
	for(QMap<QString,QObject*>::iterator i=m_components.begin ();i!=m_components.end ();++i){
		if((is=dynamic_cast<ISerializable*>(i.value ()))==NULL)
			continue;
		is->restore (g.getRawData (i.key ()));
	}
}

//赠送玩家道具...
void MainWindow::on_awardToolAction_triggered(){
	int count=m_gc->getInt ("/ToolManager/count",0);
	for(int i=0;i<count;++i)
		m_toolManager->awardToolSlot (i,100);
}

//切换回默认图标库
void MainWindow::on_defaultIconAction_triggered(){
	m_gc->loadIconFromPath (m_gc->gets ("defaultIconPath"));
}

QString MainWindow::getFile(bool open, const QString& ext){
	QFileDialog d(this);
	d.setAcceptMode (open?QFileDialog::AcceptOpen:QFileDialog::AcceptSave);
	d.setNameFilter ("*"+ext);
	if(!d.exec ())
		return QString::null;
	QString fileName=d.selectedFiles ().at (0);
	if (QFileInfo(fileName).suffix().isEmpty())  //若后缀为空自动添加png后缀  
		fileName.append(ext); 
	return fileName;
}
