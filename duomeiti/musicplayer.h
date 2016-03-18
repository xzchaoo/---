#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QUrl>

class QMediaPlayer;
class QMediaPlaylist;
class GameConfig;

class MusicPlayer : public QObject{
	Q_OBJECT
public:
	explicit MusicPlayer(QObject *parent = 0);
	~MusicPlayer();
public slots:
	void play(const QString& url);
	void stop();
private:
	QMediaPlayer* m_mediaPlayer;
	GameConfig* m_gc;
};

#endif // MUSICPLAYER_H
