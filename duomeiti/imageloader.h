#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <QList>
#include <QPixmap>
#include <QMap>

class ImageLoader:public QObject{
	Q_OBJECT
public:
	ImageLoader();
	void load(const QString& path);
	int size()const;
	QList<QPixmap>& icoList();
	QPixmap get(int i);
	QPixmap get(const QString& key);
private:
	QList<QPixmap> list;
	QMap<QString,QPixmap> m_pixmapMap;
};

#endif // IMAGELOADER_H
