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

void RleCompressor::compressingPicture() {
	std::vector<unsigned char> current_pixel;
	current_pixel.resize(3);
	bool same = false;
	bool first = true;

	while (!input_file.eof()) {
		for (int i = 0; i < 3; i++)
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
			for (int i = 0; i < 3; i++)
				encoded_pixels.push_back(current_pixel[i]);
			occurence.push_back(1);
		}
	}

	for (int i = 0; i < occurence.size(); i++) {
		output_file << occurence[i];
		for (int j = 0; j < 3; j++)
			output_file << encoded_pixels[i*3 + j];
	}
	input_file.close();
	output_file.close();
}

void RleCompressor::decompressingPicture() {

	std::vector<unsigned char> current_pixel;
	current_pixel.resize(3);

	while (!input_file.eof()) {
		unsigned char len = input_file.get();

		for (int i=0; i<3;i++)
			current_pixel[i]= input_file.get();

		for (int i = 0; i < len; i++)
			for (int j = 0; j < 3; j++)
				output_file<<current_pixel[j];
	}
}