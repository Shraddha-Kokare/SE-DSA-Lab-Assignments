//============================================================================
// Name        : AVL_Tree.cpp
// Author      : ShraddhaKokare
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#define SPACE 10
using namespace std;

class Node
{
public:
	int key;
	string value;
	Node *left;
	Node *right;
	int height;
};

class AVLTree
{
public:
	Node *root;
	AVLTree()
	{
		root = NULL;
	}
	int getHeight(struct Node *n);
	Node *createNode(int key, string val);
	int getBalanceFactor(Node *n);
	Node *rightRotate(Node *y);
	Node *leftRotate(Node *x);
	Node *insert(Node *root, int key, string value);
	void print2D(Node *root, int space);
	Node* update(Node *root,int key, string value);
	void deleteKey(int key);
	void search(int key);

	// Node* insert(Node* root,int key,string value)
	// {

	// 	if(root==NULL)
	// 	{
	// 		return (createNode(key,value));
	// 	}
	// 	if(key<root->key)
	// 	{
	// 		root->left=insert(root->left,key,value);
	// 	}
	// 	else if(key>root->key)
	// 	{
	// 		root->right=insert(root->right,key,value);
	// 	}
	// 	cout<<"\n\t\tInserting key = "<<key;
	// 	return root;

	// 	root->height=1+max(getHeight(root->left),getHeight(root->right));
	// 	cout<<"\n\t\tkey = "<<root->key<<"\t\theight = "<<root->height;
	// 	int bf=getBalanceFactor(root);

	// 	// depending upon the balance factor below are the 4 cases

	// 	// left left case
	// 	// right right case
	// 	// left right case
	// 	// right left case
	// }
};

int AVLTree::getHeight(struct Node *n)
{
	if (n == NULL)
		return -1;
	else
		return n->height;
}

Node *AVLTree::createNode(int key, string val)
{
	Node *newNode = new Node();
	newNode->key = key;
	newNode->value = val;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 0;

	return newNode;
}

int AVLTree::getBalanceFactor(Node *n)
{
	if (n == NULL)
		return 0;
	else
	{
		return (getHeight(n->left) - getHeight(n->right));
	}
}

Node *AVLTree::rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

	return x;
}

Node *AVLTree::leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;

	y->left = x;
	x->right = T2;

	y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

	return y;
}

Node *AVLTree::insert(Node *root, int key, string value)
{
	if (root == NULL)
	{
		cout << "\n\t\tInserting key = " << key;
		return createNode(key, value);
	}

	if (key < root->key)
	{
		root->left = insert(root->left, key, value);
	}
	else if (key > root->key)
	{
		root->right = insert(root->right, key, value);
	}
	else
	{
		// Duplicate keys not allowed
		return root;
	}

	// Update height
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	cout << "\n\t\tkey = " << root->key << "\t\theight = " << root->height;

	int bf = getBalanceFactor(root);

	// Left Left Case
	if (bf > 1 && key < root->left->key)
		return rightRotate(root);

	// Right Right Case
	if (bf < -1 && key > root->right->key)
		return leftRotate(root);

	// Left Right Case
	if (bf > 1 && key > root->left->key)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Left Case
	if (bf < -1 && key < root->right->key)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

Node* AVLTree::update(Node *root,int key, string value)
{
	if(root==NULL)
	{
		return root;
	}
	if(root->key==key)
	{
		root->value=value;
		cout<<"\nValue updated";
	}
	else if(key<root->key)
	{
		root->left=update(root->left,key,value);
	}
	else{
		root->right=update(root->right,key,value);
	}

	return root;
}
void AVLTree::deleteKey(int key)
{
	
}
void AVLTree::search(int key)
{
	Node* current = root;
	int comparisons = 0;

	while (current != NULL)
	{
		comparisons++;
		if (key == current->key)
		{
			cout << "\nKey found with value: " << current->value;
			cout << "\nComparisons made: " << comparisons;
			return;
		}
		else if (key < current->key)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}

	cout << "\nKey not found.";
	cout << "\nComparisons made: " << comparisons;
}

void AVLTree::print2D(Node *root, int space)
{
	if (root == NULL)
		return;
	space += SPACE;
	cout << endl;
	print2D(root->right, space);
	cout << endl;
	for (int i = SPACE; i < space; i++)
	{
		cout << " ";
	}
	cout << root->key << "\n";
	print2D(root->left, space);
}

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	int choice, key;
	string val;
	AVLTree avl;

	do
	{
		cout << "\n1. Insert\t2. Update\t3. Delete\t4. Search\t5. Display\t6. Exit";
		cout << "\nEnter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Enter key:";
			cin >> key;
			cout << "Enter value:";
			cin >> val;

			avl.root = avl.insert(avl.root, key, val);
			break;

		case 2:
			cout << "Enter key:";
			cin >> key;
			cout << "Enter value to update:";
			cin >> val;

			avl.root=avl.update(avl.root,key,val);
			break;

		case 3:
			cout << "Enter key:";
			cin >> key;
			avl.deleteKey(key);
			break;

		case 4:
			cout << "Enter key:";
			cin >> key;
			avl.search(key);
			break;
		
		case 5:
			avl.print2D(avl.root, 0);
			break;
		
		default:
			break;
		}

	} while (choice != 6);

	return 0;
}