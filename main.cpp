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

	char path[] = "prof_octo.bmp";
	BMPImage picture;
	picture.read(path);

    handleProcess(2,3, picture);
	return 0;
}
