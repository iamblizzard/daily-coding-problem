#include<bits/stdc++.h>
using namespace std;

struct Point {
	int x,y,idx;
};

vector<Point> points;
pair<int, int> sol;
double dist;

double distance(Point p, Point q) {
	return sqrt((p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y));
}

void findMinDistance(int i, int j) {
	if(i == j)	return;
	if(j - i == 1) {
		double dis = distance(points[i], points[j]);
		if(dist > dis) {
			dist = dis, sol = {points[i].idx, points[j].idx};
		}
		return;
	}
	int mid = (i + j) >> 1;
	findMinDistance(i, mid);
	findMinDistance(mid+1, j);
	
	vector<Point> left, right;
	for(int k = mid; k >= i; --k) {
		if(points[mid+1].x - points[k].x > dist)	break;
		left.emplace_back(points[k]);
	}
	for(int k = mid+1; k <= j; ++k) {
		if(points[k].x - points[mid].x > dist)	break;
		right.emplace_back(points[k]);
	}
	sort(left.begin(), left.end(), [](Point p, Point q){
		return p.y < q.y;
	});
	sort(right.begin(), right.end(), [](Point p, Point q){
		return p.y < q.y;
	});
	for(auto pointL : left) {
		for(auto pointR : right) {
			if(abs(pointL.y - pointR.y) > dist)	break;
			double dis = distance(pointL, pointR);
			if(dist > dis) {
				dist = dis, sol = {pointL.idx, pointR.idx};
			}
		}
	}
}

int main()
{
	int n;
	cout << "Enter no. of points (>= 2) and then the coordinates of the points:\n";
	cin >> n;
	points.resize(n);
	for(int i = 0; i < n; ++i) {
		cin >> points[i].x >> points[i].y;
		points[i].idx = i;
	}
	sort(points.begin(), points.end(), [](Point p, Point q){
		if(p.x != q.x)	return p.x < q.x;
		return p.y < q.y;
	});

	dist = INT_MAX;
	findMinDistance(0, n-1);

	cout << "Minimum distance is: " << dist << endl;
	cout << "Indices of points pair are: " << sol.first << " " << sol.second << endl;

	return 0;
}