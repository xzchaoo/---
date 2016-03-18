#ifndef ICONMANAGER_H
#define ICONMANAGER_H

#include <QObject>
#include <QSizeF>
#include <QRectF>
#include <QpointF>
#include <QList>

#include "tooleffect.h"
#include "linkservice.h"
#include "iserializable.h"

class LinkService;
class GameIcon;
class ImageLoader;
class ChainItem;
class GamePanel;
class MusicPlayer;
class ToolEffect;
class GameConfig;

class IconManager: public QObject,public ISerializable{
	Q_OBJECT
public:
	//构造函数接受一个GamePanel
	//作为图标们的父对象
	IconManager(GamePanel* gamePanel);
	~IconManager();
	//获得底层的结构
	QList<GameIcon*>* gameIconList();
	QList<int>* gameIconTypeList();
	GamePanel* gamePanel();
	int getIndex(int row, int col);
	int getIndex(Point p);
	int getIndex(QPoint p);
	//注意这个是有包含外围的
	QPoint rowAndCol()const;
	//获得这个icon的中心位置
	QPointF getCenterPoint(GameIcon* gi);
	//获得由p索引所确定的ico的中心位置
	QPointF getCenterPoint(Point p);
	void setToFreezing(GameIcon* gi);
	
	bool running()const;
	int stepLimit()const;
	
	QSizeF iconSize()const;
	void setIconSize(QSizeF size);
	
	virtual void save(QByteArray* b);
	virtual void restore(QByteArray* b);

public slots:
	//接受检查游戏是否完成得请求
	void checkGameFinishedSlot();
	//接受停止游戏的请求
	void stopGameSlot();
	//点在其他区域上 则要清除一些状态 中断持续连击
	void clickOnViewSlot();
	//接受开始游戏的请求
	void startGameSlot();
	//接受使用道具特效的请求
	void useToolSlot(ToolEffect* ve);
	//如果图标被点击了
	void iconBeClickedSlot();
	//一定是QTimer发出的信号给它
	void clearLastTypeSlot();
	LinkService* linkService()const;
	
	//测试用
	void imitateIconClicked(int x, int y);
	
signals:
	//游戏完成的信号 玩家消灭了所有图标
	void gameFinishedSignal();
	//发出开始连击的信号
	void beginHitSignal();
	//发出持续连击的信号
	void continueHitSignal();
	
private:
	//缩放当前的图标内容
	//使得他们可以刚好缩放到给定的矩形里
	void fitTheRect(QRectF r);
	void playLinkErrorMusic();
	void playLinkSuccessMusic();
	void clearLastTypeLater();
	//随机建立图标的图像
	IconManager* createIcons();
	//清理旧的状态 准备开始新一轮之前调用
	void clearOldState();
	void setupNewState();
	//因为我们将二维数组拉成一维数组来做
	//顺序是从左到右从上到下
	//获得row,col处的索引
	//创建两个图标连接起来的特效
	//现在的实现是创建一个黑影
	void createChain(const QList<Point>& vs);
	//连接的逻辑
	//用来判断两个图标之间能不能连起来
	//支持更强的功能
	//比如允许多条连线
	LinkService* m_linkService;
	//游戏面板的引用
	GamePanel* m_gamePanel;
	
	//鼠标前后两次点击的图标
	GameIcon* m_lastClickedGameIcon;
	//一个标记 当用户消除了一种图标之后 就将它++ 然后将它给一个Timer
	//若干时间之后(比如500毫秒) Timer触发clearLastTypeSlot
	//比对两者的mark和lastLinkedType 如果两者都相同 表明用户此期间没有继续连击
	//所以持续连击时间到了 将m_lastLinkedType设置为-1
	int m_mark;
	//上一次消除的类型 注意消除和点击的差别
	int m_lastLinkedType;
	
	//两包图片
	ImageLoader* m_iconLoader;
	//ImageLoader* m_mxdIconLoader;
	
	//用于播放音乐特效
	//考虑将这个拉到外面去
	MusicPlayer* m_musicPlayer;
	
	//考虑到可玩性 方块数量最多不超多20*20[400]个
	//方块移动有22*22块 给外围加上一圈
	QList<GameIcon*> m_gameIconList;
	//用于标识 第i行第j列的图标是什么 一个数字和一个图片是对应的
	//int* iconTypes;
	QList<int> m_gameIconTypeList;
	//记录多少行 多少列
	//它们包括了外围的一圈!
	//记住!
	int m_row;
	int m_col;
	QSizeF m_iconSize;
	//限制连线的最大条数
	//传统是为3条
	//步数限制
	int m_stepLimit;
	
	//是否正在游戏
	bool m_running;
	//是否允许持续连击
	bool m_allowContinueHit;
	
	//用于记录还剩下多少个
	int m_remain;
	
	GameConfig* m_gc;
	
	//正在使用道具
	bool m_isUsingTool;
};



#endif // ICONMANAGER2_H
