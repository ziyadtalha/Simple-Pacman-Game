# Simple-Pacman-Game
OOP, C++, MyGraphics.h

Controls: i,j,k,l for movement, s to start game, x to quit.

Level is loaded as a 2d array of integers from board.txt file.
There is a single level.

Level contains wals, teleporters, pills, and energiser pills.
Pills are small white circles, energisers are larger circles.
The level has four energisers.

There is a single ghost ( represented by a green circle).
This ghost moves randomly around the level; only changing direction when it collides with a wall.

Pacman is the yellow circle.
The mouth of pacman opens and closes constantly :)
When Pacman consumes an energiser, it stays active until the ghost is eaten.

Eating the ghost increases score by 100.

Teleport tunnels are given at the left and right sides of the screen.

Game ends when either lives are used up or all dots are eaten.

Key for board.txt:
0 = Pill
1 = Wall
2 = Pacman
3 = Ghost
4 = Energiser
5 = Right Side Teleporter
6 = Left Side Teleporter

The first line of board.txt defines the dimensions of the level.

Note for students:
I do not support copying this project and rebranding it as your own to submit for an assignment or project; doing so is unethical as it counts as cheating.
Also not that this is not the best iteration of a Pacman game made in C++.
There are design and coding standards that this project lacks in.
