#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;

int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls"); // system("clear") for Linux;
	for (int i = 0; i < width +1; i++)
		cout << "#";
	cout << endl;
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x) 
				cout << "0";
				else if (i == foodY && j == foodX)
					cout << "F";
				else {
					bool print = false;
					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << "o";
						}
					}
				if (!print)
					cout << " ";
				}

				
		}
		cout << endl;
	}

	for (int i = 0; i < width +1; i++)
		cout << "#";
	cout << endl;

	cout << "Score " << score << endl;

}

void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
		case 'd':
			dir = RIGHT;
		case 's':
			dir = DOWN;
		case 'w':
			dir = UP;
		case 'x':
			gameOver = true;
		}
	}

}

void Logic() {
	int prevX = tailX[0], prevY = tailY[0];
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
	switch (dir)
	{
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
	}


		//Walls make death
//	if (x > width || x<0 || y> height, y < 0) gameOver = true;

		//Go through walls
	if (x > width)
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y > height)
		y = 0;
	else if (y < 0)
		y = height - 1;


	for (int i = 0; i < nTail; i++) {
		if (tailX[i] = x && tailY[i] == y)
			gameOver = true;
	}

	if (x == foodX && y == foodY) {
		score+=5;
		foodX = rand() + width % 2;
		foodY = rand() + height % 2;
		nTail++;
	}

}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}

	
	return 0;
}