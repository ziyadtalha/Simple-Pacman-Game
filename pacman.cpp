#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include "mygraphics.h"
using namespace std;

class maze
{
public:

	maze()
	{
		rows = 0;
		cols = 0;
		score = 0;
		winscore = 0;
		teleportColor = false;
		grid = nullptr;
	}

	//parameterised constructor, takes input from file
	maze(string filename) {
		// Read from the text file
		ifstream file(filename);
		string rawinput = "";
		if (file.is_open()) {   //checking whether the file is open
			string temp;
			while (getline(file, temp)) { //read data from file object and put it into string.
				rawinput = rawinput + temp;
			}
			file.close(); //close the file object.
		}

		//GETTING ROWS AND COLUMNS OF LEVEL FROM FILE
		string t;
		int k = 0;
		for (int i = 0; i < 2; i++)
		{
			t = "";
			while (rawinput[k] != ',')
			{
				t = t + rawinput[k];
				k = k + 1;
			}
			k = k + 1;
			if (i == 0)
			{
				stringstream geek1(t);
				geek1 >> rows;
			}
			if (i == 1)
			{
				stringstream geek1(t);
				geek1 >> cols;
			}
		}

		//making a temp array to store the file inputs in
		int* temparr = new int[rows * cols];
		for (int i = 0; i < rows * cols; i++)
		{
			t = "";
			while (rawinput[k] != ',')
			{
				t = t + rawinput[k];
				k = k + 1;
			}
			k = k + 1;
			stringstream geek1(t);
			geek1 >> temparr[i];
		}

		grid = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			grid[i] = new int[cols];
		}

		int x = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int k = 0; k < cols; k++)
			{
				*(grid[i] + k) = temparr[x];
				x++;
			}
		}

		//deallocating temporary array
		delete[] temparr;
		temparr = nullptr;
	}

	virtual ~maze()
	{
		for (int i = 0; i < rows - 1; i++)
		{
			delete[] grid[i];
			grid[i] = nullptr;
		}
		delete[] grid;
		grid = nullptr;
	}

	int getRows() {
		return rows;
	}

	int getCols() {
		return cols;
	}

	int getScore() {
		return score;
	}

	int getWinScore() {
		return winscore;
	}

	int pillsLeft() {
		int pills = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j] == 0)
				{
					pills++;
				}
			}
		}
		return pills;
	}

	void setRows(int r) {
		rows = r;
	}

	void setColumns(int c) {
		cols = c;
	}

	void setScore(int s) {
		score = s;
	}

	void incrementScore() {
		score++;
	}

	void setWinScore(int w) {
		winscore = w;
	}

	void calculateWinScore() {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j] == 0)
				{
					winscore++;
				}
			}
		}
	}

	void changeTeleportColor() {
		if (teleportColor == false)
		{
			teleportColor = true;
		}
		else
		{
			teleportColor = false;
		}
	}

	void displayStats(int Lives) {
		//displaying scoRE
		gotoxy(4, 22);
		cout << " Score: " << getScore() << "				PRESS X TO QUIT" << endl;
		cout << endl;

		//displaying lives
		gotoxy(4, 23);
		cout << " Pills: " << pillsLeft() << "   " << endl;

		//displaying score needed to win
		gotoxy(4, 24);
		cout << " Lives: " << Lives << "				PRESS P TO PAUSE" << endl;

		showConsoleCursor(false);
	}

	void displayBoard() {
		delay(50);

		//board with the dot should be 26x30 (not including border)
		int y = 0;

		for (int i = 0; i < rows; i++)
		{
			int x = 10;
			for (int k = 0; k < cols; k++)
			{
				if (i == 0)
				{
					if (grid[i][k] == 0)
					{
						grid[i][k] == 1;
					}
					drawRectangle(0, 5, 480, 20, 0, 0, 255, 255, 0, 0);
				}
				else
				{
					if (i == rows - 1)
					{
						if (grid[i][k] == 0)
						{
							grid[i][k] == 1;
						}
						drawLine(0, 350, 465, 350, 255, 255, 255);
					}
					else
					{
						if ((k > 0) && (k < cols - 1))
						{
							if (grid[i][k] == 0)
							{
								drawEllipse(x + 20, y + 20, x + 10, y + 10, 0, 0, 0, 160, 160, 160);
							}
							else if (grid[i][k] == 1)
							{
								drawRectangle(x + 10, y + 5, x + 30, y + 25, 0, 0, 0, 0, 100, 200);
							}
							else if (grid[i][k] == -1)
							{
								drawEllipse(x + 20, y + 20, x + 10, y + 10, 0, 0, 0, 0, 0, 0);
							}
							else if ((grid[i][k] == 5) || (grid[i][k] == 6))
							{
								if (teleportColor == false)
								{
									drawRectangle(x + 10, y + 5, x + 30, y + 25, 0, 0, 0, 230, 0, 230);
								}
								else
								{
									drawRectangle(x + 10, y + 5, x + 30, y + 25, 230, 0, 230, 255, 150, 150);
								}
							}
							else if (grid[i][k] == 4)
							{
								drawEllipse(x + 20, y + 20, x + 10, y + 10, 250, 250, 250, 250, 250, 250);
							}
							x = x + 20;
						}
						else
						{
							if (grid[i][k] == 0)
							{
								grid[i][k] == 1;
							}
						}
					}
				}
			}
			//updating y coordinates for displaying board
			y = y + 20;
		}

		//border of board (starts from x = 10 to x = 510), (y = 10 to y = 460)
		drawRectangle(0, 20, 15, 350, 0, 0, 255, 255, 0, 0);
		drawRectangle(465, 20, 480, 350, 0, 0, 255, 255, 0, 0);

		drawLine(480, 350, 480, 420, 255, 255, 255);
		drawLine(0, 420, 480, 420, 255, 255, 255);
	}
	
