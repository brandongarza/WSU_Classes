#pragma once

#ifndef MAZEBUILDERLARGE_H
#define MAZEBUILDERLARGE_H

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

class MazeBuilderLarge
{

private:
	static const int x = 50;
	static const int y = 100;

public:

	Cell LargeMaze[x][y];

	MazeBuilderLarge()
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
				LargeMaze[i][j].setIndex(indexNumber);
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
			LargeMaze[0][i].setBorder(0);
		}
		//South Border
		for (int i = 0; i < y; i++)
		{
			LargeMaze[x - 1][i].setBorder(2);
		}
		//East Border
		for (int i = 0; i < x; i++)
		{
			LargeMaze[i][y - 1].setBorder(1);
		}
		//West Border
		for (int i = 0; i < x; i++)
		{
			LargeMaze[i][0].setBorder(3);
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

		while (set.getNumOfSets() > 1)  // repeat until there is only one set 
		{
			int randRow = (rand() % x);
			int randColumn = (rand() % y);
			int randomWall = (rand() % 4);

			// index number of the randomly selected cell
			int index = LargeMaze[randRow][randColumn].getIndex();

			switch (randomWall)
			{
				// if the randomly selected cell wall is not a border wall - 
				// destroy the wall and the associated wall of the neighbor cell.

			case 0:       // north wall
				if (LargeMaze[randRow][randColumn].checkBorder(0) == false)
				{
					if (set.findSet(index) != set.findSet((index - y)))
					{
						set.unionSet(index, (index - y));
						LargeMaze[randRow][randColumn].removeWall(0);
						LargeMaze[(randRow - 1)][randColumn].removeWall(2);
					}
				}
				break;

			case 1:             // east wall
				if (LargeMaze[randRow][randColumn].checkBorder(1) == false)
				{
					if (set.findSet(index) != set.findSet((index + 1)))
					{
						set.unionSet(index, (index + 1));
						LargeMaze[randRow][randColumn].removeWall(1);
						LargeMaze[randRow][(randColumn + 1)].removeWall(3);
					}
				}
				break;

			case 2:             // south wall
				if (LargeMaze[randRow][randColumn].checkBorder(2) == false)
				{
					if (set.findSet(index) != set.findSet((index + y)))
					{
						set.unionSet(index, (index + y));
						LargeMaze[randRow][randColumn].removeWall(2);
						LargeMaze[(randRow + 1)][randColumn].removeWall(0);
					}

				}
				break;

			case 3:             // west wall
				if (LargeMaze[randRow][randColumn].checkBorder(3) == false)
				{
					if (set.findSet(index) != set.findSet((index - 1)))
					{
						set.unionSet(index, ((index - 1)));
						LargeMaze[randRow][randColumn].removeWall(3);
						LargeMaze[randRow][(randColumn - 1)].removeWall(1);
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

		for (int i = 0; i < getRows(); i++)
		{
			for (int j = 0; j < getColumns(); j++)
			{
				if (LargeMaze[i][j].checkWall(0))
				{
					int x1 = i * 25 + 100;
					int x2 = (i + 1) * 25 + 100;
					int y1 = j * 25 + 50;
					int y2 = j * 25 + 50;

					file << "<line x1 = \"" << x1 << "\" x2 = \"" << x2 << "\" y1 = \"" << y1 << "\" y2 = \"" << y2 << "\" style = \"stroke:black; stroke-width:2\" />" << endl;
				}
				if (LargeMaze[i][j].checkWall(1))
				{
					int x1 = (i + 1) * 25 + 100;
					int x2 = (i + 1) * 25 + 100;
					int y1 = j * 25 + 50;
					int y2 = (j + 1) * 25 + 50;

					file << "<line x1 = \"" << x1 << "\" x2 = \"" << x2 << "\" y1 = \"" << y1 << "\" y2 = \"" << y2 << "\" style = \"stroke:black; stroke-width:2\" />" << endl;
				}
				if (LargeMaze[i][j].checkWall(2))
				{
					int x1 = i * 25 + 100;
					int x2 = (i + 1) * 25 + 100;
					int y1 = (j + 1) * 25 + 50;
					int y2 = (j + 1) * 25 + 50;

					file << "<line x1 = \"" << x1 << "\" x2 = \"" << x2 << "\" y1 = \"" << y1 << "\" y2 = \"" << y2 << "\" style = \"stroke:black; stroke-width:2\" />" << endl;
				}
				if (LargeMaze[i][j].checkWall(3))
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

		file.close();

		return 0;
	}

};

#endif