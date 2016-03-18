#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QObject>

//支持序列化的接口
class ISerializable{
public:
	virtual void save(QByteArray* b)=0;
	virtual void restore(QByteArray* b)=0;
	virtual ~ISerializable(){}
};

#endif // ISERIALIZABLE_H
