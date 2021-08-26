#include "zipper.h"

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
	//test01Sonet106many();
	test02MyAbstractText();
	//test03BirdsPick();
}