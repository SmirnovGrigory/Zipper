#include "rle.h"

RleCompressor::RleCompressor(const std::string& input_file_name, const std::string& output_file_name) {
	input_file = std::ifstream(input_file_name, std::ios::binary);
	if (!input_file.is_open()) {
		throw std::invalid_argument("File Not Found.");
	}
	output_file = std::ofstream(output_file_name, std::ios::binary);
	if (!output_file.is_open()) {
		throw std::invalid_argument("File Not Found.");
	}
}

void RleCompressor::printOccurence() {
	for (auto c : occurence)
		std::cout << (int)c << " ";
}

void RleCompressor::writePixelsToFile() {
	for (size_t i = 0; i < occurence.size(); i++) {
		output_file << occurence[i];
		for (size_t j = 0; j < 3; j++)
			output_file << encoded_pixels[i * 3 + j];
	}
}

void RleCompressor::compressingPicture() {
	std::vector<unsigned char> current_pixel;
	current_pixel.resize(3);
	bool same = false;
	bool first = true;

	while (!input_file.eof()) {
		for (size_t i = 0; i < 3; i++)
			current_pixel[i] = input_file.get();
		if (!first && current_pixel[0] == encoded_pixels[encoded_pixels.size() - 3]
				   && current_pixel[1] == encoded_pixels[encoded_pixels.size() - 2]
				   && current_pixel[2] == encoded_pixels[encoded_pixels.size() - 1]) {
			same = true;
		}
		else {
			first = false;
			same = false;
		}

		if (same) {
			if (occurence[occurence.size() - 1] == 255) {
				for (int i = 0; i < 3; i++)
					encoded_pixels.push_back(current_pixel[i]);
				occurence.push_back(1);
			}
			else
				occurence[occurence.size() - 1] += 1;
		}
		else {
			for (size_t i = 0; i < 3; i++)
				encoded_pixels.push_back(current_pixel[i]);
			occurence.push_back(1);
		}
	}

	writePixelsToFile();

	input_file.close();
	output_file.close();
}

void RleCompressor::decompressingPicture() {

	std::vector<unsigned char> current_pixel;
	current_pixel.resize(3);

	while (!input_file.eof()) {
		unsigned char len = input_file.get();

		for (size_t i=0; i<3;i++)
			current_pixel[i]= input_file.get();

		for (size_t i = 0; i < len; i++)
			for (size_t j = 0; j < 3; j++)
				output_file<<current_pixel[j];
	}
}

void RleCompressor::writeBitsToFile() {
	for (size_t i = 0; i < occurence.size(); i++) {
		unsigned char out_char = occurence[i] | (encoded_bits[i] << 7);
		output_file << out_char;
	}
}

void RleCompressor::compressingBits(bool utf8) {
	bool same = false;
	bool first = true;

	while (!input_file.eof()) {
		char current_byte = input_file.get();
		if (utf8 && current_byte == EOF)
			break;
		for (size_t i = 0; i < 8; i++) {
			bool current_bool = current_byte & 1 << (7 - i);
			if (!first && current_bool == encoded_bits[encoded_bits.size() - 1]) {
				same = true;
			}
			else {
				first = false;
				same = false;
			}

			if (same) {
				if (occurence[occurence.size() - 1] == 127) {
					encoded_bits.push_back(current_bool);
					occurence.push_back(1);

				}
				else
					occurence[occurence.size() - 1] += 1;
			}
			else {
				encoded_bits.push_back(current_bool);
				occurence.push_back(1);
			}
		}
	}

	writeBitsToFile();

	input_file.close();
	output_file.close();
}

void RleCompressor::decompressingBits(bool utf8) {
	unsigned char buf = 0;
	int count8 = 0;
	char current_char;

	while (!input_file.eof()) {
		current_char = input_file.get();
		if (utf8 && current_char == EOF)
			break;
		bool current_bit = current_char & (1 << 7);
		current_char = current_char & 127;

		size_t i = 0;
		while (i < current_char) {
			buf = buf | current_bit << (7 - count8);
			count8++;
			if (count8 == 8) {
				count8 = 0;
				output_file << buf;
				buf = 0;
			}
			i++;
		}		
	}
}