private:
	int rows;
	int cols;
	int score; //current score
	int winscore; //score needed to win the game

protected:
	int** grid; //our level is stored as a 2d dynamic array of integers
	bool teleportColor; //used to constantly change color of teleportation blocks
};

class ghostRandom
{
public:
	
	ghostRandom()
	{
		x1 = 10;
		y1 = 10;
		x2 = 20;
		y2 = 20;
		
		og1 = 0;
		og2 = 0;
		coord1 = 0;
		coord2 = 0;
		
		direction = 4; //direction is up so ghost can get out of hole
		previousthing = -1; //previous element ghost has interacted with/ passed over

		color = false;
	}

	~ghostRandom() {
		//empty
	}

	void setcoord1(int c) {
		coord1 = c;
	}
	void setcoord2(int c) {
		coord2 = c;
	}
	void setog1(int o) {
		og1 = o;
	}
	void setog2(int o) {
		og2 = o;
	}

	int getcoord1() {
		return coord1;
	}
	int getcoord2() {
		return coord2;
	}
	int getog1() {
		return og1;
	}
	int getog2() {
		return og2;
	}

	void changeColor() {
		if (color == false)
		{
			color = true;
		}
		else
		{
			color = false;
		}
	}

	void calculateGhostCoordinates(int** grid, int rows, int cols) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j] == 3)
				{
					coord1 = i;
					coord2 = j;
					break;
				}
			}
		}
		og1 = coord1;
		og2 = coord2;
	}

	void respawn(int** grid) {
		//putting previous thing on board to where the ghost died
		grid[coord1][coord2] = previousthing;

		//putting ghost back to it's spawn
		coord1 = og1;
		coord2 = og2;
		grid[coord1][coord2] = 3;

		direction = 4; //ghost moves up to get out of hole

		//no previous thing for ghost now
		previousthing = -1;

		color = false; //color is back to green
	}

	void displayGhost(int** grid, int rows, int cols) {
		y1 = 10;
		y2 = 20;

		bool flag = false;
		int i = 0;
		while ((flag == false) && (i < rows))
		{
			x1 = 0;
			x2 = 10;
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j] == 3)
				{
					//if pacman is normal, ghost is green
					if (color == false)
					{
						drawEllipse(x1, y1, x2, y2, 0, 255, 0, 0, 255, 0);
					}

					//if pacman is energised, ghost is white
					else
					{
						drawEllipse(x1, y1, x2, y2, 255, 255, 255, 0, 0, 255);
					}


					flag = true;
					break;
				}
				x1 = x1 + 20;
				x2 = x2 + 20;
			}
			i++;
			y1 = y1 + 20;
			y2 = y2 + 20;
		}
		y1 = y1 - 20;
		y2 = y2 - 20;

		//direction is right
		if (direction == 1)
		{
			if (x1 == 30)
			{
				//do nothing
			}
			else if (previousthing == -1) {
				drawEllipse(x1 - 20, y1, x2 - 20, y2, 0, 0, 0, 0, 0, 0);
			}
			else if (previousthing == 0) {
				drawEllipse(x1 - 20, y1, x2 - 20, y2, 0, 0, 0, 160, 160, 160);
			}
		}

		//direction is left
		else if (direction == 2)
		{
			if (x1 == 30)
			{
				//do nothing
			}
			else if (previousthing == -1) {
				drawEllipse(x1 + 20, y1, x2 + 20, y2, 0, 0, 0, 0, 0, 0);
			}
			else if (previousthing == 0) {
				drawEllipse(x1 + 20, y1, x2 + 20, y2, 0, 0, 0, 160, 160, 160);
			}
		}
		
		//direction is down
		else if (direction == 3)
		{
			if (previousthing == -1) {
				drawEllipse(x1, y1 - 20, x2, y2 - 20, 0, 0, 0, 0, 0, 0);
			}
			else if (previousthing == 0) {
				drawEllipse(x1, y1 - 20, x2, y2 - 20, 0, 0, 0, 160, 160, 160);
			}
		}

		//direction is up
		else if (direction == 4)
		{
			if (previousthing == -1)
			{
				drawEllipse(x1, y1 + 20, x2, y2 + 20, 0, 0, 0, 0, 0, 0);
			}
			else if (previousthing == 0) {
				drawEllipse(x1, y1 + 20, x2, y2 + 20, 0, 0, 0, 160, 160, 160);
			}
		}
	}

	void updateXright() {
		x1 = x2 + 10;
		x2 = x2 + 20;
		coord2 = coord2 + 1;
		direction = 1;
	}

	void updateXleft() {
		x2 = x1 - 10;
		x1 = x1 - 20;
		coord2 = coord2 - 1;
		direction = 2;
	}

	void updateYdown() {
		y2 = y2 + 20;
		y1 = y1 + 20;
		coord1 = coord1 + 1;
		direction = 3;
	}

	void updateYup() {
		y1 = y1 - 20;
		y2 = y2 - 20;
		coord1 = coord1 - 1;
		direction = 4;
	}

	void findNewDirection(int cd) {
		bool flag = false;
		while (flag == false)
		{
			//srand(time(0));
			int temp = (rand() % 4) + 1;
			if (temp != cd)
			{
				direction = temp;
				flag = true;
			}
		}
	}

	void checkghost(int** grid) {
		if (direction == 1)
		{
			if ((grid[coord1][coord2 + 1] == 1) || (grid[coord1][coord2 + 1] == 5) || (grid[coord1][coord2 + 1] == 6))
			{
				findNewDirection(direction);
			}
			else if ((grid[coord1][coord2 + 1] == 0) || (grid[coord1][coord2 + 1] == -1) || (grid[coord1][coord2 + 1] == 4))
			{
				grid[coord1][coord2] = previousthing;
				previousthing = grid[coord1][coord2 + 1];
				grid[coord1][coord2 + 1] = 3;
				updateXright();
			}
			else if ((grid[coord1][coord2 + 1] == 2))
			{
				grid[coord1][coord2] = previousthing;
				previousthing = -1;
				updateXright();
			}
		}
		else if (direction == 2)
		{
			if ((grid[coord1][coord2 - 1] == 1) || (grid[coord1][coord2 - 1] == 5) || (grid[coord1][coord2 - 1] == 6))
			{
				findNewDirection(direction);
			}
			else if ((grid[coord1][coord2 - 1] == 0) || (grid[coord1][coord2 - 1] == -1) || (grid[coord1][coord2 - 1] == 4))
			{
				grid[coord1][coord2] = previousthing;
				previousthing = grid[coord1][coord2 - 1];
				grid[coord1][coord2 - 1] = 3;
				updateXleft();
			}
			else if ((grid[coord1][coord2 - 1] == 2))
			{
				grid[coord1][coord2] = previousthing;
				previousthing = -1;
				updateXleft();
			}
		}
		else if (direction == 3)
		{
			if ((grid[coord1 + 1][coord2] == 1) || (grid[coord1 + 1][coord2] == 5) || (grid[coord1 + 1][coord2] == 6))
			{
				findNewDirection(direction);
			}
			else if ((grid[coord1 + 1][coord2] == 0) || (grid[coord1 + 1][coord2] == -1) || (grid[coord1 + 1][coord2] == 4))
			{
				grid[coord1][coord2] = previousthing;
				previousthing = grid[coord1 + 1][coord2];
				grid[coord1 + 1][coord2] = 3;
				updateYdown();
			}
			else if (grid[coord1 + 1][coord2] == 2)
			{
				grid[coord1][coord2] = previousthing;
				previousthing = -1;
				updateYdown();
			}

		}
		else if (direction == 4)
		{
			if ((grid[coord1 - 1][coord2] == 1) || (grid[coord1 - 1][coord2] == 5) || (grid[coord1 - 1][coord2] == 6))
			{
				findNewDirection(direction);
			}
			else if ((grid[coord1 - 1][coord2] == 0) || (grid[coord1 - 1][coord2] == -1) || (grid[coord1 - 1][coord2] == 4))
			{
				grid[coord1][coord2] = previousthing;
				previousthing = grid[coord1 - 1][coord2];
				grid[coord1 - 1][coord2] = 3;
				updateYup();
			}
			else if (grid[coord1 - 1][coord2] == 2)
			{
				grid[coord1][coord2] = previousthing;
				previousthing = -1;
				updateYup();
			}
		}
	}

