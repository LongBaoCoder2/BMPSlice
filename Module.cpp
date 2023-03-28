#include "Module.h"
#include <iostream>

void sliceImage (BMPImage image, int h, int w, BMPImage *&listImage) {

    int sizeList = h * w;
    int height = image.height(), width = image.width();
    int newHeight = height / h, newWidth = width / w;

    BMPImage *temp = new BMPImage[sizeList];

    if (temp == nullptr) {
        std::cout << "Out of memory\n.";
        return;
    }
    Color **tempColor = nullptr;
    for (int i = 0; i < sizeList; i++) {
        temp[i].header = image.header;
        temp[i].dib = image.dib;
        temp[i].dib.b_width = newWidth;
        temp[i].dib.b_height = newHeight;

        tempColor = new Color *[newHeight];
        for (int j = 0; j < newHeight; j++) {
            tempColor[j] = new Color[newWidth];

            for (int z = 0; z < newWidth; z++) {
                tempColor[j][z] = image.color[j + (i / w) * newHeight][z + (i % w) * newWidth];
            }
        }
        temp[i].color = tempColor;
        temp[i]._update();
    }

    listImage = temp;
}

void handleProcess (int h, int w, const BMPImage& image) {
    BMPImage *listImage = nullptr;
    sliceImage(image, h, w, listImage);

    if (listImage == nullptr) {
        std::cout << "Out of memory.\n";
        return;
    }

    listImage[0].write("output.bmp");

}

