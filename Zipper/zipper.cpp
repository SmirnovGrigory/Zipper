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

	out_file << (unsigned char)vocab_table.size();

	std::map<char, std::vector<bool>>::iterator it;
	for (it = vocab_table.begin(); it != vocab_table.end(); it++) {
		out_file << it->first;
		out_file << (unsigned char)it->second.size();

		std::vector<bool> char_code = it->second;

		for (int i = 0; i <char_code.size(); i++) {
			out_file << char_code[i];
		}
		
	}

	input_stream.clear();
	input_stream.seekg(0);

	int count8 = 0;
	char compress_buf = 0;
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
	if (!input_stream.is_open()) {
		throw std::invalid_argument("File Not Found."); 
	}
	//сделать проверку возможно файл не откроется
	fillVocabStatistics();
	//printVocabStatistics();
	createTree();
	buildTable(main_root);
	compress(output_file_name);
	input_stream.close();
}

void printVocabTableFromZippedFile() {
	/*unsigned char table_len = zipped_file.get();
	for (int i = 0; i < table_len; i++) {
		std::cout << (char)zipped_file.get() << " ";
		unsigned char len = zipped_file.get();
		for (int j = 0; j < len; j++) {
			std::cout << (char)zipped_file.get();
		}
		std::cout << std::endl;
	}*/
}

void HaffmanZipper::unzipping(const std::string& input_file_name, const std::string& output_file_name) {
	std::ifstream zipped_file(input_file_name, std::ios::binary);
	if (!zipped_file.is_open()) {
		throw std::invalid_argument("File Not Found.");
	}
	std::ofstream unzipped_file(output_file_name, std::ios::binary);


	std::map<char, std::vector<bool>> unzipping_vocab_table;
	unsigned char table_len = zipped_file.get();
	for (int i = 0; i < table_len; i++) {
		char c =(char)zipped_file.get();
		unsigned char len = zipped_file.get();
		std::vector<bool> char_code;
		for (int j = 0; j < len; j++) {
			 char_code.push_back((bool)(zipped_file.get() - '0'));
		}
		unzipping_vocab_table[c] = char_code;
	}

	int count8 = 0; char byte;
	byte = zipped_file.get();
	std::vector<bool> current_char_code;

	while (!zipped_file.eof()) {
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
			unzipped_file << it->first;
			current_char_code.clear();
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