private:

	//display printing coordinates
	int x1;
	int y1;
	int x2;
	int y2;

	//original row and column in 2d array
	int og1;
	int og2;
	
	//current row and column in 2d array
	int coord1;
	int coord2;
	
	//previous object ghost has reacted with (passed over)
	int previousthing;

	//1 = right, 2 = left, 3 = down, 4 = up
	int direction;
		
	//false is green, true is white
	bool color;
};

class pacman :public maze
{
public:

	pacman()
	{
		x1 = 10;
		y1 = 10;
		x2 = 20;
		y2 = 20;
		og1 = 0;
		og2 = 0;
		coord1 = 0;
		coord2 = 0;
		lives = 3;
		direction = 0;
		status = false;
		mouthFlag = false;
		maze();
	}

	//we are going to use this constructor in the game
	//it initialises pacman to default value, and initialises maze using input from board.txt file
	pacman(string filename) :maze(filename)
	{
		x1 = 10;
		y1 = 10;
		x2 = 20;
		y2 = 20;
		og1 = 0;
		og2 = 0;
		coord1 = 0;
		coord2 = 0;
		lives = 3;
		direction = 0;
		status = false;
		mouthFlag = false;
	}

	pacman(int t1, int t2, int t3, int t4) {
		x1 = t1;
		y1 = t2;
		x2 = t3;
		y2 = t4;

		og1 = 0;
		og2 = 0;
		coord1 = 0;
		coord2 = 0;
		lives = 3;
		direction = 0;
		status = false;
		mouthFlag = false;
	}

