#include "rle.h"

void RleCompressor::printEncodedBytes() {
	for (int i = 0; i < encoded_bytes.size(); i++) {
		std::cout << encoded_bytes[i].first << " - " << encoded_bytes[i].second << std::endl;
	}
}

void RleCompressor::compressing(const std::string& input_file_name,
    const std::string& output_file_name) {
	std::ifstream input_stream(input_file_name, std::ios::binary);
	if (!input_stream.is_open()) {
		throw std::invalid_argument("File Not Found.");
	}
	std::ofstream out_file(output_file_name, std::ios::binary);

	std::vector<char> current_pixel;
	current_pixel.resize(3);
	bool same = false;
	bool first = true;
	//char tech_info[256];
	//input_stream.read(tech_info, 256);
	while (!input_stream.eof()) {
		for (int i = 0; i < 3; i++)
			current_pixel[i] = input_stream.get();
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
		out_file << occurence[i];
		for (int j = 0; j < 3; j++)
			out_file << encoded_pixels[i*3 + j];
	}
	input_stream.close();
	out_file.close();
}

void RleCompressor::decompressing(const std::string& input_file_name, const std::string& output_file_name) {
	std::ifstream input_stream(input_file_name, std::ios::binary);
	if (!input_stream.is_open()) {
		throw std::invalid_argument("File Not Found.");
	}
	std::ofstream out_file(output_file_name, std::ios::binary);

	std::vector<char> current_pixel;
	current_pixel.resize(3);

	while (!input_stream.eof()) {
		int len = (int)input_stream.get();

		for (int i=0; i<3;i++)
			current_pixel[i]= input_stream.get();

		for (int i = 0; i < len; i++)
			for (int j = 0; j < 3; j++)
				out_file<<current_pixel[j];
	}

	input_stream.close();
	out_file.close();
}