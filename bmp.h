/*
 * @file    bmp.h
 * @brief   Writes/Reads bmp files from/into memory
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license GPL
 *
 */

#ifndef BMP_H
#define BMP_H

#include <stdlib.h>
#include <stdio.h>

#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE)

typedef unsigned char uchar;

typedef struct BMPColor//{{{
{   
    unsigned char b, g, r;  
}BMPColor;//}}}          

size_t bmpWriteColor(BMPColor **buffer, int width, int height, char *filename);

#endif
