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
#include "bmp.h"

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


#endif
