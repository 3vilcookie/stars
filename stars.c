/*
 * @file    stars.c
 * @brief   Generates pictures of stars in space
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license LGPL
 *
 */

#define WIDTH 1920
#define HEIGHT 1080 
#define STARS 50
#include "stars.h"

enum{

    MIX_XOR,
    MIX_BLEND,
    MIX_ADD,
    MIX_SUB,
    MIX_AND,
    MIX_OR,
};

int main(int argc, char *argv[])
{

    int x,y,i;
    /*Star stars[] = 
      {
      {
      {-10,30},
      {255,128,0},
      100
      },
      {
      {500,500},
      {25,158,50},
      20
      }
      };*/
    /*
       star.pos.x = -10;
       star.pos.y = 30;
       star.intensity = 100;
       star.color.b = 255;
       star.color.g = 128;
       star.color.r = 0;

*/

    BMPColor **buffer = calloc(HEIGHT, sizeof(BMPColor**));
    for(y=0;y<HEIGHT;y++)
        buffer[y] = calloc(WIDTH, sizeof(BMPColor*));

    //BMPColor buffer[HEIGHT][WIDTH]; 

    // Initialize buffer with black Color
    for(y=0;y<HEIGHT;y++)
        for(x=0;x<WIDTH;x++)
        {
            buffer[y][x].r = 0;
            buffer[y][x].g = 0;
            buffer[y][x].b = 0;
        }

    Pos p;

    srand(time(NULL));
    Star rndStar;
    //for(i=0;i<sizeof(stars)/sizeof(Star);i++)
    for(i=0;i<STARS;i++)
    {
        if( i % 100 == 0)
        {
            printf("Process: %.2f%%    \r",(100.0/5000.0)*(i+1));
            fflush(stdout);
        }
        rndStar.pos.x = (rand() % WIDTH)+1;
        rndStar.pos.y = (rand() % HEIGHT)+1;

        int r = rand() % 256;
        rndStar.color.r = 256-r;
        rndStar.color.g = r %50;
        rndStar.color.b = r;

        rndStar.intensity = (float)(rand() % 10000+1)/1000.0;
        for(y=0;y<HEIGHT;y++)
            for(x=0;x<WIDTH;x++)
            {
                p.x = x;
                p.y = y;

                //BMPColor *c = getPixelColorByStar(stars[i], p);
                buffer[y][x] = *mixRGB(*getPixelColorByStar(rndStar, p),buffer[y][x],MIX_SUB);
                
                /*
                buffer[y][x].r = clamp(buffer[y][x].r ^ c->r, 0, 255);
                buffer[y][x].g = clamp(buffer[y][x].g ^ c->g, 0, 255);
                buffer[y][x].b = clamp(buffer[y][x].b ^ c->b, 0, 255);
                */

            }
    }

    char* filename = getUniqueFilenameWithPath(OUTPUT_PATH,BASE_FILENAME,"bmp");

    size_t fileSize = bmpWriteColor((unsigned char**) buffer,WIDTH,HEIGHT,filename);
    printf("Wrote %lu bytes to %s\n", fileSize, filename);

    free(buffer);
    return EXIT_SUCCESS;
}

char* getUniqueFilenameWithPath(char* path, char* baseFilename, char* extension)
{
    // newFilename consits of: path + baseFilename + Index + . + extension + \0
    char *newFilename = (char*) malloc(strlen(path) + strlen(baseFilename) + 5 + 1 + strlen(extension) + 1);

    // Unsigned int can have 5 digits (log(2^16) ~ 5)
    unsigned int index = 1;
    FILE *f = NULL;

    while(1)
    {
        sprintf(newFilename, "%s%s%05u.%s", path, baseFilename, index, extension);
        f  = fopen(newFilename,"r");
        if(f == NULL)
            break;

        fclose(f);
        index++;
    }

    free(f);

    return newFilename;
}

BMPColor* getPixelColorByStar(Star s, Pos pixelPos)
{
    float d = euclidieanDistance(s.pos, pixelPos);

    BMPColor *c = (BMPColor*) malloc(sizeof(BMPColor));

    c->r = clamp((s.color.r * s.intensity)/d, 0, 255);
    c->g = clamp((s.color.g * s.intensity)/d, 0, 255);
    c->b = clamp((s.color.b * s.intensity)/d, 0, 255);
    return c;
}

BMPColor* mixRGB(BMPColor a, BMPColor b, unsigned mixMethod )
{
    BMPColor *resultColor = (BMPColor*)malloc(sizeof(BMPColor));

    switch(mixMethod)
    {
        case MIX_BLEND:
            resultColor->r = a.r*0.5 + b.r*0.5;
            resultColor->g = a.g*0.5 + b.g*0.5;
            resultColor->b = a.b*0.5 + b.b*0.5;
            break;
        case MIX_ADD:
            resultColor->r = a.r + b.r;
            resultColor->g = a.g + b.g;
            resultColor->b = a.b + b.b;
            break;
        case MIX_SUB:
            resultColor->r = a.r - b.r;
            resultColor->g = a.g - b.g;
            resultColor->b = a.b - b.b;
            break;
        case MIX_OR:
            resultColor->r = a.r | b.r;
            resultColor->g = a.g | b.g;
            resultColor->b = a.b | b.b;
            break;
        case MIX_AND:
            resultColor->r = a.r & b.r;
            resultColor->g = a.g & b.g;
            resultColor->b = a.b & b.b;
            break;
        case MIX_XOR:
            resultColor->r = a.r ^ b.r;
            resultColor->g = a.g ^ b.g;
            resultColor->b = a.b ^ b.b;
            break;
        default:
            resultColor->r = a.r;
            resultColor->g = a.g;
            resultColor->b = a.b;
    }


    resultColor->r = clamp(resultColor->r, 0, 255);
    resultColor->g = clamp(resultColor->g, 0, 255);
    resultColor->b = clamp(resultColor->b, 0, 255);

    return resultColor;
}

// Distance Functions {{{

float manhattanDistance(Pos p1, Pos p2)
{
    return abs(p1.x-p2.x) + abs(p1.y-p2.y);
}

float euclidieanDistance(Pos p1, Pos p2)
{
    return sqrt( pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
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
