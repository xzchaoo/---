#include "gameconfig.h"

//单例
GameConfig* GameConfig::m_singleton=NULL;

//添加一个属性的过程
//添加字段
//添加get set(可选)方法
//在构造函数里读取
//在saveConfig里保存
//在UI里添加新的项
//在SettingDialog 构造函数里 读取初始值
//在accept里设置新值
GameConfig::GameConfig(QObject *parent) :
	BasicConfig("config.ini",parent){
	
	m_continueHit=get("continueHit",false).toBool ();
	
	m_limitStep=getInt("limitStep",3);
	
	m_rowAndCol=get("rowAndCol",QPoint(10,10)).toPoint ();
	
	m_continueHitNoTimeLimit=get("continueHitNoTimeLimit",false).toBool ();
	
	m_playBGMOnStartup=get("playBGMOnStartup",false).toBool ();
	
	m_mute=get("mute",false).toBool ();
	
	m_gameTime=getInt("gameTime",60);
	
	m_noMusicWhenHitFail=get("notMusicWhenHitFail",false).toBool ();
	
	m_continueHitInterval=getInt("continueHitInterval",1000);
	
	m_noInformationWhenStop=get("noInformationWhenStop",false).toBool ();
	
	m_openingShowId=getInt("openingShowId",0);
	
	m_iconTypes=getInt("iconTypes",10);
	
	
	m_curImagePath=gets ("defaultIconPath");
	
	m_iconLoader.load (m_curImagePath);
	
	if(m_iconTypes>m_iconLoader.size ())
		m_iconTypes=m_iconLoader.size ();
	
	QString pngs_path=gets ("PngsItem/path");
	int pngs_size=getInt ("/PngsItem/count",0);
	for(int i=1;i<=pngs_size;++i){
		ImageLoader* il=new ImageLoader();
		QString path=pngs_path+"/"+QString::number(i);
		il->load (path);
		m_pngsMap.insert (i,il);
		
		QSettings set(path+"/config.txt",QSettings::IniFormat);
		bool ok;
		int dx=set.value ("dx",0).toInt (&ok);
		dx=ok?dx:0;
		int dy=set.value ("dy",0).toInt (&ok);
		dy=ok?dy:0;
		
		m_pngsDXY.insert(i,QPoint(dx,dy));
		
	}
	
	//加载关卡
	QString roundConfigFile=gets ("roundPath")+"/config.ini";
	BasicConfig bc(roundConfigFile);
	QStringList keys=bc.settings ()->allKeys ();
	foreach(QString key , keys){
		bool ok;
		int r=key.toInt (&ok);
		if(!ok)
			continue;
		QString cfgpath=gets("roundPath")+"/"+bc.gets (key)+"/config.ini";
		BasicConfig bc2(cfgpath);
		m_rounds.push_back (Pair<int,QString>(r,bc2.gets ("title")));
	}
}
QString GameConfig::curImagePath() const
{
	return m_curImagePath;
}

void GameConfig::loadIconFromPath(const QString& path){
	m_iconLoader.load (path);
	setIconTypes (m_iconLoader.size ());
}

int GameConfig::openingShowId() const
{
	return m_openingShowId;
}

void GameConfig::setOpeningShowId(int openingShowId)
{
	m_openingShowId = openingShowId;
}

void GameConfig::loadRound(int r){
	BasicConfig rcfg(gets ("roundPath")+"/config.ini");
	QString path=gets ("roundPath")+"/"+rcfg.gets (QString::number (r));
	QString configFile=path+"/config.ini";
	BasicConfig bc(configFile);
	m_curImagePath=path;
	m_iconLoader.load (m_curImagePath);
	coverConfig (&bc);
}

QList<Pair<int, QString> > GameConfig::rounds() const{
	return m_rounds;
}

