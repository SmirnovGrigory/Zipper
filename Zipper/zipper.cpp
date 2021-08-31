#include "zipper.h"

HaffmanZipper::HaffmanZipper(const std::string& input_file_name, const std::string& output_file_name) {
	input_file = std::ifstream(input_file_name, std::ios::binary);
	if (!input_file.is_open()) {
		throw std::invalid_argument("File Not Found.");
	}
	output_file = std::ofstream(output_file_name, std::ios::binary);
	if (!output_file.is_open()) {
		throw std::invalid_argument("File Not Found.");
	}
}

void HaffmanZipper::fillVocabStatistics() {
	while (!input_file.eof())
	{
		char c = input_file.get();
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

void HaffmanZipper::compress() {

	output_file << (unsigned char)vocab_table.size();

	std::map<char, std::vector<bool>>::iterator it;
	for (it = vocab_table.begin(); it != vocab_table.end(); it++) {
		output_file << it->first;
		output_file << (unsigned char)it->second.size();

		std::vector<bool> char_code = it->second;

		for (size_t i = 0; i <char_code.size(); i++) {
			output_file << char_code[i];
		}
		
	}
	
	input_file.clear();
	input_file.seekg(0);

	int count8 = 0;
	char compress_buf = 0;
	while (!input_file.eof()) {

		char c = input_file.get();
		std::vector<bool> char_code = vocab_table[c];

		for (size_t i = 0; i < char_code.size(); i++) {
			compress_buf = compress_buf | char_code[i] << (7 - count8);
			count8++;

			if (count8 == 8) {
				count8 = 0;
				output_file << compress_buf;
				compress_buf = 0;
			}
		}	
	}
	output_file.close();
}

void HaffmanZipper::zipping(){
	fillVocabStatistics();
	createTree();
	buildTable(main_root);
	compress();
	input_file.close();
}

void HaffmanZipper::unzipping() {
	std::map<char, std::vector<bool>> unzipping_vocab_table;
	unsigned char table_len = input_file.get();
	for (size_t i = 0; i < table_len; i++) {
		char c =(char)input_file.get();
		unsigned char len = input_file.get();
		std::vector<bool> char_code;
		for (size_t j = 0; j < len; j++) {
			 char_code.push_back((bool)(input_file.get() - '0'));
		}
		unzipping_vocab_table[c] = char_code;
	}

	int count8 = 0; char byte;
	byte = input_file.get();
	std::vector<bool> current_char_code;

	while (!input_file.eof()) {
		bool bit = byte & (1 << (7 - count8));
		current_char_code.push_back(bit);
		bool search_flag = false;
		std::map<char, std::vector<bool>>::iterator it;
		for (it = unzipping_vocab_table.begin(); it != unzipping_vocab_table.end(); it++) {
			if (it->second == current_char_code) {
				search_flag = true;
				break;
			}
		}
		if (search_flag) {
			output_file << it->first;
			current_char_code.clear();
		}

		count8++;
		if (count8 == 8) {
			count8 = 0;
			byte = input_file.get();
		}
	}
	input_file.close();
	output_file.close();
}

void HaffmanZipper::printVocabStatistics()  {
	std::map<char, int>::iterator it;
	for (it = vocab_statistics.begin(); it != vocab_statistics.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
}
