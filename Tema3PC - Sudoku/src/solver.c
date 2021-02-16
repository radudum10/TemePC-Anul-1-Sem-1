#include "utils.h"
#include "bmp_header.h"

void *get_bmp_fileheader(FILE *fp)
{
    bmp_fileheader *fileh = malloc(sizeof(bmp_fileheader));

    fread(&fileh->fileMarker1, sizeof(char), 1, fp);
    fread(&fileh->fileMarker2, sizeof(char), 1, fp);
    fread(&fileh->bfSize, sizeof(int), 1, fp);
    fread(&fileh->unused1, sizeof(short), 1, fp);
    fread(&fileh->unused2, sizeof(short), 1, fp);
    fread(&fileh->imageDataOffset, sizeof(int), 1, fp);

    return (void *)fileh;
}

void *get_bmp_infoheader(FILE *fp)
{
    bmp_infoheader *infoh = malloc(sizeof(bmp_infoheader));

    fread(&infoh->biSize, sizeof(int), 1, fp);
    fread(&infoh->width, sizeof(int), 1 , fp);
    fread(&infoh->height, sizeof(int), 1 ,fp);
    fread(&infoh->planes, sizeof(short), 1, fp);
    fread(&infoh->bitPix, sizeof(short), 1 , fp);
    fread(&infoh->biCompression, sizeof(int), 1 , fp);
    fread(&infoh->biSizeImage, sizeof(int), 1, fp);
    fread(&infoh->biXPelsPerMeter, sizeof(int), 1, fp);
    fread(&infoh->biYPelsPerMeter, sizeof(int), 1, fp);
    fread(&infoh->biClrUsed, sizeof(int), 1, fp);
    fread(&infoh->biClrImportant, sizeof(int), 1, fp);

    return (void *)infoh;
}

color *get_color_arr(FILE *fp, void *fileinfo)
{
    bmp_infoheader *infoh = (bmp_infoheader *)fileinfo;
    int padsize = get_padding_size(infoh->width, infoh->bitPix);

    char *pixelarr = malloc(infoh->biSizeImage);
    color *colorarr = malloc(infoh->biSizeImage);

    int i, j, k = 0;
    int index;

    fread(pixelarr, infoh->biSizeImage, 1, fp);

    for (i = infoh->height - 1; i >= 0; i--) {
        for (j = 0; j < infoh->width; j++) {
            index = i * infoh->height + j;
            colorarr[index].blue = pixelarr[k++];
            colorarr[index].green = pixelarr[k++];
            colorarr[index].red = pixelarr[k++];
        }

        for (int pad = 0; pad < padsize; pad++)
            k++;
    }
    free(pixelarr);

    return colorarr;
}

bool out_of_bounds(int *row, int *col)
{
    if ((*row) == MATRIX_SIZE - 1 && (*col) == MATRIX_SIZE)
        return true;

    if ((*col) == MATRIX_SIZE) {
        (*row)++;
        (*col) = 0;
    }

    return false;
}

bool find_free_square(int *matrix, int *row, int *col)
{
    for ((*row) = 0; (*row) < MATRIX_SIZE; (*row)++)
        for ((*col) = 0; (*col) < MATRIX_SIZE; (*col)++)
            if (matrix[(*row) * MATRIX_SIZE + (*col)] == 0)
                return true;

    return false;
}

bool is_valid(int *matrix, int row, int col, int nr)
{
    int i, j;

    for (j = 0; j < MATRIX_SIZE; j++)
        if (matrix[row * MATRIX_SIZE + j] == nr)
            return false;

    for (i = 0; i < MATRIX_SIZE; i++)
        if (matrix[i * MATRIX_SIZE + col] == nr)
            return false;

    int squarerow, squarecol;
    squarerow = row - row % 3;
    squarecol = col - col % 3;
    for (i = squarerow; i < squarerow + 3; i++)
        for (j = squarecol; j < squarecol + 3; j++)
            if (matrix[i * MATRIX_SIZE + j] == nr)
                return false;
    
    if (matrix[row * MATRIX_SIZE + col] != 0)
        return false;

    return true;
}

bool solve_sudoku(int *matrix, int row, int col)
{
    if (out_of_bounds(&row, &col) == true)
        return true;

    if (matrix[row * MATRIX_SIZE + col] > 0)
        return solve_sudoku(matrix, row, col + 1);

    if (find_free_square(matrix, &row, &col) == false)
        return true;

    int nr;

    for (nr = 1; nr < 10; nr++) {
        if(is_valid(matrix, row, col, nr) == true) {
            matrix[row * MATRIX_SIZE + col] = nr;

            if (solve_sudoku(matrix, row, col + 1) == true)
                return true;
        }

        matrix[row * MATRIX_SIZE + col] = 0;
    }

    return false;
}

color *insert_val(char *number, color *colorarr, int startrow, int startcol,
                int height)
{
    int i, j;
    int k = 0;

    for (i = startrow; i < startrow + SQUARE_SIZE; i++) {
        for (j = startcol; j < startcol + SQUARE_SIZE; j++) {
            if (number[k] == '\n')
                k++;

            if (number[k] == '.') {
                colorarr[i * height + j].blue = 255;
                colorarr[i * height + j].green = 255;
                colorarr[i * height + j].red = 255;
            }

            if (number[k] == 'X') {
                colorarr[i * height + j].blue = 255;
                colorarr[i * height + j].green = 0;
                colorarr[i * height + j].red = 255;
            }
            k++;
        }
    }
    return colorarr;
}

color *generate_solution(int *matrix, char **numbers, color *colorarr,
                        void *fileinfo)
{
    bmp_infoheader *infoh = (bmp_infoheader *)fileinfo;
    int i, j;
    int k = 0;

    for (i = 1; i < infoh->height; i += 8)
        for (j = 1; j < infoh->width; j += 8) {
            char *squarevalue = get_string(colorarr, i, j, infoh->height);
            if(strcmp(squarevalue, numbers[0]) == 0)
                colorarr = insert_val(numbers[matrix[k]], colorarr,
                                        i , j, infoh->height);
            k++;
            free(squarevalue);
        }

    return colorarr;
}

color *insert_failure(color *colorarr, int startrow, int startcol, int height,
                    char *failueprint)
{
    int i, j;
    int k = 0;
    for (i = startrow; i < startrow + SQUARE_SIZE; i++)
        for (j = startcol; j < startcol + SQUARE_SIZE; j++) {
                if (failueprint[k] == '\n')
                    k++;

                else if (failueprint[k] == '.') {
                    colorarr[i * height + j].blue = 255;
                    colorarr[i * height + j].green = 255;
                    colorarr[i * height + j].red = 255;
                }

                else {
                    colorarr[i * height + j].blue = 0;
                    colorarr[i * height + j].green = 0;
                    colorarr[i * height + j].red = 255;
                }
                k++;
            }
    return colorarr;
}

color *generate_failure(color *colorarr, void *fileinfo, char *failureprint)
{
    bmp_infoheader *infoh = (bmp_infoheader *)fileinfo;

    int i, j;

    for (i = 1; i < infoh->height; i += 8)
        for (j = 1; j < infoh->width; j += 8)
            colorarr = insert_failure(colorarr, i, j, infoh->height,
                                    failureprint);

    return colorarr;
}