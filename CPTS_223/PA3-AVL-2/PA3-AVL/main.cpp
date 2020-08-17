/*
*  main.cpp - AVL Tree testing
*   Aaron Crandall - 2017
*   Educational use only
*/


#include <iostream>
#include <cstdlib>
#include <string.h>
#include "AvlTree.h"
#include "AvlTreeTesting.h"
using namespace std;

/*
*  Main function for test or use
*/
int main(int argc, char* argv[])
{
	int retState = 0;
	// Note: If you call this program like this: ./avltree --test
	//  it will call the test function
	if (argc > 1 && !strcmp(argv[1], "--test"))
	{
		cout << " [x] Running in test mode. " << endl;

		bool withFuzzing = false;
		withFuzzing = (argc > 2 && !strcmp(argv[2], "--withFuzzing")); // Test for fuzzing option

		retState = avlTreeTests(withFuzzing);          // From AvlTreeTesting.h
		cout << " [x] Program complete. " << endl;
	}
	else
	{
		cout << " [x] Running in normal mode. " << endl;
		cout << "  [!] Nothing to do in normal mode so here's a helicopter: " << endl;
		cout << "   ___.___\n     (_]===*\n     o 0" << endl;
		cout << endl << " You should probably run 'make test' to test your program. " << endl;
		cout << "  This program also has a fuzzing test with 'make bigtest' to test your program. " << endl;
	}
	return(retState);
}
