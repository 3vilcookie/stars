/*
 * @file    stars.c
 * @brief   Generates pictures of stars in space
 * @date    11/02/2018
 * @author  Raphael Pour <info@raphaelpour.de>
 * @license GPL
 *
 */

#define WIDTH (1920)
#define HEIGHT (1080)
#define STARS 10

#include "stars.h"

enum{//{{{
    MIX_XOR,
    MIX_BLEND,
    MIX_ADD,
    MIX_SUB,
    MIX_MUL,
    MIX_AND,
    MIX_OR,
};//}}}

int main(int argc, char *argv[])//{{{
{
    char view = 0;
	char trueColor = 0;
	int mixFunction = MIX_ADD;

    int i;
    for(i=1; i< argc;i++)
		if(argv[i][0] == 't' || (strcmp(argv[i],"--test") == 0))
		{
			puts("Test Flag set. Generate Test Image");
			testImage();
			return EXIT_SUCCESS;
		}
		else if(argv[i][0] == 'v' || (strcmp(argv[i],"--view") == 0))
			view = 1;
		else if(argv[i][0] == 'c' || (strcmp(argv[i],"--true-color") == 0))
			trueColor = 1;
		else if(argv[i][0] == 'x' || (strcmp(argv[i],"--mix-function") == 0))
		{
			int iValue = i+1;
			if(iValue < argc)
			{
				if(strcmp(argv[iValue],"add")==0)
					mixFunction = MIX_ADD;
				else if(strcmp(argv[iValue],"sub")==0)
					mixFunction = MIX_SUB;
				else if(strcmp(argv[iValue],"mul")==0)
					mixFunction = MIX_MUL;
				else if(strcmp(argv[iValue],"or")==0)
					mixFunction = MIX_OR;
				else if(strcmp(argv[iValue],"and")==0)
					mixFunction = MIX_AND;
				else if(strcmp(argv[iValue],"xor")==0)
					mixFunction = MIX_XOR;
				else if(strcmp(argv[iValue],"blend")==0)
					mixFunction = MIX_BLEND;
				else
				{
					printf("Unknown mix function\n");
					return EXIT_FAILURE;
				}
			}
			else
			{
				printf("Mix function missing\n");
				return EXIT_FAILURE;
			}
		}
        else
                printf("Unknown argument '%c'\n",argv[1][0]);


    int width,height;
    char* filename;
    size_t fileSize;
    int x,y;

    Pos p;
    srand(time(NULL));
    Star s;

    BMPColor initColor = {0,0,0};
    BMPColor **buffer;


    scanf("%d %d", &width, &height);

    buffer = getEmptyFrameBuffer(width, height,initColor);

    if(buffer == NULL)
    {
        puts("Couldn't allocate memory. Width > 0 and Height > 0?");
        return EXIT_FAILURE;
    }


    while(scanf("%d %d %hhu %hhu %hhu %f", &s.pos.x, &s.pos.y, &s.color.r, &s.color.g, &s.color.b, &s.intensity)>0)
    {
        fflush(stdout);

        for(y=0;y<height;y++)
            for(x=0;x<width;x++)
            {
                p.x = x;
                p.y = y;
                buffer[y][x] = mixRGB(getPixelColorByStar(s, p),buffer[y][x],mixFunction);
            }
    }

    filename = getUniqueFilenameWithPath(OUTPUT_PATH,BASE_FILENAME,"bmp");

    fileSize = bmpWriteColor(buffer, width, height, filename);
    printf("Wrote %lu bytes to %s\n", fileSize, filename);

    if(view)
        viewBitmap(buffer,width,height, trueColor);
    //free(buffer);
    return EXIT_SUCCESS;
}//}}}

void viewBitmap(BMPColor** buffer, int width, int height, char trueColor){
    int x,y;
        printf("   | ");
        for(x=0;x<width;x++)
            printf("%x", x % 16);

        printf("\n---+-");
        for(x=0;x<width;x++)
            printf("-");

        puts("");
        for(y=0;y<height;y++)
        {
            printf("%03x| ",y);
            for(x=0;x<width;x++)
            {
                BMPColor currentPixel = buffer[y][x];

				if(trueColor)
					printf("\x1b[48;2;%d;%d;%dm \x1b[0m", currentPixel.r, currentPixel.g, currentPixel.b);
				else
					printf("\e[48;5;%dm \e[0m",rgbToAnsi256(currentPixel.r, currentPixel.g, currentPixel.b));
            }
            printf("\n");
        }
}


