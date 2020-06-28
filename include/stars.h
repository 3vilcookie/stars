/*
 * @file    stars.h
 * @brief   Writes/Reads bmp files from/into memory
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license GPL
 *
 */

#ifndef STARS_H
#define STARS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "bmp.h"

#define OUTPUT_PATH "./examples/"
#define BASE_FILENAME "starout"


typedef struct Pos  
{                           
  int x,y;                
}Pos;          

typedef struct Star  
{                           
  Pos pos;                  
  BMPColor color;   
  float intensity;        
}Star;                 

void testImage();

// Utils and usability features which make the main program easier to understand
BMPColor** getEmptyFrameBuffer(unsigned width, unsigned height, BMPColor initColor);
char* getUniqueFilenameWithPath(char* path, char* baseFilename, char* extension);
char* getUniqueFrameFilenameWithPath(char* path, char* baseFilename, unsigned frameNumber, char* extension);
BMPColor mixRGB(BMPColor a, BMPColor b, unsigned mixMethod );

void viewBitmap(BMPColor** buffer, int width, int height, char trueColor);
int rgbToAnsi256(int r, int g, int b);

// Where the Graphic Stuff happens
BMPColor getPixelColorByStar(Star s, Pos pixel);
float manhattanDistance(Pos p1, Pos p2);
float euclidieanDistance(Pos p1, Pos p2);
float min(float a, float b);
float max(float a, float b);
float clamp (float value, float lowerBound, float upperBound);


#endif //STARS_H
