#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;		// Keep track of either game is over or not
const int width = 20;	// Width of screen
const int height = 20;	// Height of screen
int x,y,fruitX,fruitY,score;	// x and y for Snake Head position, fruitX and FruitY for Fruit position
int tailX[100], tailY[100];	// tailX and tailY for all Snake Tail positions
int nTail;			// Size of Snake's Tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;		// Keep track of where snake going

void Setup() {

	// Start with game over set to false
	// and directions set to STOP (snake not moving)
	gameOver = false;
	dir = STOP;
	// Set Snake's starting position (middle of screen)
	x = width / 2;
	y = height / 2;
	// Set Fruit's starting position randomly
	fruitX = rand() % width;
	fruitY = rand() % height;
	// Score starts at 0
	score = 0;

}

void Draw() {

	// Clear screen
	system("cls");
	// Draw top boarder of screen
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	// Draw rest of screen, go through each line up to height
	for (int i = 0; i < height; i++) {
		// For each line, go through each column up to width+2 (counts 2 boarder tiles)
		for (int j = 0; j < width+2; j++) {
			// If it is the first or the last column, print boarder
			if (j == 0 || j == width+1)
				cout << "#";
			// If it is the block where Snake Head is, print Snake Head
			else if (i == y && j == x)
				cout << "O";
			// If it is the block where Fruit is, print Fruit 
			else if (i == fruitY && j == fruitX)
				cout << "F";
			// Otherwise
			else {
				// Keep track if tail printed or not
				bool print = false;
				// Go through each coordinate in tail
				for (int k = 0; k < nTail; k++) {
					// If currently in a tail's coordinate, print tale and set printed to true
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				// If gone through list of tail and this is not a tale coordinate, print empty block
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	// Draw bottom boarder of screen
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl << endl;
	// Display score
	cout << "Score: " << score << endl;

}

void Input() {
	// If a key has been hit
	if (_kbhit()) {
		// Check which key and set direction accordingly
		switch(_getch()) {
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				// Using x to stop game
				gameOver = true;
				break;
		}
	}

}

void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch(dir) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}

	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width-1;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height-1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		nTail++;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}

}

int main() {

	Setup();

	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(25);
	}

	return 0;
}
