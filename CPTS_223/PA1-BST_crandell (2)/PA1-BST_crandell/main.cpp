/*
* Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
*
* Simple integer keys and basic operations
* Now also doing testing & height calculations
*
* Aaron Crandall - 2016 - Added / updated:
*  * Inorder, Preorder, Postorder printouts
*  * Stubbed in level order printout
*  * Also doing height calculations
*
*/
//Updated and built by adithiya vivekanandan
//collaborated with Austin Kappl and Farzan Ghodsi

#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
#include "BST.h"
#include "TestData.h"
using namespace std;

/*
*  Interface to run all tests if --test is passed on command line
*/
void runTests() {
	cout << " [x] Running tests. " << endl;
	TestData *testing = new TestData();			// Create object with testing data and interfaces

	BST<int> *bst_test = new BST<int>;

	/* Should make a tree like this:
	10
	5          14
	1      7           17
	19
	18

	*/


	int testval = testing->get_next_minitest();
	while (testval >= 0) {
		bst_test->add(testval);
		testval = testing->get_next_minitest();
	}
	cout << " [x] Should print out in pre order: 10 5 1 7 14 17 19 18 " << endl;
	cout << " [x] Resulting print out test:      ";
	bst_test->print();
	cout << endl;

	cout << " [x] Should print a tree height of  : 5" << endl;
	cout << " [x] Currently calculating height of: ";
	cout << bst_test->height();
	cout << endl;
}








/*
* Generate the CSV file for the project output here
*/
void genCSV() {

	BST<int> *bst_sorted = new BST<int>;
	BST<int> *bst_balanced = new BST<int>;
	BST<int> *bst_scram1 = new BST<int>;
	BST<int> *bst_scram2 = new BST<int>;
	BST<int> *bst_scram3 = new BST<int>;
	BST<int> *bst_scram4 = new BST<int>;
	BST<int> *bst_scram5 = new BST<int>;


	ofstream myproj;
	myproj.open("outputdata.csv");


	cout << " [x] Generating CSV output file. " << endl;
	cout << " [!!!] UNIMPLEMENTED - Need to generate the CSV file based on the tree height growth." << endl;

	TestData *Tests = new TestData();			// Create object with testing data and interfaces

	vector< vector<int> > node_Heights(7);

	int inorder = Tests->get_next_sorted();

	while (inorder >= 0) {
		bst_sorted->add(inorder);
		inorder = Tests->get_next_sorted();
		node_Heights[0].push_back(bst_sorted->height());
	}

	inorder = Tests->get_next_balanced();
	while (inorder >= 0) {
		bst_balanced->add(inorder);
		inorder = Tests->get_next_balanced();
		node_Heights[1].push_back(bst_balanced->height());
	}


	inorder = Tests->get_next_scrambled(0);
	while (inorder >= 0) {
		bst_scram1->add(inorder);
		inorder = Tests->get_next_scrambled(0);
		node_Heights[2].push_back(bst_scram1->height());
	}


	inorder = Tests->get_next_scrambled(1);
	while (inorder >= 0) {
		bst_scram2->add(inorder);
		inorder = Tests->get_next_scrambled(1);
		node_Heights[3].push_back(bst_scram2->height());
	}


	inorder = Tests->get_next_scrambled(2);
	while (inorder >= 0) {
		bst_scram3->add(inorder);
		inorder = Tests->get_next_scrambled(2);
		node_Heights[4].push_back(bst_scram3->height());
	}

	inorder = Tests->get_next_scrambled(3);
	while (inorder >= 0) {
		bst_scram4->add(inorder);
		inorder = Tests->get_next_scrambled(3);
		node_Heights[5].push_back(bst_scram4->height());
	}
	inorder = Tests->get_next_scrambled(4);
	while (inorder >= 0) {
		bst_scram5->add(inorder);
		inorder = Tests->get_next_scrambled(4);
		node_Heights[6].push_back(bst_scram5->height());
	}


	// make a file: OutputData-BST.csv
	// make 7 trees (sorted, balanced, scrambled[0..4])
	// fill trees with data from TestData
	//  -- as you fill, get the heights and output to CSV file: log_2 N, height sorted, height balanced, height scrambled[0..4]
	//  -- fill until the get_next_* functions return -1


	myproj << "N,Log_2(N),Sorted, Scrambled #0,Scrambled #1,Scrambled #2,Scrambled #3,Scrambled #4";
	//data
	//collaborated with austin kappl
	for (size_t i = 0; i < node_Heights[0].size(); i++)
	{
		myproj << i + 1 << ",";
		for (int j = 0; j<7; j++)
		{
			myproj << node_Heights[j][i];
			if (j != 6)
			{
				myproj << ",";
			}
			else {
				myproj << "\n";
			}
		}
	}

	myproj.close();

}


/*
*   Main function for execution
*/
int main(int argc, char* argv[]) {
	//	if (argc > 1 && !strcmp(argv[1], "--test"))
	//	{
	//		cout << " [x] Program in test mode, doing simple tests. " << endl;
	//		runTests();  // testing should just do a simple tree insert set and search
	//	}
	//	else
	//	{
	cout << " [x] Program built and running in full CSV generation mode. " << endl;
	genCSV();
	//	}
	return 0;
}
//Chat Conversation End
