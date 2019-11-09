#pragma once
#include<cstdio>
#include <graphics.h>
#include <easyx.h>
using namespace std;
class UI
{
public:
	void Gameover() {
		cleardevice();
		RECT GameOver = { 50,240,639,479 };
		drawtext("Game Over", &GameOver, DT_CENTER);

		char k[] = "Press F1 to continue";
		outtextxy(280, 340, k);
		char j[] = "Press ESC to esc";
		outtextxy(280, 360, j);


	}

	void draw() {
		RECT scoreRect = { 10,10,140,50 };
		drawtext("socre:", &scoreRect, DT_CENTER);

		sprintf_s(s, "%d", score);
		outtextxy(100, 10, s);

		RECT levelRect = { 10,240,140,290 };
		drawtext("level:", &levelRect, DT_CENTER);

		sprintf_s(l, "%d", level);
		outtextxy(100, 240, l);

		settextcolor(RGB(152, 245, 255));
		RECT MSCRect = { 120,240,639,479 };
		drawtext("M S C", &MSCRect, DT_CENTER);
		settextcolor(WHITE);
	}
	void adds() {
		score++;
	}
	
	void addl(int k) {
		level += k;
	}

	void reset() {
		score = 0;
	}
private:
	int level=0;
	int score=0;
	char l[2];
	char s[5];
};

