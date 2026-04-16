/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
    /*if (rule != 0x1801) {
        exit(-1);
    }*/
    Color *color = (Color*) malloc(sizeof(Color));
    int count = 0;
    if (image->rows == 0 || image->cols == 0) {
        exit(-1);
    }
    for (int i = row-1; i <= row+1; i++) {
        for (int j = col-1; j <= col+1; j++) {
            if (i == row && j == col) {
                continue;
            }
            int m = (i + image->rows) % image->rows;
            int n = (j + image->cols) % image->cols;
            if (image->image[m][n].R == 255) {
                count += 1;
            }
            
        }
    }
    if (image->image[row][col].R == 255) {
        if (count == 2 || count == 3) {
            color->R = 255;
            color->G = 255;
            color->B = 255;
        } else {
            color->R = 0;
            color->G = 0;
            color->B = 0;
        }
    } else {
        if (count == 3) {
            color->R = 255;
            color->G = 255;
            color->B = 255;
        } else {
            color->R = 0;
            color->G = 0;
            color->B = 0;
        }
    }

    return color;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
    /*if (rule != 0x1801) {
        exit(-1);
    }*/
    Image *img = (Image*) malloc(sizeof(Image));
    img->rows = image->rows;
    img->cols = image->cols;
    img->image = (Color**) malloc(img->rows * sizeof(Color*));
    for (int i = 0; i < img->rows; i++) {
        img->image[i] = (Color*) malloc(img->cols * sizeof(Color));
    }
    for (int i = 0; i < image->rows; i++) {
        for (int j = 0; j < image->cols; j++) {
            Color *color = evaluateOneCell(image, i, j, rule);
            img->image[i][j] = *color;
            free(color);
        }
    }
    return img;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
    if (argc <= 2) {
        printf("usage: ./gameOfLife filename rule\nfilename is an ASCII PPM file (type P3) with maximum value 255.\nrule is a hex number beginning with 0x; Life is 0x1808.\n");
        exit(-1);
    }
    
    Image *image = readData(argv[1]);
    if (image == NULL || image->image == NULL) {
        exit(-1);
    }
    /*uint32_t rule = strtol(argv[2], NULL, 0);
    if (rule < 0 || rule > 0x3FFFF) {
        exit(-1);
    }*/
    char *endptr;
    uint32_t rule = strtol(argv[2], &endptr, 16);
    if (*endptr != '\0' || rule < 0x00000 || rule > 0x3FFFF) {
        printf("Invalid rule. Rule should be a hex number between 0x00000 and 0x3FFFF.\n");
        return -1;
    }
    Image *img = life(image, rule);
    writeData(img);
    freeImage(image);
    freeImage(img);
    return 0;
}
