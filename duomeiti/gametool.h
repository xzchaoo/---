#ifndef GAMETOOL_H
#define GAMETOOL_H

#include <QObject>
#include <QPixmap>

//游戏道具
//封装了相应的图片和道具id
class GameTool : public QObject{
	Q_OBJECT
public:
	explicit GameTool(const QPixmap& toolPixmap, int toolId, QObject *parent = 0);
	explicit GameTool(QObject *parent = 0);
	QPixmap* toolPixmap();
	int toolId()const;
private:
	//道具图片
	QPixmap m_toolPixmap;
	//道具id
	int m_toolId;
	//用于显示道具提示
	QString m_toolTip;
};

#endif // GAMETOOL_H
