#pragma once

#ifndef MAZEBUILDERSMALL_H
#define MAZEBUILDERSMALL_H

#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <Windows.h>

#include "Cell.h"
#include "DisjointSet.h"

using namespace std;

class MazeBuilderSmall
{

private:
	static const int x = 20;
	static const int y = 20;

public:

	Cell SmallMaze[x][y];

	MazeBuilderSmall()
	{
		setIndices();
		setBorders();
	}

	void setIndices()
	{
		int indexNumber = 0;

		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				SmallMaze[i][j].setIndex(indexNumber);
				indexNumber++;
			}
		}
		return;
	}

	void setBorders()
	{
		//North Border
		for (int i = 0; i < y; i++)
		{
			SmallMaze[0][i].setBorder(0);
		}
		//South Border
		for (int i = 0; i < y; i++)
		{
			SmallMaze[x - 1][i].setBorder(2);
		}
		//East Border
		for (int i = 0; i < x; i++)
		{
			SmallMaze[i][y - 1].setBorder(1);
		}
		//West Border
		for (int i = 0; i < x; i++)
		{
			SmallMaze[i][0].setBorder(3);
		}
		return;
	}

	int getMazeSize()
	{
		return x*y;
	}

	int getRows()
	{
		return x;
	}

	int getColumns()
	{
		return y;
	}

	int BuildMaze()
	{
		fstream file;
		file.open("BrandonsMaze.svg");

		int elements = getMazeSize();
		DisjointSet set(elements);

		srand(time(NULL));// remaining  

		setBorders();

		while (set.getNumOfSets() > 1)  // repeat until there is only one set 
		{
			int randRow = (rand() % getRows());
			int randColumn = (rand() % getColumns());
			int randomWall = (rand() % 4);

			// index number of the randomly selected cell
			int index = SmallMaze[randRow][randColumn].getIndex();

			switch (randomWall)
			{
				// if the randomly selected cell wall is not a border wall - 
				// destroy the wall and the associated wall of the neighbor cell.

			case 0:       // north wall
				if (SmallMaze[randRow][randColumn].checkBorder(0) == false)
				{
					if (set.findSet(index) != set.findSet((index - getColumns())))
					{
						set.unionSet(index, (index - getColumns()));
						SmallMaze[randRow][randColumn].removeWall(0);
						SmallMaze[(randRow - 1)][randColumn].removeWall(2);
					}
				}
				break;

			case 1:             // east wall
				if (SmallMaze[randRow][randColumn].checkBorder(1) == false)
				{
					if (set.findSet(index) != set.findSet((index + 1)))
					{
						set.unionSet(index, (index + 1));
						SmallMaze[randRow][randColumn].removeWall(1);
						SmallMaze[randRow][(randColumn + 1)].removeWall(3);
					}
				}
				break;

			case 2:             // south wall
				if (SmallMaze[randRow][randColumn].checkBorder(2) == false)
				{
					if (set.findSet(index) != set.findSet((index + getColumns())))
					{
						set.unionSet(index, (index + getColumns()));
						SmallMaze[randRow][randColumn].removeWall(2);
						SmallMaze[(randRow + 1)][randColumn].removeWall(0);
					}

				}
				break;

			case 3:             // west wall
				if (SmallMaze[randRow][randColumn].checkBorder(3) == false)
				{
					if (set.findSet(index) != set.findSet((index - 1)))
					{
						set.unionSet(index, ((index - 1)));
						SmallMaze[randRow][randColumn].removeWall(3);
						SmallMaze[randRow][(randColumn - 1)].removeWall(1);
					}
				}
				break;
			}
		}

		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
		file << "<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\" " << endl;
		file << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
		file << "<svg xmlns = \"http://www.w3.org/2000/svg\">" << endl;

		file << "<text x = \"35\" y = \"70\" font-family = \"Arial\" font-size = \"25\" fill = \"black\" >" << endl;
		file << "Start" << endl;
		file << "</text>" << endl;
		file << "<text x = \"607\" y = \"547\" font-family = \"Arial\" font-size = \"25\" fill = \"black\" >" << endl;
		file << "End" << endl;
		file << "</text>" << endl;

		for (int i = 0; i < getRows(); i++)
		{
			for (int j = 0; j < getColumns(); j++)
			{
				if (SmallMaze[i][j].checkWall(0))
				{
					int x1 = i * 25 + 100;
					int x2 = (i + 1)* 25 + 100;
					int y1 = j * 25 + 50;
					int y2 = j * 25 + 50;

					file << "<line x1 = \"" << x1 << "\" x2 = \"" << x2 << "\" y1 = \"" << y1 << "\" y2 = \"" << y2 << "\" style = \"stroke:black; stroke-width:2\" />" << endl;
				}
				if (SmallMaze[i][j].checkWall(1))
				{
					int x1 = (i + 1)* 25 + 100;
					int x2 = (i + 1)* 25 + 100;
					int y1 = j * 25 + 50;
					int y2 = (j + 1) * 25 + 50;

					file << "<line x1 = \"" << x1 << "\" x2 = \"" << x2 << "\" y1 = \"" << y1 << "\" y2 = \"" << y2 << "\" style = \"stroke:black; stroke-width:2\" />" << endl;
				}
				if (SmallMaze[i][j].checkWall(2))
				{
					int x1 = i * 25 + 100;
					int x2 = (i + 1)* 25 + 100;
					int y1 = (j + 1) * 25 + 50;
					int y2 = (j + 1) * 25 + 50;

					file << "<line x1 = \"" << x1 << "\" x2 = \"" << x2 << "\" y1 = \"" << y1 << "\" y2 = \"" << y2 << "\" style = \"stroke:black; stroke-width:2\" />" << endl;
				}
				if (SmallMaze[i][j].checkWall(3))
				{
					int x1 = i * 25 + 100;
					int x2 = i * 25 + 100;
					int y1 = j * 25 + 50;
					int y2 = (j + 1) * 25 + 50;

					file << "<line x1 = \"" << x1 << "\" x2 = \"" << x2 << "\" y1 = \"" << y1 << "\" y2 = \"" << y2 << "\" style = \"stroke:black; stroke-width:2\" />" << endl;
				}
			}
		}

		file << "</svg>" << endl;

		return 0;
	}

};

#endif