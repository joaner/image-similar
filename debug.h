#include "gd.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

char* readfile(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char*)malloc(fsize + 1);
    buffer[fsize] = '\0';
    fread(buffer, 1, fsize, fp);
    fclose(fp);

    printf("filesize: %d\n", fsize);

    const unsigned char *content = buffer;

    return g_base64_encode(content, fsize);
}

void debug(gdImagePtr sourceImg, gdImagePtr targetImg)
{
    FILE *output, *source, *target;

    source = tmpfile();
    gdImagePng(sourceImg, source);

    target = tmpfile();
    gdImagePng(targetImg, target);

    output = fopen("./debug.html", "wb");
    fprintf(output, "<!doctype html>");
    fprintf(output, "<html><head><title>%s</title><head>", "similar debug");
    fprintf(output, "<body>");

    char *base64;

    base64 = readfile(source);
    fprintf(output, "<img src=\"data:image/png;base64,%s\" />", base64);
    base64 = readfile(target);
    fprintf(output, "<img src=\"data:image/png;base64,%s\" />", base64);

    fprintf(output, "<style>img { width: 320px; }</style>");

    fprintf(output, "</body></html>");
}