#include "imageloader.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>

ImageLoader::ImageLoader(){
}

void ImageLoader::load(const QString& path){
	list.clear ();
	//扫描目录
	QDir dir(path);
	QFileInfoList flist=dir.entryInfoList (QStringList()<<"*.png");
	foreach(QFileInfo fi , flist){
		QPixmap pix(fi.filePath ());
		list.push_back (pix);
		m_pixmapMap.insert (fi.baseName ().toLower (),pix);
	}
}

int ImageLoader::size()const{
	return list.size ();
}

QList<QPixmap>& ImageLoader::icoList(){
	return list;
}

QPixmap ImageLoader::get(int i){
	if(i>=list.size ())
		i=list.size ()-1;
	return list.at (i);
}

//利用[] 如果对应的值不存在 也会构造一个空的QPixmap返回 从而不会造成错误
QPixmap ImageLoader::get(const QString& key){
	return m_pixmapMap[key];
}
