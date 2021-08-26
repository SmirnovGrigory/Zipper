#include "node.h"

Node::Node() {
	left = NULL;
	right = NULL;
}

Node::Node(Node* left, Node* right) {
	this->left = left;
	this->right = right;
	count = left->count + right->count;
}

void Node::setSymbol(char symbol) {
	this->symbol = symbol;
}

void Node::setCount(int count) {
	this->count = count;
}

char Node::getSymbol() {
	return symbol;
}

int Node::getCount() {
	return count;
}

Node* Node::getLeft() {
	return left;
}

Node* Node::getRight() {
	return right;
}