#include <iostream>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x,y,fruitX,fruitY,score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
}

void Draw() {

}

void Input() {

}

void Logic() {

}

int main() {

	Setup();

	while (!gameOver) {
		Draw();
		Input();
		Logic();
		//Sleep(); can be used to slow game down
	}

	return 0;
}