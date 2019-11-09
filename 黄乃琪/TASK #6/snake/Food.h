#pragma once
#include <graphics.h>
#include<time.h>
class Food
{
public:
	Food() {
		genfood();
	}

	void genfood() {
		srand((unsigned)time(NULL));
			x = rand() % 35;
			y = rand() % 35;
	}

	void draw() {
		setfillcolor(RED);
		solidcircle(x * 12 + 160 + 24, y * 12 + 24, 5);
		setfillcolor(WHITE);
	}
	

private:
	int x;
	int y;
};

