#pragma once

#include <stdint.h>
#define MAX 100

struct Argument {
    uint32_t _width;
    uint32_t _height;
    char path[MAX];
};

void _getMainArgument(int argc, char **argv, Argument &argument);
void BMPSliceApplication(int argc, char **argv);