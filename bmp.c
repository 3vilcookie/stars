/*
 * @file    bmp.c
 * @brief   Writes/Reads bmp files from/into memory
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license LGPL
 *
 */

#include "bmp.h"

// TODO: Go through buffer with coordinates (x,y) instead of index while
//       we now use uchar** instead of uchar*

size_t bmpWriteColor(uchar **buffer, int width, int height, char *filename)
{
    //int i;
    size_t fsize = width * height * 3  + HEADER_SIZE;

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

    infoHeader[4] = (uchar)(width);
    infoHeader[5] = (uchar)(width>>8);
    infoHeader[6] = (uchar)(width>>16);
    infoHeader[7] = (uchar)(width>>24);
    infoHeader[8] = (uchar)(height);
    infoHeader[9] = (uchar)(height>>8);
    infoHeader[10] = (uchar)(height>>16);
    infoHeader[11] = (uchar)(height>>24);


    FILE *out = fopen(filename, "wb");
    fwrite(fileHeader,1,FILE_HEADER_SIZE,out);
    fwrite(infoHeader,1,INFO_HEADER_SIZE,out);
    
    uchar paddingLength = (4-(3*width)%4)%4;
    uchar bytesPerPixel = 3;
    //size_t realWidth = width*bytesPerPixel;

    int y;
    for(y=height-1;y>=0;y--)
    {
        fwrite(&buffer[y][0],bytesPerPixel,width,out);
        fwrite(pad,1,paddingLength,out);
    }

    /*
    for(i=height;i>=0;i--)
    {
        puts ("HELLO");
        size_t offset = realWidth * (height-i-1);
        puts ("FROM");
        fwrite(buffer+(offset),bytesPerPixel,width,out);
        puts ("THE");
        fwrite(pad,1,paddingLength,out);
        puts ("OTHER");
    }
    */
    

    fclose(out);
    
    return fsize;
}
