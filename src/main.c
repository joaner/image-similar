#include "gd.h"
#include "./debug.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("./a.out {source.png} {target.png} {size}\n");
        return 1;
    }

    float minPercent = 0.9;
    int size = 8;
    if (argc > 3) {
        char *p;
        size = (int) strtol(argv[3], &p, 10);
        printf("size: %d\n", size);
    }

    const int width = size;
    const int height = size;

    gdImagePtr sourceImg, targetImg;
    sourceImg = gdImageCreateFromFile(argv[1]);
    targetImg = gdImageCreateFromFile(argv[2]);

    gdImagePtr compareImg1, compareImg2;
    compareImg1 = gdImageCreate(width, height);
    compareImg2 = gdImageCreate(width, height);

    // 缩小到8x8像素
    gdImageCopyResized(compareImg1, sourceImg, 0, 0, 0, 0, width, height, gdImageSX(sourceImg), gdImageSY(sourceImg));
    gdImageCopyResized(compareImg2, targetImg, 0, 0, 0, 0, width, height, gdImageSX(targetImg), gdImageSY(targetImg));

    // 缩小到灰度 最多64种色彩
    // gdImageGrayScale(compareImg1);
    // gdImageGrayScale(compareImg2);

    // 设置分辨率
    gdImageSetResolution(compareImg1, width, height);
    gdImageSetResolution(compareImg2, width, height);

    int compare = gdImageCompare(compareImg1, compareImg2);
    printf("gdImageCompare: %d\n", compare);

    int sourceColor, targetColor, diff;
    int x = width, y, match = 0;

    while (x-- > 0) {
        y = height;
        while (y-- > 0) {
            sourceColor = gdImagePalettePixel(compareImg1, x, y);
            targetColor = gdImagePalettePixel(compareImg2, x, y);

            diff = sourceColor - targetColor;
            if (diff > -2 && diff < 2) {
                match++;
            }
        }
    }

    double matchPercent = (100 * match) / (width * height);
    printf("gdImagePalettePixel: %.1f %%\n", matchPercent);
    
    debug(compareImg1, compareImg2);

    gdImageDestroy(compareImg1);
    gdImageDestroy(compareImg2);

    if (matchPercent > minPercent) {
        return 200;
    } else {
        return 201;
    }
}
