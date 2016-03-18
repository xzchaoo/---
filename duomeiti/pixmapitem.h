#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H
#include <QPixmap>
#include "gameiconmask.h"

class QGraphicsItem;
class QStyleOptionGraphicsItem;
class QWidget;

//封装了简单的Pixmap图形项
class PixmapItem : public GameIconMask{
	Q_OBJECT
public:
	enum Type{Rectangle,Ellipse};
	explicit PixmapItem(const QPixmap& pix ,QRectF boundRect, QGraphicsItem* parent=0);
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	virtual QPainterPath shape() const;
	void setShapeType(Type t);
	Type shapeType()const{
		return m_shapeType;
	}
private:
	QPixmap m_pixmap;
	Type m_shapeType;
};
#endif // PIXMAPITEM_H
