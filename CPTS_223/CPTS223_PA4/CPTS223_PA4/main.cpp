#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <Windows.h>

#include "MazeBuilderSmall.h"
#include "MazeBuilderLarge.h"
#include "Cell.h"
#include "DisjointSet.h"

using namespace std;

int main(int argc, char* argv[])
{
	bool is_small_maze = false;
	bool is_big_maze = false;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "--maze"))
		{
			cout << " [x] Building 20x20 maze. " << endl;
			is_small_maze = true;
		}

		else if (!strcmp(argv[i], "--bigmaze"))
		{
			cout << " [x] Buidling 50x100 maze. " << endl;
			is_big_maze = true;
		}
	}
	
	if (is_small_maze)
	{
		MazeBuilderSmall Maze;
		Maze.BuildMaze();
	}

	else if (is_big_maze)
	{
		MazeBuilderLarge Maze;
		Maze.BuildMaze();
	}

	return 0;
}