#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <QObject>
#include <QSettings>
#include <QPoint>
#include <QMap>

#include "basicconfig.h"
#include "imageloader.h"

template<class T, class U>
struct Pair{
	Pair(){}
	Pair(T t, U u):first(t),second(u){}
	T first;
	U second;
};

//class GameConfig;
//全局共用一个gameConfig
//extern GameConfig gameConfig;

//用于保存游戏设置 析构的时候自动保存到本地文件
//创建的时候自动从文件读取 如果不存在 就使用默认值
class GameConfig : public BasicConfig{
	Q_OBJECT
public:
	~GameConfig();
	//成功保存返回true
	bool saveConfig();
	
	bool continueHit()const;
	void setContinueHit(bool b);
	
	int limitStep() const;
	void setLimitStep(int limitStep);
	
	QPoint rowAndCol() const;
	void setRowAndCol(const QPoint& rowAndCol);
	

	bool continueHitNoTimeLimit() const;
	void setContinueHitNoTimeLimit(bool continueHitNoTimeLimit);
	
	bool playBGMOnStartup() const;
	void setPlayBGMOnStartup(bool playBGMOnStartup);
	
	bool mute() const;
	void setMute(bool mute);
	
	int gameTime() const;
	void setGameTime(int gameTime);
	
	bool noMusicWhenHitFail() const;
	void setNoMusicWhenHitFail(bool value);
	
	int continueHitInterval() const;
	void setContinueHitInterval(int continueHitInterval);
	
	bool noInformationWhenStop() const;
	void setNoInformationWhenStop(bool noInformationWhenStop);
	
	int iconTypes() const;
	void setIconTypes(int iconTypes);
	
	ImageLoader* iconLoader();
	static GameConfig* getInstance();
	ImageLoader* pngsLoader(int i);
	int openingShowId() const;
	void setOpeningShowId(int openingShowId);
	//加载关卡
	void loadRound(int r);
	QList< Pair<int,QString> > rounds()const;
	
	QString curImagePath() const;
	void loadIconFromPath(const QString& path);
private:
	void coverConfig(BasicConfig* bc);
	static GameConfig* m_singleton;
	explicit GameConfig(QObject *parent = 0);
	explicit GameConfig(const GameConfig&);
	GameConfig& operator=(const GameConfig&);
	
	//QSettings m_settings;
	//是否可以连击
	bool m_continueHit;
	//直线条数
	int m_limitStep;
	//行列
	QPoint m_rowAndCol;
	//连击无时长限制
	bool m_continueHitNoTimeLimit;
	//程序启动时播放背景音乐
	bool m_playBGMOnStartup;
	//程序静音
	bool m_mute;
	//游戏进行时间
	int m_gameTime;
	//刚连击失败不发出提示声
	bool m_noMusicWhenHitFail;
	//持续连击最长间隔时间
	int m_continueHitInterval;
	//当游戏停止或完成时 不提示用户
	bool m_noInformationWhenStop;
	//参与游戏的图标的数量
	int m_iconTypes;
	
	//开场动画
	int m_openingShowId;
	ImageLoader m_iconLoader;
	QMap<int,ImageLoader*> m_pngsMap;
	QMap<int,QPoint> m_pngsDXY;
	QList< Pair<int,QString> > m_rounds;

	QString m_curImagePath;
};

#endif // GAMECONFIG_H
