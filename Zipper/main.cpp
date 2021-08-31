#include "zipper.h"
#include "parser.h"
#include "rle.h"


int main(int argc, char* argv[]) {
	InputParser input(argc, argv);

	if (!(input.cmdOptionExists("-of") && input.cmdOptionExists("-if"))) {
		std::cout << "you have not chosen names for files";
		return -1;
	}

	const std::string& input_filename = input.getCmdOption("-if");
	const std::string& output_filename = input.getCmdOption("-of");

	if (input.cmdOptionExists("-haf")) {
		HaffmanZipper hfz(input_filename, output_filename);
		if (input.cmdOptionExists("-un")) {
			std::cout << "unzipping...";
			hfz.unzipping();
			std::cout << std::endl << "done";
		}
		else {
			std::cout << "zipping...";
			hfz.zipping();
			std::cout << std::endl << "done";
		}
	} 
	else if (input.cmdOptionExists("-rle")) {
		RleCompressor rle(input_filename, output_filename);
		if (input.cmdOptionExists("-ppm")) {
			if (input.cmdOptionExists("-un")) {
				std::cout << "unzipping...";
				rle.decompressingPicture();
				std::cout <<std::endl << "done";
			}
			else {
				std::cout << "zipping...";
				rle.compressingPicture();
				std::cout << std::endl << "done";
			}
		}
		else if (input.cmdOptionExists("-utf8")) {
			if (input.cmdOptionExists("-un")) {
				std::cout << "unzipping...";
				rle.decompressingBits(true);
				std::cout << std::endl << "done";
			}
			else {
				std::cout << "zipping...";
				rle.compressingBits(true);
				std::cout << std::endl << "done";
			}
		}
		else {
			if (input.cmdOptionExists("-un")) {
				std::cout << "unzipping...";
				rle.decompressingBits();
				std::cout << std::endl << "done";
			}
			else {
				std::cout << "zipping...";
				rle.compressingBits();
				std::cout << std::endl << "done";
			}
		}
	}
	else {
		std::cout << "you have not chosen a compression algorithm";
	}

	//RleCompressor rle("mytext.txt", "lol.bin"); /*("test/test.txt", "lol.bin")*/ /*("ppm\\test5.ppm", "lol.bin")*/
	//rle.compressingBits(true);

	//RleCompressor rle2("lol.bin", "unzipped.txt"); /*("lol.bin", "testun.txt")*/ /*("lol.bin", "unzipped.ppm")*/
	//rle2.decompressingBits(true);

	return 0;
}
