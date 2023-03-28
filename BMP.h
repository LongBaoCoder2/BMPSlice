#pragma once
#include <stdint.h>

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;
    uint32_t file_size;
    uint32_t reserved;
    uint32_t offset;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct BMP_Dib {
    uint32_t dib_size;
    uint32_t b_width;
    uint32_t b_height;

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

struct BMPImage {
    BMPHeader header;
    BMP_Dib dib;
    uint8_t padding;
    int line_pixel;
    Color** color;
    char* raw;
    uint32_t size_raw;

    BMPImage() :header(), dib(), padding(0), line_pixel(0), color(nullptr), raw(nullptr) {};
    BMPImage(Color** color) : header(), dib(), padding(0), line_pixel(0), color(color) , raw(nullptr) {};
    ~BMPImage() {
        int size = dib.b_width;
        for (int i = 0; i < size; i++) {
            delete[]color[i];
        }
        delete[] color;
        delete[] raw;
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

    // Read Color
    void _readColor();

};




