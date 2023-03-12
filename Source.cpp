#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

// Class for node
class Node
{
public:
	// Holds input for node
	int num;
	
	// Right pointer of node
	Node* right;

	// Left pointer of node
	Node* left;

	// Constructors for node, pointers initialized to null and allows input into node
	Node() { right = nullptr; left = nullptr;}
	Node(int c) { right = nullptr; left = nullptr; num = c; }
};

// Class for binary tree
class BinaryTree
{
public:
	// Pre-order traversal
	void NLR(Node* N);

	// Counts the levels of the binary tree for both left and right paths of a node, returns biggest height between both paths
	int countLevels(Node* N);

	// Calculates the height difference between left and right paths of a node
	int nodeHeightDifference(Node* N);

	// Inserts node into binary tree
	Node* insertNode(Node* N, int INPUT);

	// Removes node from binary tree
	Node* removeNode(Node* N, int INPUT);

	// Rotates the binary tree when node is inserted left of the left node
	Node* rotateLeftTwice(Node* N);

	// Rotates the binary tree when node is inserted to the right of right node
	Node* rotateRightTwice(Node* N);

	// Rotates binary tree when node is added to left of right node
	Node* rotateLeftRight(Node* N);

	// Rotates binary tree when node is added to the right of left node
	Node* rotateRightLeft(Node* N);

	// Balances the binary tree when the difference in heights between two subtrees is greater than or equal to 2
	Node* balanceTree(Node* N);
};

// Pre-order traversal
void BinaryTree::NLR(Node* N)
{
	cout << N->num << endl;
	if (N->left != nullptr)
		NLR(N->left);
	if (N->right != nullptr)
		NLR(N->right);
}

// Counts the levels of the binary tree for both left and right paths of a node, returns biggest height between both paths
int BinaryTree::countLevels(Node* N) 
{
	int nodeHeight = 0;

	if (N != nullptr) 
	{
		// Recurse through left and right subtrees
		int leftNodeHeight = countLevels(N->left);
		int rightNodeHeight = countLevels(N->right);

		// Finds biggest height between both subtree heights
		int maxNodeHeight = max(leftNodeHeight, rightNodeHeight);

		// Increases height by 1 everytime there is a non-null pointer
		nodeHeight = maxNodeHeight + 1;
	}
	return nodeHeight;
}

// Calculates the height difference between left and right paths of a node
int BinaryTree::nodeHeightDifference(Node* N) 
{
	// Recurse through left and right subtrees
	int leftNodeHeight = countLevels(N->left);
	int rightNodeHeight = countLevels(N->right);

	// Subtracts left and right subtree heights to find the balance factor of node
	int nodeHeightDifference = leftNodeHeight - rightNodeHeight;

	return nodeHeightDifference;
}

// Rotates the binary tree when node is inserted left of the left node
Node* BinaryTree::rotateLeftTwice(Node* N)
{
	// Nodes for left-left rotation
	Node* tempNode1;
	Node* tempNode2;

	tempNode1 = N;
	tempNode2 = tempNode1->left;

	tempNode1->left = tempNode2->right;
	tempNode2->right = tempNode1;

	return tempNode2;
}

// Rotates the binary tree when node is inserted to the right of right node
Node* BinaryTree::rotateRightTwice(Node* N)
{
	// Nodes for right-right rotation
	Node* tempNode1;
	Node* tempNode2;

	tempNode1 = N;
	tempNode2 = tempNode1->right;

	tempNode1->right = tempNode2->left;
	tempNode2->left = tempNode1;

	return tempNode2;
}

// Rotates binary tree when node is added to left of right node
Node* BinaryTree::rotateLeftRight(Node* N)
{
	// Nodes for left-right rotation
	Node* tempNode1;
	Node* tempNode2;
	Node* tempNode3;

	// First rotation
	tempNode1 = N;
	tempNode2 = tempNode1->left;
	tempNode3 = tempNode1->left->right;

	// Second rotation
	tempNode1->left = tempNode3->right;
	tempNode2->right = tempNode3->left;
	tempNode3->right = tempNode1;
	tempNode3->left = tempNode2;

	return tempNode3;
}

