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
		if (input.cmdOptionExists("-ppm")) {
			if (input.cmdOptionExists("-un")) {
				rle.decompressingPicture();
			}
			else {
				rle.compressingPicture();
			}
		}
		else if (input.cmdOptionExists("-utf8")) {
			if (input.cmdOptionExists("-un")) {
				rle.decompressingBits(true);
			}
			else {
				rle.compressingBits(true);
			}
		}
		else {
			if (input.cmdOptionExists("-un")) {
				rle.decompressingBits();
			}
			else {
				rle.compressingBits();
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
