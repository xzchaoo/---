#include "gametool.h"

GameTool::GameTool(const QPixmap& toolPixmap, int toolId, QObject *parent) :
	QObject(parent){
	this->m_toolPixmap=toolPixmap;
	this->m_toolId=toolId;
	this->m_toolPixmap=toolPixmap;
}

QPixmap* GameTool::toolPixmap() {
	return &m_toolPixmap;
}

int GameTool::toolId() const{
	return m_toolId;
}
