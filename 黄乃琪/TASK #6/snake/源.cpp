#include<graphics.h>
#include<Windows.h>
#include "Snake.h"
#include "Wall.h"
#include "Food.h"
#include "UI.h"
using namespace std;
Snake snake;
Wall wall;
Food food;
UI ui;

bool GameRunning = true;

bool IsKeyDown(int key) {
	return(GetAsyncKeyState(key) & 0x8000 ? 1 : 0);
}

void KeyboardControl() {
	if (IsKeyDown(VK_ESCAPE)) {
		GameRunning = false;
		return;
	}
	if (IsKeyDown(VK_UP)) {
		snake.ChangeDirection(direction::up);
	}
	if (IsKeyDown(VK_DOWN)) {
		snake.ChangeDirection(direction::down);
	}
	if (IsKeyDown(VK_LEFT)) {
		snake.ChangeDirection(direction::left);
	}
	if (IsKeyDown(VK_RIGHT)) {
		snake.ChangeDirection(direction::right);
	}
}

void HandleLogic() {
	snake.update();
	snake.isdie(GameRunning);
	snake.tryeat(food,ui);
}

void Draw() {
	BeginBatchDraw();
	cleardevice();
	snake.draw();
	wall.draw();
	food.draw();
	ui.draw();
	EndBatchDraw();
}

int main() {
	int i;
	printf("choose the level of game(1-9):");
	scanf_s("%d", &i);
	ui.addl(i); snake.addl(i);
	initgraph(640, 480);
	setbkmode(TRANSPARENT);
	setbkcolor(BLACK);
	setlinecolor(WHITE);
	settextcolor(WHITE);
	while (1) {
		KeyboardControl();
		HandleLogic();
		Draw();
		Sleep(10);
		if (!GameRunning) {
			ui.Gameover();
			Sleep(2000);
			if (IsKeyDown(VK_F1)) { GameRunning = true; snake.reset(); ui.reset();  continue; }
			if (IsKeyDown(VK_ESCAPE)) { break; }
		}
	}
	cleardevice();
	closegraph();
	return 0;
}