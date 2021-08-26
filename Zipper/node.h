#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
private:
	char symbol;
	int count;
	Node* left;
	Node* right;
public:
	Node();
	Node(Node* left, Node* right);
	void setSymbol(char symbol);
	void setCount(int count);
	char getSymbol();
	int getCount();
	Node* getLeft();
	Node* getRight();
};

#endif 
