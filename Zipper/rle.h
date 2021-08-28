#ifndef RLE_H
#define RLE_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

class RleCompressor {
private:
	std::vector<std::pair<char, int>> encoded_bytes;
	std::vector<unsigned char> encoded_pixels;
	std::vector<unsigned char> occurence;
public:
	void compressing(const std::string& input_file_name, const std::string& output_file_name);
	void decompressing(const std::string& input_file_name, const std::string& output_file_name);
	void printEncodedBytes();
	void printOccurence();
};

#endif
