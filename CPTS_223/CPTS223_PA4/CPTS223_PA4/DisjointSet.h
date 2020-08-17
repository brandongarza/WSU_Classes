#pragma once

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>
#include <stdexcept>
#include <math.h>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

class DisjointSet
{
private:
	vector<int> set;
	int elements;
	int numsets;

public:

	DisjointSet()
	{

	}

	explicit DisjointSet(int numElements)
	{
		for (int i = 0; i < numElements; i++)
		{
			set.push_back(-1);
		}
		elements = numElements;
		numsets = numElements;
	}

	void unionSet(int data1, int data2)
	{
		int x = findSet(data1);
		int y = findSet(data2);

		if (set[y] < set[x])
		{
			set[x] = y;
		}
		else
		{
			if (set[x] == set[y])
			{
				--set[x];
			}
			set[y] = x;
		}

		numsets--;
	}

	int findSet(int data)
	{
		if (set[data] < 0)
		{
			return data;
		}
		else
		{
			return set[data] = findSet(set[data]);
		}
	}

	int getNumOfSets()
	{
		return numsets;
	}

	int getNumOfElements()
	{
		return elements;
	}

};

#endif