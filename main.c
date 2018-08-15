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

    gdImagePtr compareImg1, compareImg2;
    compareImg1 = gdImageCreate(8, 8);
    compareImg2 = gdImageCreate(8, 8);

    // 缩小到8x8像素
    gdImageCopyResized(compareImg1, sourceImg, 0, 0, 0, 0, 8, 8, gdImageSX(sourceImg), gdImageSY(sourceImg));
    gdImageCopyResized(compareImg2, targetImg, 0, 0, 0, 0, 8, 8, gdImageSX(targetImg), gdImageSY(targetImg));

    // 缩小到灰度 最多64种色彩
    gdImageGrayScale(compareImg1);
    gdImageGrayScale(compareImg2);

    int sourceColor, targetColor;
    int x = 8, y;
    while (x-- > 0) {
        y = 8;
        while (y-- > 0) {
            sourceColor = gdImagePalettePixel(compareImg1, x, y);
            targetColor = gdImagePalettePixel(compareImg2, x, y);
            printf("color: %d -> %d\n", sourceColor, targetColor);
        }
    }
    
    FILE *output;
    output = fopen("/tmp/result.png", "wb");
    gdImagePng(compareImg1, output);
    fclose(output);
    gdImageDestroy(compareImg1);
}