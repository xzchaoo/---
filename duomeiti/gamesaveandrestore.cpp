#include "gamesaveandrestore.h"

GameSaveAndRestore::GameSaveAndRestore(QObject *parent) :
	QObject(parent)
{
}

bool GameSaveAndRestore::save(const QString& fileName){
	QFile f(fileName);
	if(!f.open (QFile::WriteOnly))
		return false;
	QDataStream s(&f);
	//写入幻数
	s<<(qint32)70862045;
	s<<m_map;
	f.close ();
	return true;
}

bool GameSaveAndRestore::restore(const QString& fileName){
	QFile f(fileName);
	if(!f.open (QFile::ReadOnly))
		return false;
	QDataStream s(&f);
	qint32 magic;
	s>>magic;
	if(magic!=70862045){
		f.close ();
		return false;
	}
	s>>m_map;
	f.close ();
	return true;
}

QByteArray*GameSaveAndRestore::getRawData(const QString& key){
	return &m_map[key];
}
