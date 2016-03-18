#include "musicplayer.h"
#include <QMediaPlayer>
#include <QUrl>
#include <QMediaPlaylist>
#include "gameconfig.h"
#include <QFile>
#include <QFileInfo>

MusicPlayer::MusicPlayer(QObject *parent) :
	QObject(parent){
	m_mediaPlayer=new QMediaPlayer(this);
	m_gc=GameConfig::getInstance ();
}

MusicPlayer::~MusicPlayer(){
	delete m_mediaPlayer;
}

void MusicPlayer::play(const QString& url){
	if(m_gc->mute ())
		return;
	if(QFile(url).exists ()){
		m_mediaPlayer->setMedia (QUrl(url));
		m_mediaPlayer->play ();
	}else{
		//qDebug()<<url<<"文件不存在"<<endl;
	}
}

void MusicPlayer::stop()
{
	m_mediaPlayer->stop ();
}
