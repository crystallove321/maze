// maze.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>

using namespace std;

struct Point{
	Point() {};
	Point(int _x, int _y) {x = _x; y = _y;};

	bool operator == (const Point& _pt) const {
		if (_pt.x == x && _pt.y == y)
			return true;
		return false;
	}
	int x;
	int y;
};

const int N = 8;

class mazepuzzle {
	vector<Point> pt;
	bool mark[N][N];
	Point start;
	Point end;
	

public:
	mazepuzzle() {};
	mazepuzzle(Point _start, Point _end);
	void Create(Point _start, Point _end);
	bool SearchPath(Point _start, int map[][N]);
	Point GetPath(int index);
  int nCount;
};

int mazepuzzle::nCount = 0;

void mazepuzzle::Create(Point _start, Point _end) {
	pt.resize(N*N);
	nCount = 0;
	start = _start;
	end = _end;
	memset(mark, false, sizeof(mark));
};

mazepuzzle::mazepuzzle(Point _start, Point _end) {
	Create(_start, _end);
};

bool mazepuzzle::SearchPath(Point _start, int map[][N]) {
	
	if (_start.x < 0 || _start.x == N || _start.y < 0 || _start.y == N || mark[_start.x][_start.y] == true || map[_start.x][_start.y] == 0)
		return false;
	if (_start == end && map[_start.x][_start.y] == 1) {
		pt[nCount++] = _start;
		mark[_start.x][_start.y] = true;
		return true;
	}
	mark[_start.x][_start.y] = true;
	if (mark[_start.x + 1][_start.y] == false && SearchPath(Point(_start.x + 1, _start.y), map)) {
		mark[_start.x + 1][_start.y] = true;
		pt[nCount++] = Point(_start.x + 1, _start.y);
		return true;
	}
	else if (mark[_start.x][_start.y + 1] == false && SearchPath(Point(_start.x, _start.y + 1), map)){
		mark[_start.x][_start.y + 1] = true;
		pt[nCount++] = Point(_start.x, _start.y + 1);
		return true;
	}
	else if (mark[_start.x - 1][_start.y] == false && SearchPath(Point(_start.x - 1, _start.y), map)) {
		mark[_start.x - 1][_start.y] = true;
		pt[nCount++] = Point(_start.x - 1, _start.y);
		return true;
	}
	else if (mark[_start.x][_start.y - 1] == false && SearchPath(Point(_start.x, _start.y - 1), map)) {
		mark[_start.x][_start.y - 1] = true;
		pt[nCount++] = Point(_start.x, _start.y - 1);
		return true;
	}
	else
		return false;
}

Point mazepuzzle::GetPath(int index) {
	return Point(pt[index]);
}

int main(int argc, char* argv[]) {
	int map[N][N] = {1,1,0,1,1,1,0,1,
		1,1,0,1,1,1,0,1,
		1,1,1,1,0,0,1,1,
		1,0,0,0,1,1,1,1,
		1,1,1,0,1,1,1,1,
		1,0,1,1,1,0,1,1,
		1,0,0,0,1,0,0,1,
		0,1,1,1,1,1,1,1};
	Point st(0 ,0);
	Point ed(7, 7);
	mazepuzzle mz(st, ed);
	if (!mz.SearchPath(st, map))
		cout << "found no path!" << endl;
	else {
		for (int i = 0; i < mz.nCount; i++)
			cout << mz.GetPath(i).x << " " << mz.GetPath(i).y << endl;
	}
	return 0;
}
