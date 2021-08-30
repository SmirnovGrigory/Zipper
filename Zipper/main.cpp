#include "zipper.h"
#include "parser.h"
#include "rle.h"


int main(int argc, char* argv[]) {
	InputParser input(argc, argv);
	const std::string& input_filename = input.getCmdOption("-if");
	const std::string& output_filename = input.getCmdOption("-of");

	if (input.cmdOptionExists("-haf")) {
		HaffmanZipper hfz(input_filename, output_filename);
		if (input.cmdOptionExists("-un")) {
			hfz.unzipping();
		}
		else {
			hfz.zipping();
		}
	} 
	else if (input.cmdOptionExists("-rle")) {
		RleCompressor rle(input_filename, output_filename);
		if (input.cmdOptionExists("-un")) {
			rle.decompressingPicture();
		}
		else {
			rle.compressingPicture();
		}
	}
	else {
		std::cout << "you have not chosen a compression algorithm";
	}
	
	return 0;
}