void GameConfig::coverConfig(BasicConfig* bc){
	setGameTime (bc->getInt ("gameTime",gameTime ()));
	setLimitStep (bc->getInt ("limitStep",limitStep ()));
	setContinueHit (bc->get ("continueHit",continueHit ()).toBool());
	setRowAndCol (bc->get ("rowAndCol",rowAndCol ()).toPoint ());
	setContinueHitNoTimeLimit (bc->get ("continueHitNoTimeLimit",continueHitNoTimeLimit ()).toBool ());
	setContinueHitInterval (bc->getInt ("continueHitInterval",continueHitInterval ()));
	setIconTypes (m_iconLoader.size ());
}

GameConfig::~GameConfig(){
	saveConfig();
}


bool GameConfig::saveConfig(){
    m_settings.setValue ("continueHit",m_continueHit);
	m_settings.setValue ("limitStep",m_limitStep);
	m_settings.setValue ("rowAndCol",m_rowAndCol);
	m_settings.setValue ("continueHitNoTimeLimit",m_continueHitNoTimeLimit);
	m_settings.setValue ("playBGMOnStartup",m_playBGMOnStartup);
	m_settings.setValue ("mute",m_mute);
	m_settings.setValue ("gameTime",m_gameTime);
	m_settings.setValue ("notMusicWhenHitFail",m_noMusicWhenHitFail);
	m_settings.setValue ("continueHitInterval",m_continueHitInterval);
	m_settings.setValue ("noInformationWhenStop",m_noInformationWhenStop);
	m_settings.setValue ("iconTypes",m_iconTypes);
	m_settings.setValue ("openingShowId",m_openingShowId);
	return true;
}

bool GameConfig::continueHit()const{
	return m_continueHit;
}

void GameConfig::setContinueHit(bool b){
	m_continueHit=b;
}

int GameConfig::limitStep() const
{
	return m_limitStep;
}

void GameConfig::setLimitStep(int limitStep)
{
	m_limitStep = limitStep;
}
QPoint GameConfig::rowAndCol() const
{
    return m_rowAndCol;
}

void GameConfig::setRowAndCol(const QPoint& rowAndCol)
{
	m_rowAndCol = rowAndCol;
}
bool GameConfig::continueHitNoTimeLimit() const
{
    return m_continueHitNoTimeLimit;
}

void GameConfig::setContinueHitNoTimeLimit(bool continueHitNoTimeLimit)
{
    m_continueHitNoTimeLimit = continueHitNoTimeLimit;
}
bool GameConfig::playBGMOnStartup() const
{
	return m_playBGMOnStartup;
}

void GameConfig::setPlayBGMOnStartup(bool playBGMOnStartup)
{
	m_playBGMOnStartup = playBGMOnStartup;
}
bool GameConfig::mute() const
{
    return m_mute;
}

void GameConfig::setMute(bool mute)
{
    m_mute = mute;
}
int GameConfig::gameTime() const
{
    return m_gameTime;
}

void GameConfig::setGameTime(int gameTime){
    m_gameTime = gameTime;
}
bool GameConfig::noMusicWhenHitFail() const
{
    return m_noMusicWhenHitFail;
}

void GameConfig::setNoMusicWhenHitFail(bool value)
{
    m_noMusicWhenHitFail = value;
}
bool GameConfig::noInformationWhenStop() const
{
    return m_noInformationWhenStop;
}

void GameConfig::setNoInformationWhenStop(bool noInformationWhenStop)
{
    m_noInformationWhenStop = noInformationWhenStop;
}
int GameConfig::iconTypes() const
{
    return m_iconTypes;
}

void GameConfig::setIconTypes(int iconTypes){
    m_iconTypes = iconTypes;
}

ImageLoader*GameConfig::iconLoader(){
	return &m_iconLoader;
}
GameConfig* GameConfig::getInstance(){
	if(m_singleton==NULL){
		m_singleton=new GameConfig();
	}
	return m_singleton;
}

ImageLoader*GameConfig::pngsLoader(int i){
	return m_pngsMap[i];
}


int GameConfig::continueHitInterval() const
{
	return m_continueHitInterval;
}

void GameConfig::setContinueHitInterval(int continueHitInterval)
{
	m_continueHitInterval = continueHitInterval;
}
