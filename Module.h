#include "BMP.h"

void handleEachImage(BMPImage &temp, int newWidth, int newHeight, uint32_t w,int process, BMPImage srcImage);
void sliceImage ( BMPImage image, uint32_t h, uint32_t w, BMPImage * &listImage);
void handleProcess (uint32_t h , uint32_t w ,  BMPImage image);
