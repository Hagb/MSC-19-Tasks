#pragma once
#include <graphics.h>
#include <list>
#include"Food.h"
#include"UI.h"
using namespace std;
enum direction {
	up,
	down,
	left,
	right,
};
class Snake
{
public:
	Snake() {
		POINT head = { 1,1 };
		POINT p1 = { 1,2 };
		POINT p2 = { 1,3 };
		bodylist.push_back(head);
		bodylist.push_back(p1);
		bodylist.push_back(p2);
		dir = direction::right;
	}
	void reset() {
		bodylist.clear();
		POINT head = { 1,1 };
		POINT p1 = { 1,2 };
		POINT p2 = { 1,3 };
		bodylist.push_back(head);
		bodylist.push_back(p1);
		bodylist.push_back(p2);
		dir = direction::right;

	}
	void tryeat(Food &food,UI &ui) {
		POINT headc = *bodylist.begin();
		if (getpixel((1+headc.x)*12+160,(1+headc.y)*12+160)!= RED) { return; }
		food.genfood();
		ui.adds();
		POINT end = bodylist.back();
		bodylist.push_back(end);
	}
	
	void isdie(bool &a) {
		POINT headc = *bodylist.begin();
		if (getpixel((0.5 + headc.x) * 12 + 160, (0.5 + headc.y) * 12 + 160) != WHITE
			&& getpixel((0.5 + headc.x) * 12 + 160, (0.5 + headc.y) * 12 + 160) != RED
			&& getpixel((0.5 + headc.x) * 12 + 160, (0.5 + headc.y) * 12 + 160) != BLACK
			|| (0.5 + headc.x) * 12 + 160 <160) { a = false; }
	}

	void ChangeDirection(direction d) {
		if (d == direction::up && dir == direction::down
			|| d == direction::down && dir == direction::up
			|| d == direction::left && dir == direction::right
			|| d == direction::right && dir == direction::left) {
			return;
		}
		dir = d;
	}

	void update() {
		int xset[4] = { 0,0,-1,1 };
		int yset[4] = { -1,1,0,0 };
		static int lmt = 0;
		int ct = GetTickCount();
		if (ct - lmt < 500-(level-1)*50) {
			return;
		}  
		lmt = ct;
		list<POINT>::iterator it = bodylist.begin();
		int px = it->x;
		int py = it->y;
		it->x += xset[dir];
		it->y += yset[dir];
		it++;
		for (; it != bodylist.end(); it++) {
			int cx = it->x;
			int cy = it->y;
			if (cx == px && cy == py) { return; }
			it->x = px;
			it->y = py;
			px = cx;
			py = cy;
		}
	}

	void draw() {
		setlinecolor(BLACK);
		list<POINT>::iterator it = bodylist.begin();
		POINT pos = *it;
		fillrectangle(pos.x * 12 + 160, pos.y * 12 + 160, (pos.x + 1) * 12 + 160, (pos.y + 1) * 12 + 160);
		it++;
		int color = 1;
		for (; it != bodylist.end(); it++) {
			if (color == 8) { color = 1; }
			switch (color) {
			case 1:setfillcolor(RGB(255, 106, 106)); break;
			case 2:setfillcolor(RGB(255, 165, 0)); break;
			case 3:setfillcolor(YELLOW); break; 
			case 4:setfillcolor(GREEN); break;
			case 5:setfillcolor(CYAN); break;
			case 6:setfillcolor(BLUE); break;
			case 7:setfillcolor(MAGENTA); break;
			}
			POINT pos = *it;
			fillrectangle(pos.x * 12+160, pos.y * 12+160, (pos.x + 1) * 12+160, (pos.y + 1) * 12+160);
			color++;
		}
		setlinecolor(WHITE);
		setfillcolor(WHITE);
	}

	void addl(int k){
		level+=k;
	}

private:
	int level = 1;
	list<POINT> bodylist;
	direction dir;
};

