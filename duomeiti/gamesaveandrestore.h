#ifndef GAMESAVEANDRESTORE_H
#define GAMESAVEANDRESTORE_H

#include <QObject>
#include <QMap>
#include <QByteArray>
#include <QFile>
#include <QDataStream>

class GameSaveAndRestore : public QObject{
	Q_OBJECT
public:
	explicit GameSaveAndRestore(QObject *parent = 0);
	bool save(const QString& fileName);
	bool restore(const QString& fileName);
	QByteArray* getRawData(const QString& key);
private:
	QMap<QString,QByteArray > m_map;
};

#endif // GAMESAVEANDRESTORE_H
