#include "basicconfig.h"

BasicConfig::BasicConfig(const QString& fileName, QObject *parent) :
	QObject(parent),m_settings(fileName,QSettings::IniFormat){
	m_settings.setIniCodec("utf-8");
}


QVariant BasicConfig::get(const QString& key, const QVariant& def){
	return m_settings.value (key,def);
}

void BasicConfig::set(const QString& key, const QVariant& value){
	m_settings.setValue (key,value);
}

QString BasicConfig::gets(const QString& key){
	return m_settings.value (key).toString ();
}

void BasicConfig::sets(const QString& key, const QString& value){
	m_settings.setValue (key,value);
}

int BasicConfig::getInt(const QString& key, int def){
	bool ok;
	int ret=m_settings.value (key,def).toInt (&ok);
	ret=ok?ret:def;
	return ret;
}

QSettings* BasicConfig::settings() {
	return &m_settings;
}
