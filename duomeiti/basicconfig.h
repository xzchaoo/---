#ifndef BASICCONFIG_H
#define BASICCONFIG_H

#include <QObject>
#include <QSettings>

//提供基本的读取设置配置文件的功能
class BasicConfig : public QObject{
	Q_OBJECT
public:
	explicit BasicConfig(const QString&fileName, QObject *parent = 0);
	QVariant get(const QString& key, const QVariant& def=QVariant());
	void set(const QString&key, const QVariant& value);
	QString gets(const QString& key);
	void sets(const QString& key,const QString& value);
	int getInt(const QString& key,int def);
	QSettings* settings();
protected:
	QSettings m_settings;
};

#endif // BASICCONFIG_H
