#include "BMP.h"
#include <fstream>
#include <iostream>
#include <string.h>


bool BMPImage::read(const char* filename)
{
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (!inFile) {
        std::cout << "Cannot open file\n";
        return false;
    }

    _readInfo(inFile);
    _readColor(inFile);

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

    _writeInfo(outFile);
    _writeColor(outFile);

    if (outFile.bad()) {
        std::cout << "Fail to read file.\n";
        return false;
    }
    outFile.close();
    return true;
}


uint32_t BMPImage::width()
{
    return dib.b_width;
}

uint32_t BMPImage::height()
{
    return dib.b_height;
}

void BMPImage::_readColor(std::istream& inFile){
    inFile.seekg(header.offset, std::ios::beg);
    Color** temp = new Color * [dib.b_height];
    for (uint32_t i = 0; i < dib.b_height; i++) {
        temp[i] = new Color[dib.b_width];
        inFile.read(reinterpret_cast<char*>(temp[i]), line_pixel);
    }
    color = temp;
}


void BMPImage::_readInfo (std::istream& inFile) {
    inFile.read(reinterpret_cast<char*>(&header), sizeof(header));
    inFile.read(reinterpret_cast<char*>(&dib), sizeof(dib));

    // Update padding & linePixel
    this->_update();
}


void BMPImage::_writeInfo(std::ostream &outFile) {
    outFile.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    outFile.write(reinterpret_cast<char*>(&dib), sizeof(BMP_Dib));
}

void BMPImage::_writeColor(std::ostream &outFile) {
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
}

void BMPImage::_update()
{
    uint16_t colorDepth = dib.color_depth >= 8 ? dib.color_depth : 8;
    line_pixel = dib.b_width * colorDepth / 8;
    padding = (4 - line_pixel % 4) % 4;
}

