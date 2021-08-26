#ifndef ZIPPER_H
#define ZIPPER_H

#include<iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <string>

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

class HaffmanZipper {
private:
	std::map<char,int> vocab_statistics;
	std::vector<bool> current_code;
	std::map<char, std::vector<bool>> vocab_table;
	std::list<Node*> binary_tree;
	std::ifstream input_stream;
	Node* main_root;

	void fillVocabStatistics();
	void createTree();
	void compress(const std::string& output_file_name);
	void buildTable(Node* root);
public:
	HaffmanZipper();
	void zipping(const std::string& input_file_name,const std::string& output_file_name);
	void unzipping(const std::string& input_file_name, const std::string& output_file_name);
	void printVocabStatistics();

};

struct CompareNodesbyCount
{
	bool operator()(Node* left, Node* right) const {
		return left->getCount() < right->getCount(); 
	}
};

#endif
