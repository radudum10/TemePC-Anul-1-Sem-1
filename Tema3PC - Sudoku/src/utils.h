#ifndef utils
#define utils

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "cJSON.h"

#define MAX_LEN 62000
#define FILENAME_LEN 100
#define PATTERN_MEMORY 11
#define MATRIX_SIZE 9
#define OUTPUT_SIZE 100
#define DIGITS 10
#define SQUARE_SIZE 7

typedef struct 
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} color;

int get_padding_size(int width, int bitpix);
void *getfromjson_file_header(char *string);
void *getfromjson_info_header(char *string);
color *generate_img_task1(char *string, void *fileinfo);
color *mirror_bmp(color *colorsarr, void *fileinfo);
void print_bmp(color *colorsarr, char *filename, void *headerinfo,
                void *fileinfo, int taskid, int bonus);

char *get_string(color *colorarr, int startrow, int startcol, int height);
char *get_empty_string();
char **learn_numbers();
bool sudoku_integrity(int *matrix);
void create_json(bool ok, char *path);
void *get_bmp_fileheader(FILE *fp);
void *get_bmp_infoheader(FILE *fp);
int *sudoku_matrix(char **numbers, color *colorarr, void *fileinfo);
bool find_free_square(int *matrix, int *row, int *col);
bool out_of_bounds(int *row, int *col);
bool is_valid(int *matrix, int row, int col, int nr);
bool solve_sudoku(int *matrix, int row, int col);
color *generate_solution(int *matrix, char **numbers, color *colorarr,
                        void *fileinfo);
color *get_color_arr(FILE *fp, void *fileinfo);
color *insert_val(char *number, color *colorarr, int startrow, int startcol,
                int height);
color *generate_failure(color *colorarr, void *fileinfo, char *failureprint);
color *insert_failure(color *colorarr, int startrow, int startcol, int height,
                    char *failureprint);

#endif
