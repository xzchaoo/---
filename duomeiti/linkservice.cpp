#include "linkservice.h"

#include <QDebug>
#include <QTextStream>

static int dx[4]={-1,0,1,0};
static int dy[4]={0,1,0,-1};


LinkService::LinkService(const QList<int>& map):map(map){
	init();
}

LinkService*LinkService::setSize(int n, int m){
	if(n>0&&m>0){
		init();
		this->n=n;
		this->m=m;
		this->m_totalSize=n*m;
	}
	return this;
}

LinkService*LinkService::setBeginPoint(int x, int y){
	if(x>=0&&x<n&&y>=0&&y<m){
		m_begin.x=x;
		m_begin.y=y;
	}
	return this;
}

LinkService*LinkService::setBeginPoint(Point p){
	this->m_begin=p;
	return this;
}

LinkService*LinkService::setBeginPoint(QPoint p){
	m_begin.x=p.x();
	m_begin.y=p.y();
	return this;
}

LinkService*LinkService::setEndPoint(QPoint p){
	m_end.x=p.x();
	m_end.y=p.y();
	return this;
}

LinkService*LinkService::setEndPoint(Point p){
	this->m_end=p;
	return this;
}

LinkService*LinkService::setEndPoint(int x, int y){
	if(x>=0&&x<n&&y>=0&&y<m){
		m_end.x=x;
		m_end.y=y;
	}
	return this;
}

int LinkService::minStep(int limit){
	//TODO
	//m_hasDone=false;
	//如果用户已经正确初始化了那m_totalSize不为空
	if(m_totalSize){
		bfs(limit);
		return m_minStep[getIndex(m_end)];
	}
	return -2;
}

QList<Point> LinkService::getPassByPoints(int limit){
	bfs(limit);
	int endIndex=getIndex(m_end);
	//不能到就返回空
	if(m_minStep[endIndex]==-1){
		return QList<Point>();
	}
	QList<Point> v;
	v.push_back(m_end);
	//前面的一个节点
	Point prevPoint=m_minFrom[endIndex];
	//当前面有节点的时候 继续添加
	while(prevPoint.x!=-1){
		v.push_back(prevPoint);
		endIndex=getIndex(prevPoint);
		prevPoint=m_minFrom[endIndex];
	}
	//翻转一下
	reverse(v.begin(),v.end());
	return v;
}

QList<Point> LinkService::findAllByStartPoint(Point p,int stepLimit, int maxCount){
	setBeginPoint (p);
	clearOldStateAndSetupNewState();
	
	//只要类型和起始类型相同的点并且可以到达都可以
	int validType=map[getIndex(m_begin)];
	
	//返回值
	QList<Point> canGo;
	
	//当列表不空...
	while(queue.size()){
		//取出第一个节点
		Point begin=queue.front();
		queue.pop_front();
		//拉成一维数组后的索引
		int beginIndex=getIndex(begin.x,begin.y);
		
		//已经到达最大步数了就退出
		if(m_minStep[beginIndex]==stepLimit)
			break;
		
		//可到达的终点
		Point end;
		for(int i=0;i<4;++i){
			//以起点出发
			end=begin;
			//往同一个方向一直行进 方向向量为 dx[i],dy[i]
			while(true){
				//终点
				end.x+=dx[i];
				end.y+=dy[i];
				//终点的索引
				int endIndex=getIndex(end);
				//判断合法性: 是否落在区域内  是否可以走 是否更优
				if(
						(end.x >= 0 && end.x < n && end. y >= 0 && end. y <m)
						&& ((map[endIndex] ==-1) || (map[endIndex]==validType))
						&& (m_minStep[endIndex]>m_minStep[beginIndex]+1)
				){
					m_minStep[endIndex]=m_minStep[beginIndex]+1;
					m_minFrom[endIndex]=begin;
					if(map[endIndex]!=validType)//注意这个入队条件 否则会产生错误
						queue.push_back(end);
					else{
						//注意这里要break掉... 不然会找到被同类型包围的同类型图标...
						//比如       000
						//              000
						//              000    假设有一种类型是0 现在要寻找其他可以到达的0 如果不break 中间那个0也会被找到...
						canGo.push_back (end);
						//注意当maxCount=-1的时候 其实会转成无穷大2^32-1 因为size() 是无符号的
						if(canGo.size ()>=maxCount)
							return canGo;
						break;
					}
				}else{
					break;//不行就退出white循环
				}
			}
		}
	}
	
	return canGo;
}

LinkService*LinkService::init(){
	this->n=0;
	this->m=0;
	this->m_totalSize=-1;
	this->m_begin=Point(-1,-1);
	this->m_end=Point(-1,-1);
	return this;
}

int LinkService::getIndex(int row, int col){
	return row*m+col;
}

int LinkService::getIndex(Point p){
	return p.x*m+p.y;
}

void LinkService::clearOldStateAndSetupNewState(){
	//清空内容
	m_minFrom.clear();
	m_minStep.clear();
	queue.clear();
	///初始化
	m_minFrom.reserve(m_totalSize);
	m_minStep.reserve(m_totalSize);
	//
	for(int i=0;i<m_totalSize;++i){
		m_minFrom.push_back(Point(-1,-1));
		m_minStep.push_back(m_totalSize);
	}
	
	//添加起点
	queue.push_back(m_begin);
	//起点的步数是0
	m_minStep[getIndex(m_begin)]=0;
}

void LinkService::bfs(int limit){
	clearOldStateAndSetupNewState();
	
	//当列表不空...
	while(queue.size()){
		//取出第一个节点
		Point begin=queue.front();
		queue.pop_front();
		//拉成一维数组后的索引
		int beginIndex=getIndex(begin.x,begin.y);
		
		//已经到达最大步数了就退出
		if(m_minStep[beginIndex]==limit)
			break;
		
		//可到达的终点
		Point end;
		for(int i=0;i<4;++i){
			//以起点出发
			end=begin;
			//往同一个方向一直行进 方向向量为 dx[i],dy[i]
			while(true){
				//终点
				end.x+=dx[i];
				end.y+=dy[i];
				//终点的索引
				int endIndex=getIndex(end);
				//判断合法性: 是否落在区域内  是否可以走 是否更优
				if(
						(
							(end.x >= 0 && end.x < n && end. y >= 0 && end. y <m && map[endIndex] ==-1)
							|
							(end.x == m_end.x && end.y == m_end.y )
							)
						&&
						(m_minStep[endIndex]>m_minStep[beginIndex]+1)
						){
					m_minStep[endIndex]=m_minStep[beginIndex]+1;
					m_minFrom[endIndex]=begin;
					queue.push_back(end);
				}else{
					break;//不行就退出white循环
				}
			}
		}
	}
	//过程中的无穷大(不可到达)使用m_totalSize来表示的 最后把它修正成-1
	for(int i=0;i<m_totalSize;++i)
		if(m_minStep[i]==m_totalSize){
			m_minStep[i]=-1;
		}
}