// Rotates binary tree when node is added to the right of left node
Node* BinaryTree::rotateRightLeft(Node* N)
{
	// Nodes for right-left rotation
	Node* tempNode1;
	Node* tempNode2;
	Node* tempNode3;

	// First rotation
	tempNode1 = N;
	tempNode2 = tempNode1->right;
	tempNode3 = tempNode1->right->left;
	
	// Second rotation
	tempNode1->right = tempNode3->left;
	tempNode2->left = tempNode3->right;
	tempNode3->left = tempNode1;
	tempNode3->right = tempNode2;

	return tempNode3;
}

// Balances the binary tree when the difference in heights between two subtrees is greater than or equal to 2
Node* BinaryTree::balanceTree(Node* N)
{
	int nodeBalanceCounter = nodeHeightDifference(N);

	if (nodeBalanceCounter >= 2) 
	{
		// If new node is inserted at the left child of the left subtree
		if (nodeHeightDifference(N->left) > 0)
		{
			N = rotateLeftTwice(N);
		}
		// If new node is inserted at the left child of the right subtree
		else
		{
			N = rotateLeftRight(N);
		}
	}
	else if (nodeBalanceCounter <= -2) 
	{
		// If new node is inserted at the right child of the left subtree
		if (nodeHeightDifference(N->right) > 0)
		{
			N = rotateRightLeft(N);
		}
		// If new node is inserted at the right child of the right subtree
		else
		{
			N = rotateRightTwice(N);
		}
	}
	return N;
}

// Inserts node into binary tree
Node* BinaryTree::insertNode(Node* N, int INPUT)
{
	// Creates new node at end of subtree
	if (N == nullptr)
	{
		N = new Node(INPUT);
	}
	// Inserts node to the left of current node
	else if (INPUT < N->num)
	{
		N->left = insertNode(N->left, INPUT);
		// Balance tree
		N = balanceTree(N);
	}
	// Inserts to the right of current node
	else
	{
		N->right = insertNode(N->right, INPUT);
		// Balance tree
		N = balanceTree(N);
	}
	return N;
}

// Removes node from binary tree
Node* BinaryTree::removeNode(Node* N, int INPUT)
{
	// Stop if node is null
	if (N == nullptr)
	{
		return N;
	}
	// Remove node at left
	if (N->num > INPUT)
	{
		N->left = removeNode(N->left, INPUT);
	}
	// Remove node at right
	else if (N->num < INPUT)
	{
		N->right = removeNode(N->right, INPUT);
	}
	// Removes node once recursing through left or right subtree, when it reaches null
	else
	{
		if (N->left == nullptr && N->right == nullptr)
		{
			return nullptr;
		}
		// Deletes node and replaces it with right node
		else if (N->left == nullptr)
		{
			Node* tempNode = N->right;
			delete(N);
			return tempNode;
		}
		// Deletes node and replaces it with left node
		else if (N->right == nullptr)
		{
			Node* tempNode = N->left;
			delete(N);
			return tempNode;
		}

		// Moves down the subtrees of node 
		Node* current = N->right;
		while (current && current->left != nullptr)
		{
			current = current->left;
		}

		// Sets replacer node equal to right node of current node
		Node* tempNode = current;

		// Sets node value equal to tempNode return value
		N->num = tempNode->num;
		N->right = removeNode(N->right, tempNode->num);

		// Balances tree after deleting
		N = balanceTree(N);
	}
	return N;
}

void main()
{
	int input;
	string command;

	// Creates new binary tree called "Tree1"
	BinaryTree Tree1;

	// Sets root of tree equal to null
	Node* root = nullptr;

	// Opens file at input.txt
	ifstream inputFile("c:\\temp\\input.txt");

	// Reads until end of file
	while (!inputFile.eof())
	{
		// Reads the commands "add" and "remove"
		inputFile >> command;
		
		// Adds a node if the command reads A
		if (command == "a" || command == "A")
		{
			inputFile >> input;

			// Inserts input into tree at the root
			root = Tree1.insertNode(root, input);

			system("cls");

			// Displays in NLR format
			Tree1.NLR(root);
		}

		// Removes a node if the command reads A
		if (command == "d" || command == "D")
		{
			inputFile >> input;

			// Removes input from tree at the root
			root = Tree1.removeNode(root, input);

			system("cls");

			// Displays in NLR format
			Tree1.NLR(root);
		}

		// Stop reading from file when "e -1" is typed
		if (command == "e" || command == "E")
		{
			inputFile >> input;

			if (input == -1)
				break;
		}
	}
}