	pacman(int t1, int t2, int t3, int t4, string filename) :maze(filename)
	{
		x1 = t1;
		y1 = t2;
		x2 = t3;
		y2 = t4;

		og1 = 0;
		og2 = 0;
		coord1 = 0;
		coord2 = 0;
		lives = 3;
		direction = 0;
		status = false;
		mouthFlag = false;
	}

	~pacman()
	{
		//empty
	}

	int getDirection() {
		return direction;
	}

	int getLives() {
		return lives;
	}

	void updateXright() {
		x1 = x2 + 10;
		x2 = x2 + 20;
		coord2 = coord2 + 1;
		direction = 1;
	}

	void updateXleft() {
		x2 = x1 - 10;
		x1 = x1 - 20;
		coord2 = coord2 - 1;
		direction = 2;
	}

	void updateYdown() {
		y2 = y2 + 20;
		y1 = y1 + 20;
		coord1 = coord1 + 1;
		direction = 3;
	}

	void updateYup() {
		y1 = y1 - 20;
		y2 = y2 - 20;
		coord1 = coord1 - 1;
		direction = 4;
	}

	void checkpacman(int nd) {

		if (nd == 1)
		{
			//eating pill
			if (grid[coord1][coord2 + 1] == 0)
			{
				grid[coord1][coord2] = -1;
				grid[coord1][coord2 + 1] = 2;
				updateXright();
				incrementScore();
				//update score here by 1
			}

			//passing over empty space
			else if (grid[coord1][coord2 + 1] == -1)
			{
				grid[coord1][coord2] = -1;
				grid[coord1][coord2 + 1] = 2;
				updateXright();
			}
			
			//eating energiser
			else if (grid[coord1][coord2 + 1] == 4)
			{
				grid[coord1][coord2] = -1;
				grid[coord1][coord2 + 1] = 2;
				updateXright();
				//we only change color of ghost, when energiser eaten, to white when ghost color is green
				if (status == false)
				{
					g.changeColor();
				}
				status = true;
			}

			//teleporting from right to left
			else if (grid[coord1][coord2 + 1] == 5)
			{
				grid[coord1][coord2] = -1;
				for (int i = 0; i < getRows(); i++)
				{
					for (int j = 0; j < getCols(); j++)
					{
						if (grid[i][j] == 6)
						{
							coord2 = j + 1;
							grid[coord1][coord2] = 2;
							direction = 1;
						}
					}
				}
				displayBoard();
			}
		}

		else if (nd == 2)
		{
			if (grid[coord1][coord2 - 1] == 0)
			{
				grid[coord1][coord2] = -1;
				grid[coord1][coord2 - 1] = 2;
				incrementScore();
				updateXleft();
			}
			else if (grid[coord1][coord2 - 1] == -1)
			{
				grid[coord1][coord2] = -1;
				grid[coord1][coord2 - 1] = 2;
				updateXleft();
			}
			else if (grid[coord1][coord2 - 1] == 4) {
				grid[coord1][coord2] = -1;
				grid[coord1][coord2 - 1] = 2;
				updateXleft();
				//we only change color of ghost, when energiser eaten, to white when ghost color is green
				if (status == false)
				{
					g.changeColor();
				}
				status = true;
			}
			//teleporting from left to right
			else if (grid[coord1][coord2 - 1] == 6)
			{
				grid[coord1][coord2] = -1;
				for (int i = 0; i < getRows(); i++)
				{
					for (int j = 0; j < getCols(); j++)
					{
						if (grid[i][j] == 5)
						{
							coord2 = j - 1;
							grid[coord1][coord2] = 2;
							direction = 2;
						}
					}
				}

				displayBoard();
			}
		}
		else if (nd == 3)
		{
			if (grid[coord1 + 1][coord2] == 0)
			{
				grid[coord1][coord2] = -1;
				grid[coord1 + 1][coord2] = 2;
				incrementScore();
				updateYdown();
			}
			else if (grid[coord1 + 1][coord2] == -1)
			{
				grid[coord1][coord2] = -1;
				grid[coord1 + 1][coord2] = 2;
				updateYdown();
			}
			else if (grid[coord1 + 1][coord2] == 4)
			{
				grid[coord1][coord2] = -1;
				grid[coord1 + 1][coord2] = 2;
				updateYdown();

				//we only change color of ghost, when energiser eaten, to white when ghost color is green
				if (status == false)
				{
					g.changeColor();
				}
				status = true;
			}
		}
		else if (nd == 4)
		{
			if (grid[coord1 - 1][coord2] == 0)
			{
				grid[coord1][coord2] = -1;
				grid[coord1 - 1][coord2] = 2;
				incrementScore();
				updateYup();
			}
			else if (grid[coord1 - 1][coord2] == -1)
			{
				grid[coord1][coord2] = -1;
				grid[coord1 - 1][coord2] = 2;
				updateYup();
			}
			else if (grid[coord1 - 1][coord2] == 4)
			{
				grid[coord1][coord2] = -1;
				grid[coord1 - 1][coord2] = 2;
				updateYup();
				//we only change color of ghost, when energiser eaten, to white when ghost color is green
				if (status == false)
				{
					g.changeColor();
				}
				status = true;
			}
		}
		else
		{
			//do nothing
		}
		
		changeTeleportColor();

		g.checkghost(grid);
	}

