#ifndef LINKSERVICE_H
#define LINKSERVICE_H

#include <list>
#include <algorithm>
#include <QList>
#include <QPoint>
#include <QtCore>

using namespace std;

//请记把删除了的格子值设置成-1

struct Point{
	Point():x(0),y(0){}
	Point(QPoint p):x(p.x ()),y(p.y()){}
	Point(int x, int y){
		this->x=x;
		this->y=y;
	}
	int x;
	int y;
};

class LinkService:public QObject{
	Q_OBJECT
public:
	//规模
	LinkService(const QList<int>& map);
	LinkService* setSize(int n, int m);
	//设置起点
	LinkService* setBeginPoint(int x, int y);
	LinkService* setBeginPoint(Point p);
	LinkService* setBeginPoint(QPoint p);
	LinkService* setEndPoint(QPoint p);
	LinkService* setEndPoint(Point p);
	LinkService* setEndPoint(int x, int y);
	//模式正确可以到达返回步数
	//未初始化返回-2
	//无法到达返回-1
	//limit为最大步数
	int minStep(int limit);
	//获得路过的节点(其中一条路径之一)
	QList<Point> getPassByPoints(int limit);
	//根据一个起点找到所有可以到达的终点//不包括自己到自己
	//在指定步数内
	//最多找到maxCount点就可以了 -1表示无限制
	QList<Point> findAllByStartPoint(Point p, int litmit, int maxCount=-1);
private:
	void clearOldStateAndSetupNewState();
	int m_totalSize;
	int m_startValue;
	int n;
	int m;
	const QList<int>& map;
	Point m_begin;
	Point m_end;
	QList<Point> m_minFrom;
	QList<int> m_minStep;
	list<Point> queue;
	LinkService* init();
	int getIndex(int row, int col);
	int getIndex(Point p);
	//计算起点到其他可到点的最短路和其过程节点
	//最大步数为limit
	//采用广度优先搜索
	void bfs(int limit);
};


#endif // LINKSERVICE_H
