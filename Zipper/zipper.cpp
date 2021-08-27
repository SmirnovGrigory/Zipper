#include "zipper.h"


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

void HaffmanZipper::compress(const std::string& output_file_name) {
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
	//printVocabStatistics();
	createTree();
	buildTable(main_root);
	compress(output_file_name);
	input_stream.close();
}

void HaffmanZipper::unzipping(const std::string& input_file_name, const std::string& output_file_name) {
	std::ifstream zipped_file(input_file_name, std::ios::binary);
	std::ofstream unzipped_file(output_file_name, std::ios::binary);
	//setlocale(LC_ALL, "Russian"); 

	Node* p = main_root;
	int count8 = 0; char byte;
	byte = zipped_file.get();
	while (!zipped_file.eof())
	{
		bool b = byte & (1 << (7 - count8));
		if (b)
			p = p->getRight();
		else
			p = p->getLeft();
		if (p->getLeft() == NULL && p->getRight() == NULL) {
			unzipped_file << p->getSymbol();
			p = main_root;
		}
		count8++;
		if (count8 == 8) {
			count8 = 0;
			byte = zipped_file.get();
		}
	}
	zipped_file.close();
	unzipped_file.close();
}

void HaffmanZipper::printVocabStatistics() {
	std::map<char, int>::iterator it;
	for (it = vocab_statistics.begin(); it != vocab_statistics.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
}
