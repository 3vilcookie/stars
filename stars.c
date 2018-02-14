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
    Star stars* = (Star*)malloc(sizeof(Star));
    
    star->pos.x = -10;
    star->pos.y = 30;
    star->intensity = 100;
    star->color.r = 255;
    star->color.g = 128;
    star->color.b = 0;

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

Color* getPixelColorByStar(Star* s, Pos *pixel)
{
    // Fill with love
    assert(0 && "Add all prototypes to the Header file and fill the getPixelColorByStar Function with love");
}

// Distance Functions {{{

float manhattanDistance(Pos p1, Pos p2)
{
    return abs(p1.x-p2.x) + abs(p1.y-p2.y);
}

float euclidieanDistance(Pos p1, Pos p2)
{
    return sqrt( pow(p1.x-p2.x,2) + pow(p1.y-p2.x,2));
}

// }}}

// Color Range Functions {{{

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

//}}}
