#include <iostream>
#include <fstream>
#include "BMP.h"
#include "Module.h"

void readfile(char * file) {
    std::ifstream in(file , std::ios::binary);

    char buffer;
    for (int i = 0; i < 200; i++) {
        in.read(&buffer, 1);
        std::cout << (unsigned int) buffer << " ";
    }
    std::cout << std::endl;

    in.close();
}


int main() {

	char path[] = "littleQ.bmp", example[] = "prof_octo.bmp";
	char outPath[] = "output.bmp";
	BMPImage picture;
	picture.read(example);
    picture.write(outPath);

    handleProcess(2,2, picture);
	return 0;
}
