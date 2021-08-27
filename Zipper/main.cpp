#include "zipper.h"
#include "parser.h"

void test01Sonet106many() {
	HaffmanZipper hfz;
	hfz.zipping("sonet106.txt", "sonet106zip.txt");
	hfz.unzipping("sonet106zip.txt", "unzippedtext.txt");
}

void test02MyAbstractText() {
	HaffmanZipper hfz;
	hfz.zipping("mytext.txt", "mytext.bin");
	hfz.unzipping("mytext.bin", "unzippedtext.txt");
}

void test03BirdsPick() {
	HaffmanZipper hfz;
	hfz.zipping("pic1.jpg", "pic1.bin");
	hfz.unzipping("pic1.bin", "pic1unzipped.jpg");
	//сжатия данных не произошло
}

int main(int argc, char* argv[]) {
	InputParser input(argc, argv);
	const std::string& input_filename = input.getCmdOption("-if");
	const std::string& output_filename = input.getCmdOption("-of");

	HaffmanZipper hfz;

	if (input.cmdOptionExists("-un")) {
		hfz.zipping(input_filename, output_filename);
	}
	else {
		hfz.unzipping(input_filename, output_filename);
	}

	return 0;
}