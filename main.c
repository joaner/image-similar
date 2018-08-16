#include "gd.h"
#include "./debug.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("./a.out {source.png} {target.png}\n");
        return 1;
    }
    float minPercent = 0.9;

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

    // 设置分辨率
    gdImageSetResolution(compareImg1, 8, 8);
    gdImageSetResolution(compareImg2, 8, 8);

    int compare = gdImageCompare(compareImg1, compareImg2);
    printf("gdImageCompare: %d\n", compare);

    int sourceColor, targetColor, diff;
    diff = gdImagePalettePixel(compareImg1, 4, 4) - gdImagePalettePixel(compareImg2, 4, 4);
    printf("center diff: %d\n", diff);

    int x = 8, y, match = 0;
    while (x-- > 0) {
        y = 8;
        while (y-- > 0) {
            sourceColor = gdImagePalettePixel(compareImg1, x, y);
            targetColor = gdImagePalettePixel(compareImg2, x, y);

            if (sourceColor - targetColor == diff) {
                match++;
            }
        }
    }

    float matchPercent = (match/(8*8)) * 100;
    printf("gdImagePalettePixel: %.2f %%\n", matchPercent);
    
    debug(compareImg1, compareImg2);

    gdImageDestroy(compareImg1);
    gdImageDestroy(compareImg2);

    if (matchPercent > minPercent) {
        return 200;
    } else {
        return 201;
    }
}