	void calculateCoordinates() {
		for (int i = 0; i < getRows(); i++)
		{
			for (int j = 0; j < getCols(); j++)
			{
				if (grid[i][j] == 2)
				{
					coord1 = i;
					coord2 = j;
					break;
				}
			}
		}

		og1 = coord1;
		og2 = coord2;

		g.calculateGhostCoordinates(grid, getRows(), getCols());
	}

	void displayPacMan() {

		displayStats(getLives());

		y1 = 10;
		y2 = 20;

		bool flag = false;
		int i = 0;
		while ((flag == false) && (i < getRows()))
		{
			x1 = 0;
			x2 = 10;
			for (int j = 0; j < getCols(); j++)
			{
				if (grid[i][j] == 2)
				{
					//if pacman energised
					if (status == true)
					{
						//if mouth closed
						if (mouthFlag == true)
						{
							drawEllipse(x1, y1, x2, y2, 255, 0, 50, 255, 0, 50);
							mouthFlag = false;
						}
						//if mouth open
						else
						{
							drawEllipse(x1, y1, x2, y2, 255, 0, 50, 0, 0, 0);
							mouthFlag = true;
						}
					}

					//if pacman not energised
					else
					{
						//if mouth closed
						if (mouthFlag == true)
						{
							drawEllipse(x1, y1, x2, y2, 255, 255, 0, 255, 255, 0);
							mouthFlag = false;
						}
						//if mouth open
						else
						{
							drawEllipse(x1, y1, x2, y2, 255, 255, 0, 0, 0, 0);
							mouthFlag = true;
						}
					}

					flag = true;
					break;
				}
				//updating x coordinates
				x1 = x1 + 20;
				x2 = x2 + 20;
			}

			i++;

			//updating y coordinates
			y1 = y1 + 20;
			y2 = y2 + 20;
		}

		y1 = y1 - 20;
		y2 = y2 - 20;

		//direction is right
		if (direction == 1)
		{
			drawEllipse(x1 - 20, y1, x2 - 20, y2, 0, 0, 0, 0, 0, 0);
		}
		//direction is left
		else if (direction == 2)
		{
			drawEllipse(x1 + 20, y1, x2 + 20, y2, 0, 0, 0, 0, 0, 0);
		}
		//if direction is down
		else if (direction == 3)
		{
			drawEllipse(x1, y1 - 20, x2, y2 - 20, 0, 0, 0, 0, 0, 0);
		}
		//if direction is up
		else if (direction == 4)
		{
			drawEllipse(x1, y1 + 20, x2, y2 + 20, 0, 0, 0, 0, 0, 0);
		}

		//displaying teleport rectangles black again
		drawRectangle(10 + 10, 180 + 5, 10 + 30, 180 + 25, 150, 150, 255, 230, 0, 230);
		drawRectangle(430 + 10, 180 + 5, 430 + 30, 180 + 25, 150, 150, 255, 230, 0, 230);

		//displaying ghost
		g.displayGhost(grid, getRows(), getCols());
	}

