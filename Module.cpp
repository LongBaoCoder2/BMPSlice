#include "Module.h"
#include <iostream>
#include <string.h>
#include <windows.h>
#define MAX 100

void handleEachImage(BMPImage &temp, int newWidth, int newHeight, uint32_t w,int process, BMPImage srcImage) {
    // temp.header = srcImage.header;
    // temp.dib = srcImage.dib;
    // temp.dib.b_width = newWidth;
    // temp.dib.b_height = newHeight;


    // Color **tempColor = new Color *[newHeight];
    // for (int j = 0; j < newHeight; j++) {
    //     tempColor[j] = new Color[newWidth];

    //     for (int z = 0; z < newWidth; z++) {
    //         tempColor[j][z] = srcImage.color[j + (process / w) * newHeight][z + (process % w) * newWidth];
    //     }
    // }
    // temp.color = tempColor;
    // temp._update();
}


void sliceImage (BMPImage image, uint32_t h, uint32_t w, BMPImage *&listImage) {

    int32_t sizeList = h * w;
    int32_t height = image.height(), width = image.width();
    int newHeight = height / h, newWidth = width / w;


    BMPImage *temp = new BMPImage[sizeList];
    if (temp == nullptr) {
        std::cout << "Out of memory\n.";
        return;
    }

    
    for (int i = 0; i < sizeList; i++) {
        temp[i].header = image.header;
        temp[i].dib = image.dib;
        temp[i].dib.b_width = newWidth;
        temp[i].dib.b_height = newHeight;


        Color **tempColor = new Color *[newHeight];
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
    char path[] = ".bmp", headerName[] = "BMPSliced";

    char temp[MAX], n = 0;
    while (i > 0) {
        temp[n++] = (i % 10) + '0';
        i /= 10;
    }

    for (int j = 0; j < n / 2 ; j++) {
        int reverseTemp = temp[j];
        temp[j] = temp[n - 1 - j];
        temp[n - 1 - j] = reverseTemp;
    }

    temp[n] = '\0';

    strcat(str, headerName);
    strcat(str, temp);
    strcat(str, path);
}


void handleProcess (uint32_t h, uint32_t w,  BMPImage image) {
    BMPImage *listImage = nullptr;
    sliceImage(image, h, w, listImage);


    if (listImage == nullptr) {
        std::cout << "Out of memory.\n";
        return;
    }

    std::cout << "Start Slicing...\n";
    for (uint32_t i = 0; i < w * h; i++) {
        char fileName[MAX] = "";
        _generateFileName(i + 1, fileName);
        listImage[i].write(fileName);
        progressBar(w * h, i);
    }

    delete []listImage;
}

void progressBar(int total, int i) {
    if (i == 0) {
        std::cout << "[ ";
    }
    int percent = 80 / total;
    for (int j = 0; j < percent; j++) {
        std::cout << "#";
    }
    // sleep(1);

    if (i == total - 1) {
        std::cout << " ]\n";
    }
}

