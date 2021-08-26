#include "zipper.h"

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

HaffmanZipper::HaffmanZipper() {}

void HaffmanZipper::fillVocabStatistics() {
	while (!input_stream.eof())
	{
		char c = input_stream.get();
		vocab_statistics[c]++;
	}
}

void HaffmanZipper::createTree() {
	std::map<char, int>::iterator it;
	for (it = vocab_statistics.begin(); it != vocab_statistics.end(); it++) {
		Node* node = new Node;
		node->setSymbol(it->first);
		node->setCount(it->second);
		binary_tree.push_back(node);
	}

	while (binary_tree.size() != 1) {
		binary_tree.sort(CompareNodesbyCount());

		Node* leftSon = binary_tree.front();
		binary_tree.pop_front();
		Node* rightSon = binary_tree.front();
		binary_tree.pop_front();

		Node* parent = new Node(leftSon, rightSon);
		binary_tree.push_back(parent);
	}
	main_root = binary_tree.front();
}

void HaffmanZipper::buildTable(Node* root) {
	if (root->getLeft() != NULL) {
		current_code.push_back(0);
		buildTable(root->getLeft());
		current_code.pop_back();
	}
	if (root->getRight() != NULL) {
		current_code.push_back(1);
		buildTable(root->getRight());
		current_code.pop_back();
	}
	if (root->getLeft() == NULL && root->getRight() == NULL) {
		vocab_table[root->getSymbol()] = current_code;
	}
}

void HaffmanZipper::putCodesToOutFile(const std::string& output_file_name) {
	std::ofstream out_file(output_file_name, std::ios::binary);

	input_stream.clear();
	input_stream.seekg(0);

	int count8 = 0; char compress_buf = 0;
	while (!input_stream.eof()) {

		char c = input_stream.get();
		std::vector<bool> char_code = vocab_table[c];

		for (int i = 0; i < char_code.size(); i++) {
			compress_buf = compress_buf | char_code[i] << (7 - count8);
			count8++;

			if (count8 == 8) {
				count8 = 0;
				out_file << compress_buf;
				compress_buf = 0;
			}
		}
			
	}
	out_file.close();
}

void HaffmanZipper::zipping(const std::string& input_file_name, const std::string& output_file_name){
	input_stream = std::ifstream(input_file_name, std::ios::binary);
	//сделать проверку возможно файл не откроется
	fillVocabStatistics();
	printVocabStatistics();
	createTree();
	buildTable(main_root);
	putCodesToOutFile(output_file_name);
	input_stream.close();
}

void HaffmanZipper::printVocabStatistics() {
	std::map<char, int>::iterator it;
	for (it = vocab_statistics.begin(); it != vocab_statistics.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
}