#include "Interface.h"
#include "BMP.h"
#include "Module.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

/* Syntax
#define SYNTAX_ERROR -1
#define SLICE_FULL 0
#define SLICE_HEIGHT 1
#define SLICE_WIDTH 2
*/

void BMPSliceApplication(int argc, char **argv) {

    // Get argument
    Argument argument;
    _getMainArgument(argc, argv, argument);


    // Initialize Variable
    const char *path = argument.path;
    BMPImage image;
    image.read(path);
    handleProcess(argument._height, argument._width, image);
}




void _getMainArgument(int argc, char **argv, Argument &argument) {
    const char *optionHeight = "-h";
    const char *optionWidth = "-w";

    argument._width = argument._height = 1;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], optionHeight)) {
            argument._height = atoi(argv[i + 1]);
        }
        if (!strcmp(argv[i], optionWidth)) {
            argument._width = atoi(argv[i + 1]);
        }
    }

    strcpy(argument.path, argv[1]);
}
