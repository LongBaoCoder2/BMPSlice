#pragma once
#include <stdint.h>
#include <fstream>

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;
    uint32_t file_size;
    uint32_t reserved;
    uint32_t offset;
};

struct BMP_Dib {
    uint32_t dib_size;
    int32_t b_width;
    int32_t b_height;

    uint16_t color_planes;
    uint16_t color_depth;

    uint32_t compress_algo;
    uint32_t pi_size;
    uint32_t hor_resol;
    uint32_t veri_resol;
    uint32_t color_table;
    uint32_t important_color;
};

struct Color {
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
};

#pragma pack(pop)

struct BMPImage {
    BMPHeader header;
    BMP_Dib dib;
    uint8_t padding;
    int line_pixel;
    Color** color;
    uint32_t size_raw;

    BMPImage() :header(), dib(), padding(0), line_pixel(0), color(nullptr){};
    BMPImage(Color** color) : header(), dib(), padding(0), line_pixel(0), color(color){};

    ~BMPImage() {
        int size = dib.b_width;
        for (int i = 0; i < size; i++) {
            delete[]color[i];
        }
        delete[] color;
    }

    // Get Width
    uint32_t width();

    // Get height
    uint32_t height();

    // Read BMP file
    bool read(const char* filname);

    // Write BMP to file
    bool write(const char* filname);

    // Update Info Header & Dib
    void _update();

    // Read color
    void _readColor(std::istream &inFile);

    // Read Header & Dib
    void _readInfo (std::istream &inFile);

    // Write Header & Dib to file
    void _writeInfo(std::ostream &outFile);

    // Write Color
    void _writeColor(std::ostream &outFile);

};




