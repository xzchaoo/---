#ifndef TOOLEFFECT_H
#define TOOLEFFECT_H

#include <QObject>
#include "musicplayer.h"
#include <QList>

class GameIcon;
class IconManager;

//道具效果的基类 有待完善
class ToolEffect : public QObject{
	Q_OBJECT
public:
	explicit ToolEffect(QObject *parent = 0);
	virtual void process(IconManager* iconManager)=0;
	virtual int toolEffectScore()const;
	virtual ~ToolEffect();
	void setMusicPlayer(MusicPlayer* mp);
protected:
	//使用道具获得的得分
	int m_toolEffectScore;
	MusicPlayer* m_musicPlayer;
	GameConfig* m_gc;
};

#endif // TOOLEFFECT_H