	void checkcolision() {
		//if pacman and ghost indexes are same in grid array
		if (coord1 == g.getcoord1()) {
			if (coord2 == g.getcoord2())
			{
				//if pacman is energised, then ghost dies and respawns
				if (status == true)
				{
					g.respawn(grid);
					status = false;

					int t = 100;
					t = t + getWinScore();
					setWinScore(t);

					t = 100;
					t = t + getScore();
					setScore(t);
				}

				//if pacman is normal, then pacman dies and respawns
				else
				{
					lives = lives - 1;

					grid[coord1][coord2] = -1;

					//sending pacman to it's spawn point
					coord1 = og1;
					coord2 = og2;
					grid[coord1][coord2] = 2;

					//pacman unmoving
					direction = 0;
				}
			}
		}
	}

private:
	int x1, y1, x2, y2;
	int coord1, coord2;
	int og1, og2; //original indexes in 2d array
	int direction;
	int lives;
	bool status; //energised or not
	bool mouthFlag; //pacman pouth open or closed

	//ghost has composition relation with pacman class
	ghostRandom g;
};

void startgame() {
	//Initialising
	int w = 0, h = 0;
	getWindowDimensions(w, h);

	cls();
	showConsoleCursor(false);

	pacman p("board.txt");

	//calculating coordinates of pacman on screen
	p.calculateCoordinates();

	//calculating number of pills on level
	p.calculateWinScore();

	bool flag1 = false;

	cls();

	while (flag1 == false)
	{
		delay(100);

		//if all pills eaten, we exit loop
		if ((p.getScore() >= p.getWinScore()) || (p.pillsLeft() == 0))
		{
			flag1 = true;
			break;
		}

		//if lives are 0, we exit loop
		if (p.getLives() == 0)
		{
			flag1 = true;
			break;
		}

		char c = ' ';
		
		while (_kbhit() == true) {
			c = _getch();

			//nd means new direction
			//basically nd is the direction key hit by user
			int nd = 0;

			if ((c == 'i') || (c == 'I') || (c == 'w') || (c == 'W'))
			{
				nd = 4;
				p.checkpacman(nd);
				p.displayPacMan();
			}
			else
			{
				if ((c == 'k') || (c == 'K') || (c == 's') || (c == 'S'))
				{
					nd = 3;
					p.checkpacman(nd);
					p.displayPacMan();
				}
				else
				{
					if ((c == 'j') || (c == 'J') || (c == 'a') || (c == 'A'))
					{
						nd = 2;
						p.checkpacman(nd);
						p.displayPacMan();
					}
					else
					{
						if ((c == 'l') || (c == 'L') || (c == 'd') || (c == 'D'))
						{
							nd = 1;
							p.checkpacman(nd);
							p.displayPacMan();
						}
						else
						{
							if ((c == 'x') || (c == 'X'))
							{
								flag1 = true;
							}
							else
							{
								if ((c == 'p') || (c == 'P'))
								{
									bool pauseFlag = true;
									char p;

									while (pauseFlag == true)
									{
										p = _getch();
										if ((p == 'p') || (p == 'P'))
										{
											pauseFlag = false;
										}
									}
								}
							}
						}
					}
				}
			}
			delay(100);
		}
		delay(50);

		p.checkpacman(p.getDirection());
		p.checkcolision();
		p.displayPacMan();
		p.displayBoard();
	}

	cls();
	showConsoleCursor(true);

	gotoxy(0, 0);

	//losing condition
	if (p.getLives() <= 0)
	{
		cout << "You Lost!" << endl;
	}
	else
	{
		//winning condition
		if ((p.getScore() >= p.getWinScore()) || (p.pillsLeft() == 0))
		{
			cout << "You Win!" << endl;
			cout << endl;
			cout << "Your Score: " << p.getScore() << endl;
			cout << endl;
		}
	}
}

int main() {
	
	bool flag1 = false;

	while (flag1 == false)
	{
		cout << "START: S" << endl;
		cout << "EXIT: X" << endl;

		char op;
		op = _getch();

		if ((op == 'x') || (op == 'X'))
		{
			flag1 = true;
		}
		else
		{
			if ((op == 's') || (op == 'S'))
			{
				startgame();
				flag1 = true;
			}
			else
			{
				cout << "Enter correct option!" << endl;
			}
		}
	}

	return 0;
	system("pause");
}