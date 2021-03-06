 /**
 * Competitive Programming - Collection of solved problems.
 *
 * @author        Simone Primarosa,(http://simoneprimarosa.com)
 * @link          (https://github.com/simonepri/competitive-programming)
 * @license       MIT License (https://opensource.org/licenses/MIT)
 */
 
#include <iostream>
#include <fstream>

#include <queue>
#include <limits>
#include <vector>

using namespace std;

#define FILE_INPUT "input.txt"
#define FILE_OUTPUT "output.txt"

#define INFINITE numeric_limits<int>::max()

struct point {
	int x,y;
};

queue<point> P;
vector<point> FX;
vector<point> FY;

int abs(int a) {
	return a >= 0 ? a : -a;
}

int distance_1D(int x1, int x2) {
	return abs(x2-x1);
}

int distance_2D(point p1, point p2) {
	return (p1.x == p2.x) ? (distance_1D(p1.y,p2.y)) : ((p1.y == p2.y) ? (distance_1D(p1.x,p2.x)) : (-1));
}

int nearest(point p1, point p2, point &f1) {
	int min = INFINITE, temp;
	if(p1.y == p2.y) {
		for(vector<point>::iterator it = F.begin(); it != F.end(); it++) {
			if(it->y == p1.y && (p1.x < it->x && it->x <= p2.x || p2.x <= it->x && it->x < p1.x)) {
				temp = distance_1D(p1.x,it->x);
				if(temp < min) {
					min = temp;
					f1 = *it;
				}
			}
		}
	}
	else if(p1.x == p2.x) {
		for(vector<point>::iterator it = F.begin(); it != F.end(); it++) {
			if(it->x == p1.x && (p1.y < it->y && it->y <= p2.y || p2.y <= it->y && it->y < p1.y)) {
				temp = distance_1D(p1.y,it->y);
				if(temp < min) {
					min = temp;
					f1 = *it;
				}
			}
		}
	}
	return min < INFINITE ? min : -1;
}

bool cmp_x(point i, point j) {
	return i.x < j.x;
}

bool cmp_y(point i, point j) {
	return i.y < j.y;
}

int main()
{
	ifstream in(FILE_INPUT);
	ofstream out(FILE_OUTPUT);
	
	if(!in || !out) return 1;
	
	int N, M;
	point turing,percorso,fontanella,maxi,mini;
	in>>N>>M;
	in>>turing.x>>turing.y;
	maxi.x = turing.x; maxi.y = turing.y;
	mini.x = turing.x; mini.y = turing.y;
	for(int i = 0; i < N; i++) {
		in>>percorso.x>>percorso.y;
		if(maxi.x < percorso.x) maxi.x = percorso.x; if(maxi.y < percorso.y) maxi.y = percorso.y;
		if(mini.x > percorso.x) mini.x = percorso.x; if(mini.y > percorso.y) mini.y = percorso.y;
		P.push(percorso);
	}
	F.reserve(M);
	for(int i = 0; i < M; i++) {
		in>>fontanella.x>>fontanella.y;
		if(maxi.x < fontanella.x || maxi.y < fontanella.y || mini.x > fontanella.x || mini.y > fontanella.y) continue;
		FX.push_back(fontanella);
		FY.push_back(fontanella);
	}
	sort(FX.begin(), FX.end(), cmp_x);
	sort(FY.begin(), FY.end(), cmp_y);
	
	int max = 0, done = 0;
	while(!P.empty()) {
		percorso = P.front();
		P.pop();
		int dist;
		while(1) {
			int dist = nearest(turing,percorso,fontanella);
			if(dist == -1) break;
			turing = fontanella;
			int pay = 100-(done+dist);
			done = 0;
			if(-pay > max) max = -pay;
		}
		done += distance_2D(turing, percorso);
		turing = percorso;
		int pay = 100-(done);
		if(-pay > max) max = -pay;
	}
	out<<max;
	
	in.close();
	out.close();
	return 0;
}
