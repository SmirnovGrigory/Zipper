#include "zipper.h"

void testSonet106many() {
	HaffmanZipper hfz;

	hfz.zipping("sonet106.txt", "sonet106zip.txt");
	hfz.unzipping("sonet106lol.txt", "unzippedtext.txt");
}

int main(int argc, char* argv[]) {
	testSonet106many();
}