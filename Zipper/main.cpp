#include "zipper.h"
#include "parser.h"
#include "rle.h"


int main(int argc, char* argv[]) {
	/*InputParser input(argc, argv);
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
		else {
			if (input.cmdOptionExists("-un")) {
				rle.decompressingBits();
				//rle.logInputFileBits();
			}
			else {
				rle.compressingBits();
				rle.logInputFileBits();
			}
		}
	}
	else {
		std::cout << "you have not chosen a compression algorithm";
	}*/

	RleCompressor rle("test/test.txt", "lol.bin"); /*("test/test.txt", "lol.bin")*/
	rle.compressingBits();

	RleCompressor rle2("lol.bin", "testun.txt"); /*("lol.bin", "testun.txt")*/
	rle2.decompressingBits();

	



	
	return 0;
}
