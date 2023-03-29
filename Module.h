#pragma once
#include "BMP.h"

void sliceImage (BMPImage image, int h, int w, BMPImage * &listImage);
void handleProcess (int h, int w, const BMPImage &image);
