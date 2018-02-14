/*
 * @file    bmp.c
 * @brief   Writes/Reads bmp files from/into memory
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license LGPL
 *
 */

#include "bmp.h"

int bmpWriteColor(uchar *buffer, int w, int h, char *filename)
{
    int i;
    int fsize = w*h*3+HEADER_SIZE;
    uchar pad[3] = {0,0,0};
    uchar fileHeader[FILE_HEADER_SIZE] = 
    {
        'B','M',    // Magic Number
        0,0,0,0,
        0,0,
        0,0,
        HEADER_SIZE, // Size of the whole Header
        0,0,0
    };

    uchar infoHeader[INFO_HEADER_SIZE] = 
    {
        40,0,0,0,
        0,0,0,0,
        0,0,0,0,
        1,0,
        24,0    
    };

    fileHeader[2] = (uchar)(fsize);
    fileHeader[3] = (uchar)(fsize>>8);
    fileHeader[4] = (uchar)(fsize>>16);
    fileHeader[5] = (uchar)(fsize>>24);

    infoHeader[4] = (uchar)(w);
    infoHeader[5] = (uchar)(w>>8);
    infoHeader[6] = (uchar)(w>>16);
    infoHeader[7] = (uchar)(w>>24);
    infoHeader[8] = (uchar)(h);
    infoHeader[9] = (uchar)(h>>8);
    infoHeader[10] = (uchar)(h>>16);
    infoHeader[11] = (uchar)(h>>24);


    FILE *out = fopen(filename, "wb");
    fwrite(fileHeader,1,FILE_HEADER_SIZE,out);
    fwrite(infoHeader,1,INFO_HEADER_SIZE,out);
    
    for(i=0;i<h;i++)
    {
        fwrite(buffer+(w*(h-i-1)*3),3,w,out);
        fwrite(pad,1,(4-(w*3)%4)%4,out);
    }

    fclose(out);
    
    return fsize;
}