int rgbToAnsi256(int r, int g, int b) {
    // we use the extended greyscale palette here, with the exception of
    // black and white. normal palette only has 4 greyscale shades.
    if (r == g && g == b) {
        if (r < 8) {
            return 16;
        }

        if (r > 248) {
            return 231;
        }

        return round(((r - 8) / 247) * 24) + 232;
    }

    int ansi = 16
        + (36 * round(r / 255 * 5))
        + (6 * round(g / 255 * 5))
        + round(b / 255 * 5);

    return ansi;
}

void testImage()//{{{
{
    int width = 500;
    int height = 500;
    size_t fileSize;
    char *filename = getUniqueFilenameWithPath(OUTPUT_PATH,"test","bmp");
    int x,y,i;
    Pos p;
    Star stars[] = //{{{
    {
        {
            {width/3,width/3},
            {0,0,255},
            20.0
        },   
        {
            {width/2,width*2/3},
            {0,255,0},
            20.0
        },   
        {
            {width/3*2,width/3},
            {255,0,0},
            20.0
        }   
    };//}}}

BMPColor initColor =  {0,0,0};
BMPColor **buffer = getEmptyFrameBuffer(width,height,initColor);

if(buffer == NULL)
{
    puts("Couldn't allocate memory. Width > 0 and Height > 0?");
    exit(EXIT_FAILURE);
}


for(i=0;i<sizeof(stars)/sizeof(Star); i++)
for(y=0;y<height;y++)
for(x=0;x<width;x++)
{
    p.x = x;
    p.y = y;
    buffer[y][x] = mixRGB(getPixelColorByStar(stars[i], p),buffer[y][x],MIX_ADD);
}


fileSize = bmpWriteColor(buffer, width, height, filename);
printf("Wrote %lu bytes to %s\n", fileSize, filename);

}//}}}

BMPColor** getEmptyFrameBuffer(unsigned width, unsigned height, BMPColor initColor)//{{{
{
    if(width == 0 || height == 0)
        return NULL;

    int x,y;
    // Make a 2D Array 
    BMPColor **buffer = calloc(height, sizeof(BMPColor**));

    if(buffer == NULL)return NULL;

    // Initialize every row 
    for(y=0;y<width;y++)
    {
        buffer[y] = calloc(width, sizeof(BMPColor*));
        if(buffer[y] == NULL)
            return NULL;
    }

    // Initialize buffer with black Color
    for(y=0;y<height;y++)
        for(x=0;x<width;x++)
        {
            buffer[y][x].r = initColor.r;
            buffer[y][x].g = initColor.g;
            buffer[y][x].b = initColor.b;
        }

    return buffer;

}//}}}

char* getUniqueFrameFilenameWithPath(char* path, char* baseFilename, unsigned frameNumber, char* extension)//{{{
{
    // newFilename consits of: path + baseFilename + Index + # + frame number. + extension + \0
    char *newFilename = (char*) malloc(strlen(path) + strlen(baseFilename) + 5 + 1 + 5 + 1 + strlen(extension) + 1);

    // Unsigned int can have 5 digits (log(2^16) ~ 5)
    unsigned int index = 1;
    FILE *f = NULL;

    while(1)
    {
        sprintf(newFilename, "%s%s%05u#%05u.%s", path, baseFilename, index, frameNumber, extension);
        f  = fopen(newFilename,"r");
        if(f == NULL)
            break;

        fclose(f);
        index++;
    }

    free(f);

    return newFilename;
}//}}}

char* getUniqueFilenameWithPath(char* path, char* baseFilename, char* extension)//{{{
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
}//}}}

BMPColor getPixelColorByStar(Star s, Pos pixelPos)//{{{
{
    float d = euclidieanDistance(s.pos, pixelPos);
    //    float d = manhattanDistance(s.pos, pixelPos);

    BMPColor *c = (BMPColor*) malloc(sizeof(BMPColor));

    c->r = clamp((s.color.r * s.intensity)/d, 0, 255);
    c->g = clamp((s.color.g * s.intensity)/d, 0, 255);
    c->b = clamp((s.color.b * s.intensity)/d, 0, 255);
    return *c;
}//}}}

BMPColor mixRGB(BMPColor a, BMPColor b, unsigned mixMethod )//{{{
{
    BMPColor *resultColor = &a;

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
        case MIX_MUL:
            resultColor->r = a.r * b.r;
            resultColor->g = a.g * b.g;
            resultColor->b = a.b * b.b;
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
            break;
    }


    resultColor->r = clamp(resultColor->r, 0, 255);
    resultColor->g = clamp(resultColor->g, 0, 255);
    resultColor->b = clamp(resultColor->b, 0, 255);


    return *resultColor;
}//}}}

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
