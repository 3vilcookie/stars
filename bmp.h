/*
 * @file    bmp.h
 * @brief   Writes/Reads bmp files from/into memory
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license LGPL
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

size_t bmpWriteColor(uchar *buffer, int width, int height, char *filename);

#endif
