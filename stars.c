/*
 * @file    stars.c
 * @brief   Generates pictures of stars in space
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license LGPL
 *
 */

#define WIDTH 100
#define HEIGHT 100

#include "stars.h"
#include "math.h"

int main(int argc, char *argv[])
{
    //Star stars* = (Star*)malloc(sizeof(Star)*w*h);
    
    BMPColor buffer[HEIGHT][WIDTH]; 

    int x,y;
    for(y=0;y<HEIGHT;y++)
        for(x=0;x<WIDTH;x++)
    {
        unsigned char i = x%2 == y%2;
        buffer[y][x].r = i*255+sin(x)*cos(y);
        buffer[y][x].g = i*255*cos(y);
        buffer[y][x].b = i*255*sin(x);
    }

    bmpWriteColor((unsigned char*) buffer,WIDTH,HEIGHT,"out.bmp");
    return EXIT_SUCCESS;
}

float min(float a, float b)
{
    return (a<b)?(a):(b);
}


float max(float a, float b)
{
    return (a>b)?(a):(b);
}

float clamp (float value, float lowerBound, float upperBound)
{
    return min(upperBound,max(lowerBound,value));
}
