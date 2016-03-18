#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>

class MyView :public QGraphicsView{
	Q_OBJECT
public:
	MyView(QGraphicsScene* s,QWidget* parent=0);
signals:
	void clickOnView();
public slots:
	void saveSettings();
public:
	virtual void resizeEvent(QResizeEvent*);
	virtual void mouseDoubleClickEvent(QMouseEvent*);
	virtual void mousePressEvent(QMouseEvent*);
};

#endif // MYVIEW_H
