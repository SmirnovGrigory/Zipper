#ifndef RLE_H
#define RLE_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

class RleCompressor {
private:
	std::vector<unsigned char> encoded_pixels;
	std::vector<unsigned char> occurence;
	std::ifstream input_file;
	std::ofstream output_file;
public:
	RleCompressor(const std::string& input_file_name, const std::string& output_file_name);
	void compressingPicture();
	void decompressingPicture();
	//void compressionBits
	void printOccurence();
};

#endif
