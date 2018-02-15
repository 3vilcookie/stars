/*
 * @file    stars.h
 * @brief   Writes/Reads bmp files from/into memory
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license LGPL
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

typedef struct BMPColor//{{{
{                           
    unsigned char r, g, b;  
}BMPColor;//}}}             
                            
typedef struct Pos//{{{     
{                           
    int x,y;                
}Pos;//}}}                  
                            
typedef struct Star//{{{    
{                           
    Pos pos;                  
    BMPColor color;   
    float intensity;        
}Star;//}}}                 


BMPColor* getPixelColorByStar(Star s, Pos pixel);
float manhattanDistance(Pos p1, Pos p2);
float euclidieanDistance(Pos p1, Pos p2);

float min(float a, float b);
float max(float a, float b);
float clamp (float value, float lowerBound, float upperBound);


#endif //STARS_H
