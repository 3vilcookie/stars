/*
 * @file    bmp.c
 * @brief   Writes/Reads bmp files from/into memory
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license GPL
 *
 */

#include "bmp.h"
size_t bmpWriteColor(BMPColor **buffer, int width, int height, char *filename)
{
  size_t fsize = width * height * 3  + HEADER_SIZE;

  uchar pad[3] = {0,0,0};
  uchar fileHeader[FILE_HEADER_SIZE] = 
  {
    'B','M',    // Magic Number
    0,0,0,0,    // File Size
    0,0,        
    0,0,
    HEADER_SIZE,0,0,0  // Size of the whole Header 
  };

  uchar infoHeader[INFO_HEADER_SIZE] = 
  {
    40,0,0,0,
    0,0,0,0,    // Image width
    0,0,0,0,    // Image height
    1,0,        // 
    24,0        // Bit-Depth (3 Colors * 8 Bit, BGR )
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

  uchar bytesPerPixel = 3;
  uchar paddingLength = ( 4- ( bytesPerPixel * width ) %4) %4;

  // Bitmap is BGR (https://en.wikipedia.org/wiki/BMP_file_format)
  for(int y = height-1; y >= 0; y-- )
  {
    fwrite(&buffer[y][0],sizeof(BMPColor),width,out);
    fwrite(pad,1,paddingLength,out);
  }

  fclose(out);

  return fsize;
}
