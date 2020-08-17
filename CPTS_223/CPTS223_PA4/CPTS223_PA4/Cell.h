#pragma once

#ifndef CELL_H
#define CELL_H

#include <vector>
#include <stdexcept>
#include <math.h>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

class Cell
{

private:

	int index;

	bool northWall;
	bool eastWall;
	bool southWall;
	bool westWall;

	bool northBorder;
	bool eastBorder;
	bool southBorder;
	bool westBorder;

public:

	Cell()
	{
		northWall = true;
		eastWall = true;
		southWall = true;
		westWall = true;

		northBorder = false;
		eastBorder = false;
		southBorder = false;
		westBorder = false;
	}

	void removeWall(int wall) //0 = north, 1 = east, 2 = south, 3 = west
	{
		switch (wall)
		{
		case 0:
			northWall = false;
			return;
		case 1:
			eastWall = false;
			return;
		case 2:
			southWall = false;
			return;
		case 3:
			westWall = false;
			return;
		}
	}

	bool checkWall(int wall)
	{
		switch (wall)
		{
		case 0: return northWall;
		case 1: return eastWall;
		case 2: return southWall;
		case 3: return westWall;
		}
	}

	void setBorder(int wall) //0 = north, 1 = east, 2 = south, 3 = west
	{
		switch (wall)
		{
		case 0:
			northBorder = true;
			break;
		case 1:
			eastBorder = true;
			break;
		case 2:
			southBorder = true;
			break;
		case 3:
			westBorder = true;
			break;
		}
	}

	bool checkBorder(int wall)
	{
		switch (wall)
		{
		case 0: return northBorder;
		case 1: return eastBorder;
		case 2: return southBorder;
		case 3: return westBorder;
		}
	}

	void setIndex(int num)
	{
		index = num;
	}

	int getIndex()
	{
		return index;
	}

};

#endif