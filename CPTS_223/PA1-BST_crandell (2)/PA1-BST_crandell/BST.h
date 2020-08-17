/*
* Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
*
* Simple integer keys and basic operations
*
* Aaron Crandall - 2016 - Added / updated:
*  * Inorder, Preorder, Postorder printouts
*  * Stubbed in level order printout
*
*/

// used logic and code from the github above
#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <queue>
using namespace std;

/*
*  Node datastructure for single tree node
*/
template <class T>
struct Node {

public:

	Node()
	{
		value = 0;
		left = NULL;
		right = NULL;
	}

	Node(T vals)
	{
		this->value = vals;
		left = NULL;
		right = NULL;
	}

	T value;
	Node *left;
	Node *right;

};


/*
* Binary Search Tree (BST) class implementation
*/
template <class T>
class BST {

private:
	Node<T> *root;

	void addHelper(Node<T> *root, T vals) {

		Node<T> *pcur;
		pcur = root;

		if (pcur->value > vals) {
			if (!pcur->left) {
				pcur->left = new Node<T>(vals);
			}
			else {
				addHelper(pcur->left, vals);
			}
		}
		else {
			if (!pcur->right) {
				pcur->right = new Node <T>(vals);
			}
			else {
				addHelper(pcur->right, vals);
			}

		}
	}

	void printPreOrder(Node<T> *root) {
		if (!root) return;

		printf("%d", root->value);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}

	int countHelper(Node<T> *root) {

		if (!root) return 0;
		else return 1 + countHelper(root->left) + countHelper(root->right);
	}

	int heightHelper(Node<T> *root) {
		if (!root) return 0;
		else return 1 + max(heightHelper(root->left), heightHelper(root->right));
	}

	void printMaxPathHelper(Node<T> *root) {
		if (!root) return;
		cout << root->value << ' ';
		if (heightHelper(root->left) > heightHelper(root->right)) {
			printMaxPathHelper(root->left);
		}
		else {
			printMaxPathHelper(root->right);
		}
	}


public:

	BST()
	{
		root = NULL;
	}


	void add(T vals) {

		if (root) {
			this->addHelper(this->root, vals);
		}
		else {
			this->root = new Node<T>(vals);
		}
	}

	void print() {
		this->printPreOrder(this->root);
	}

	int nodesCount() {

		int count = countHelper(this->root);
		return count;
	}

	int height() {

		return heightHelper(this->root);

	}
};

#endif
