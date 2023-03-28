#include "BMP.h"
#include <fstream>
#include <iostream>
#include <string.h>


uint32_t BMPImage::width()
{
    return dib.b_width;
}

uint32_t BMPImage::height()
{
    return dib.b_height;
}
/*
void BMPImage::_readColor() {
    if (raw == nullptr) return;

    uint32_t height = dib.b_height, width = dib.b_width;
    uint16_t colorDepth = dib.color_depth / 8 ? dib.color_depth / 8 : 1;


    Color** temp = new Color * [height];
    for (uint32_t i = 0; i < height; i++) {
        temp[i] = new Color[width];

        // De bi crash -> tim cach sua
        memcpy(temp[i], &raw[i * (line_pixel + padding)], width * sizeof(Color));
    }

    color = temp;
}
*/
bool BMPImage::read(const char* filename)
{
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);

    if (!inFile) {
        std::cout << "Cannot open file\n";
        return false;
    }

    // Implementation
    inFile.read(reinterpret_cast<char*>(&header), sizeof(header));
    inFile.read(reinterpret_cast<char*>(&dib), sizeof(dib));

    // Update padding & linePixel
    this->_update();

    // Read Color
    // size_raw = dib.b_height * (dib.b_width * padding);
    // raw = new char[size_raw];

    inFile.seekg(header.offset, std::ios::beg);
    Color** temp = new Color * [dib.b_height];
    for (uint32_t i = 0; i < dib.b_height; i++) {
        temp[i] = new Color[dib.b_width];
        inFile.read(reinterpret_cast<char*>(temp[i]), line_pixel);
    }
    color = temp;


    // inFile.read(raw, sizeof(raw));
    // _readColor();


    if (inFile.bad()) {
        std::cout << "Fail to read file.\n";
        return false;
    }

    inFile.close();
    return true;
}



bool BMPImage::write(const char* filename)
{
    std::ofstream outFile(filename, std::ios::out | std::ios::binary);

    if (!outFile) {
        std::cout << "Cannot open file\n";
        return false;
    }

    outFile.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    outFile.write(reinterpret_cast<char*>(&dib), sizeof(BMP_Dib));
    outFile.seekp(header.offset, std::ios::beg);
    uint32_t height = this->height(), width = this->width();
    for (uint32_t i = 0; i < height; i++) {
        outFile.write(reinterpret_cast<char*>(color[i]), line_pixel);

        if (padding > 0) {
            char buffer = 0;

            for (int j = 0; j < padding; j++)
                outFile.write(&buffer, 1);
        }
    }



    if (outFile.bad()) {
        std::cout << "Fail to read file.\n";
        return false;
    }

    std::cout << "Success\n";
    outFile.close();
    return true;
}



void BMPImage::_update()
{
    uint16_t colorDepth = dib.color_depth >= 8 ? dib.color_depth : 8;

    line_pixel = dib.b_width * colorDepth / 8;
    padding = (4 - line_pixel % 4) % 4;
}

