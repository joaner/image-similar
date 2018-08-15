#include "gd.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("./a.out {source.png} {target.png}\n");
        exit(1);
    }

    gdImagePtr sourceImg, targetImg;
    sourceImg = gdImageCreateFromFile(argv[1]);
    targetImg = gdImageCreateFromFile(argv[2]);

    int sourceColor, targetColor;
    sourceColor = gdImageTrueColorPixel(sourceImg, 24, 24);
    targetColor = gdImageTrueColorPixel(targetImg, 16, 16);
    printf("color: %d -> %d\n", sourceColor, targetColor);
}