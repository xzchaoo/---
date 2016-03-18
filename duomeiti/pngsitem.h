#ifndef PNGSITEM_H
#define PNGSITEM_H
#include "gameobject.h"
#include "imageloader.h"

class PngsItem : public GameObject{
	Q_OBJECT
	Q_PROPERTY(int curIndex READ curIndex WRITE setCurIndex )
public:
	explicit PngsItem(int id, QRectF m_boundRect, QGraphicsItem *parent = 0);
	static PngsItem* createPngsItem(QPointF pos, QGraphicsScene* s);
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	int curIndex() const;
	int size()const;
public slots:
	void setCurIndex(int arg);
private:
	ImageLoader* m_imageLoader;
	int m_curIndex;
	int m_id;
};

#endif // PNGSITEM_H
