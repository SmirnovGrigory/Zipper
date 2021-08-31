#ifndef RLE_H
#define RLE_H

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

class RleCompressor {
private:
	std::vector<unsigned char> encoded_pixels;
	std::vector<bool> encoded_bits;
	std::vector<unsigned char> occurence;
	std::ifstream input_file;
	std::ofstream output_file;
	void writePixelsToFile();
	void writeBitsToFile();
public:
	RleCompressor(const std::string& input_file_name, const std::string& output_file_name);
	void compressingPicture();
	void decompressingPicture();
	void compressingBits(bool utf8=false);
	void decompressingBits(bool utf8 = false);
	void printOccurence();
};

#endif
