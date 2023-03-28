#include "Module.h"
#include <iostream>
#include <string.h>
#define MAX 100


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

void _generateFileName(int i, char str[]) {

    char path[] = ".bmp", headerName[] = "result/SlicedImage";

    char temp[MAX], n = 0;
    while (i > 0) {
        temp[n++] = (i % 10) + '0';
        i /= 10;
    }

    // Reverse
    for (int i = n - 1; i >= n / 2; i--) {
        temp[i] = temp[n - i - 1];
    }

    temp[n] = '\0';

    strcat(str, headerName);
    strcat(str, temp);
    strcat(str, path);
}


void handleProcess (int h, int w, const BMPImage& image) {
    BMPImage *listImage = nullptr;
    sliceImage(image, h, w, listImage);

    if (listImage == nullptr) {
        std::cout << "Out of memory.\n";
        return;
    }

    for (int i = 0; i < w * h; i++) {
        char fileName[MAX] = "";
        _generateFileName(i + 1, fileName);
        listImage[i].write(fileName);
    }

}

