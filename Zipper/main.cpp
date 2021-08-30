#include "zipper.h"
#include "parser.h"
#include "rle.h"

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

void test03Picture() {
	HaffmanZipper hfz;
	hfz.zipping("simple.png", "simple.bin");
	hfz.unzipping("simple.bin", "unzippedsimple.png");
	//сжатия данных не произошло
}

int main(int argc, char* argv[]) {
	/*InputParser input(argc, argv);
	const std::string& input_filename = input.getCmdOption("-if");
	const std::string& output_filename = input.getCmdOption("-of");

	HaffmanZipper hfz;

	if (input.cmdOptionExists("-un")) {
		hfz.unzipping(input_filename, output_filename);
	}
	else {
		hfz.zipping(input_filename, output_filename);
	}*/

	/*RleCompressor rle;
	rle.compressing("ppm/test4.ppm","lol.rle");
	rle.printOccurence();
	rle.decompressing("lol.rle", "result.ppm");*/
	test02MyAbstractText();
	return 0;
}
