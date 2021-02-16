#include "utils.h"
#include "bmp_header.h"
#include <stdint.h>

// parsing the json file

void *getfromjson_file_header(char *string)
{
    cJSON *root = cJSON_Parse(string);
    cJSON *header = cJSON_GetObjectItem(root, "file_header");

    bmp_fileheader *p = malloc(sizeof(bmp_fileheader));

    if (!p) {
        printf("Eroare la alocare pointer\n");
        return NULL;
    }

    p->imageDataOffset = cJSON_GetObjectItem(header, "offset")->valueint;
    cJSON *signature = cJSON_GetObjectItem(header, "signature");
    p->fileMarker1 = signature->valuestring[0];
    p->fileMarker2 = signature->valuestring[1];
    p->unused1 = cJSON_GetObjectItem(header, "reserved")->valueint;
    p->unused2 = cJSON_GetObjectItem(header, "reserved")->valueint;
    p->bfSize = cJSON_GetObjectItem(header, "file_size")->valueint;

    cJSON_Delete(root);
    return (void *)p;
}

void *getfromjson_info_header(char *string)
{
    cJSON *root = cJSON_Parse(string);
    cJSON *info = cJSON_GetObjectItem(root, "info_header");

    bmp_infoheader *p = malloc(sizeof(bmp_infoheader));
    if (!p) {
        printf("Eroare la alocare pointer\n");
        return NULL;
    }

    p->biClrUsed = cJSON_GetObjectItem(info, "colors_used")->valueint;
    p->biSize = cJSON_GetObjectItem(info, "size")->valueint;
    unsigned int im = cJSON_GetObjectItem(info, "colors_important")->valueint;
    p->biClrImportant = im;
    p->biSizeImage = cJSON_GetObjectItem(info, "image_size")->valueint;
    int xpixels = cJSON_GetObjectItem(info, "x_pixels_per_meter")->valueint;
    p->biXPelsPerMeter = xpixels;
    int ypixels = cJSON_GetObjectItem(info, "y_pixels_per_meter")->valueint;
    p->biYPelsPerMeter = ypixels;
    p->width = cJSON_GetObjectItem(info, "width")->valueint;
    p->planes = cJSON_GetObjectItem(info, "planes")->valueint;
    p->bitPix = cJSON_GetObjectItem(info, "bit_count")->valueint;
    p->biCompression = cJSON_GetObjectItem(info, "compression")->valueint;
    p->height = cJSON_GetObjectItem(info, "height")->valueint;

    cJSON_Delete(root);

    return (void *)p;
}

int get_padding_size(int width, int bitpix)
{
    int neededpad = 0; // no. of needed padding bits
    
    // if a row does not have a 4 multiple no. of bits
    // I calculate the needed padding 

    if ((width * bitpix / 8) % 4 != 0)
        neededpad = 4 - (width * bitpix / 8) % 4;

    return neededpad;
}

color *generate_img_task1(char *string, void *fileinfo)
{
    bmp_infoheader *infoh = (bmp_infoheader *)fileinfo;
    // the bitmap
    cJSON *root = cJSON_Parse(string);
    cJSON *bitmap = cJSON_GetObjectItem(root, "bitmap");

    color *colorsarr = malloc(infoh->width * infoh->height * sizeof(color));
    if (!colorsarr) {
        printf("Eroare la alocare matrice culori\n");
        return NULL;
    }
    cJSON *iterator = NULL;
    int *bitmapvalue = malloc(10 * infoh->width * infoh->height * sizeof(int));
    if (!bitmapvalue) {
        printf("Eroare la alocare vector auxiliar\n");
        return NULL;
    }

    int k = 0;
    // using ArrayForEach instead of GetArrayItem because of the complexity
    // GetArrayItem does not move the pointer to the next element
    cJSON_ArrayForEach(iterator, bitmap)
        bitmapvalue[k++] = iterator->valueint;
    int i, j;
    k = 0;
    
    // adding all colours to the struct
    for (i = 0; i < infoh->height; i++)
        for (j = 0; j < infoh->width; j++) {
            colorsarr[i * infoh->height + j].blue = bitmapvalue[k++];
            colorsarr[i * infoh->height + j].green = bitmapvalue[k++];
            colorsarr[i * infoh->height + j].red = bitmapvalue[k++];
        }

    free(bitmapvalue);
    cJSON_Delete(root);
    return colorsarr;
}

void print_bmp(color *colorsarr, char *path, void *headerinfo,
               void *fileinfo, int taskid, int bonus)
{
    bmp_infoheader *infoh = (bmp_infoheader *)fileinfo;
    bmp_fileheader *fileh = (bmp_fileheader *)headerinfo;

    char *lastslash = strrchr(path, '/');
    char *filename = calloc(FILENAME_LEN, sizeof(char));
    if (!filename) {
        printf("Eroare la alocare nume fisier\n");
        return;
    }

    // if the argument is a path, the basename is after the last /
    if (lastslash != NULL) {

        if (bonus == 0)
            sprintf(filename, "output_task%d_%s.bmp",
                taskid, strtok(lastslash + 1, "."));
        else
            sprintf(filename, "output_bonus_%s.bmp",
                    strtok(lastslash + 1, "."));
    }
    else
        strcpy(filename, path);

    // the pixel array size is equal to the image size
    char *pixelarr = malloc(infoh->biSizeImage);

    if (!pixelarr) {
        printf("Eroare la alocare vector de pixeli\n");
        return;
    }

    int i, j, k = 0;
    int neededpad = get_padding_size(infoh->width, infoh->bitPix);

    if ((infoh->width * infoh->bitPix / 8) % 4 != 0)
        neededpad = 4 - (infoh->width * (infoh->bitPix) / 8) % 4;

    k = 0;

    for(i = infoh->height - 1; i >= 0; i--) {
        for(j = 0; j < infoh->width; j++) {
            pixelarr[k++] = colorsarr[i * infoh->height + j].blue;
            pixelarr[k++] = colorsarr[i * infoh->height + j].green;
            pixelarr[k++] = colorsarr[i * infoh->height + j].red;
        }

        // adding the padding if it is needed
        for (int padding = 0;  padding < neededpad; padding++)
            pixelarr[k++] = 0;
    }

    FILE *fp = fopen(filename, "wb");
    if (!fp)
        fprintf(stderr, "Eroare la deschidere fisier de output\n");

    // writing in the binary file
    fwrite(fileh, sizeof(bmp_fileheader), 1, fp);
    fwrite(infoh, sizeof(bmp_infoheader), 1, fp);
    fwrite(pixelarr, infoh->biSizeImage, 1, fp);
    fclose(fp);

    free(pixelarr);
    free(filename);
}

color *mirror_bmp(color *colorsarr, void *fileinfo)
{
    // The number position is explained so I swap the collumns
    // In order to mirror the bmp

    bmp_infoheader *infoh = (bmp_infoheader *)fileinfo;
    int i, j, aux, k;
    int hgt = infoh->height;
    int wdt = infoh->width;
    for (i = 2; i < hgt; i++)
        for (k = 2; k < wdt - 5; k += 8)
            for (j = 0; j < 2; j++) {
                int spos = i * hgt + k + 4 - j;
                aux = colorsarr[i * hgt + k + j].blue;
                colorsarr[i * hgt + k + j].blue = colorsarr[spos].blue;
                colorsarr[i * hgt + k + 4 - j].blue = aux;

                aux = colorsarr[i * hgt + k + j].green;
                colorsarr[i * hgt + k + j].green = colorsarr[spos].green;
                colorsarr[i * hgt + k + 4 - j].green = aux;

                aux = colorsarr[i * hgt + k + j].red;
                colorsarr[i * hgt + k + j].red = colorsarr[spos].red;
                colorsarr[i * hgt + k + 4 - j].red = aux;
            }

    return colorsarr;
}

char *get_string(color *colorarr, int startrow, int startcol, int height)
{
    char *output = malloc(OUTPUT_SIZE * sizeof(char));
    if (!output) {
        printf("Eroare la alocare sir care retine numar.\n");
        return NULL;
    }
    
    int i, j, k = 0;
    int index;
    for (i = startrow; i < startrow + 7; i++) {
        for (j = startcol; j < startcol + 7; j++) {
            index = i * height + j;
            int blue = colorarr[index].blue;
            int green = colorarr[index].green;
            int red = colorarr[index].red;

            if (blue == 255 && green == 255 && red == 255)
                output[k++] = '.';

            else
                output[k++] = 'X';
        }
        output[k++] = '\n';
    }
    output[k] = '\0';
    return output;
}

// Using a known output
// I hardcode all the digits

char **learn_numbers()
{
    char *fname = malloc(FILENAME_LEN * sizeof(char));
    strcpy(fname, "input/task1/board01.json");
    char *buffer = calloc (MAX_LEN, sizeof(char));
            if (!buffer) {
                printf("Eroare la alocare buffer\n");
                return NULL;
            }

            FILE *fp;
            fp = fopen(fname, "r");
            if (!fp)
                fprintf(stderr, "Eroare la deschidere fisier");

            fread(buffer, MAX_LEN, 1, fp);
            fclose(fp);

    bmp_fileheader *fileh = (bmp_fileheader *)getfromjson_file_header(buffer);
    bmp_infoheader *infoh = (bmp_infoheader *)getfromjson_info_header(buffer);
    color *colorarr = generate_img_task1(buffer, infoh);

    free(buffer);

    color *mirroredarr = mirror_bmp(colorarr, infoh);

    char **numbers = malloc(PATTERN_MEMORY * sizeof(char *));
    int k = 1;

    numbers[8] = get_string(mirroredarr, 1, k, infoh->height);
    k += 8;

    numbers[1] = get_string(mirroredarr, 1, k, infoh->height);
    k += 8;

    numbers[9] = get_string(mirroredarr, 1, k, infoh->height);
    k += 8;

    numbers[6] = get_string(mirroredarr, 1, k, infoh->height);
    k += 8;

    numbers[7] = get_string(mirroredarr, 1, k, infoh->height);
    k += 8;

    numbers[3] = get_string(mirroredarr, 1, k, infoh->height);
    k += 8;

    numbers[2] = get_string(mirroredarr, 1, k, infoh->height);
    k += 8;

    numbers[5] = get_string(mirroredarr, 1, k, infoh->height);
    k += 8;

    numbers[4] = get_string(mirroredarr, 1, k, infoh->height);

    int i, j;
    // the empty square
    numbers[0] = malloc(OUTPUT_SIZE * sizeof(char));
    if (!numbers[0]) {
        printf("Eroare la alocare sir care retine patratul gol.\n");
        return NULL;
    }

    k = 0;
    for (i = 0; i < SQUARE_SIZE; i++) {
        for (j = 0; j < SQUARE_SIZE; j++)
            numbers[0][k++] = '.';
        numbers[0][k++] = '\n';
    }

    numbers[0][k] = '\0';

    // the X
    numbers[10] = malloc(OUTPUT_SIZE * sizeof(char));
    if (!numbers[10]) {
        printf("Eroare la alocare sir care retine X-ul pt. fail la bonus.\n");
        return NULL;
    }
    k = 0;

    for (i = 0; i < SQUARE_SIZE; i++) {
        for (j = 0; j < SQUARE_SIZE; j++) {
            if (i == 0 || i == SQUARE_SIZE - 1 || j == SQUARE_SIZE - 1)
                numbers[10][k++] = '.';

            else if (i == j || i == SQUARE_SIZE - j - 1)
                numbers[10][k++] = 'X';
            else
                numbers[10][k++] = '.';
        }
        numbers[10][k++] = '\n';
    }

    numbers[10][k] = '\0';

    free(fileh);
    free(infoh);
    free(mirroredarr);
    free(fname);
    return numbers;
}

int *sudoku_matrix(char **numbers, color *colorarr, void *fileinfo)
{
    // adding the numbers from the image in a matrix
    bmp_infoheader *infoh = (bmp_infoheader *)fileinfo;

    int *matrix = malloc(MATRIX_SIZE * MATRIX_SIZE * sizeof(int));

    if (!matrix) {
        printf("Eroare la alocare matrice\n");
        return NULL;
    }

    int i, j, k;
    int index = 0;

    // every square is compared with the saved numbers
    // when I found a number I add it to the matrix
    // if I don't find a number, then the square is empty

    for (i = 1; i < infoh->height; i += 8)
        for (j = 1; j < infoh->width; j += 8) {

            char *output = get_string(colorarr, i , j, infoh->height);

                for (k = 1; k <= 9; k++) {

                    if (strcmp(output, numbers[k]) == 0) {
                        matrix[index++] = k;
                        free(output);
                        break;
                    }
                    if (k == 9) {
                        matrix[index++] = 0;
                        free(output);
                    }
                }
        }
    return matrix;
}

bool sudoku_integrity(int *matrix)
{

    int i, j, aux;

    // frequency array
    int *freq = calloc(DIGITS, sizeof(int));
    if (!freq) {
        printf("Eroare la alocare vector de frecventa\n");
        return false;
    }

    // checking the rows
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            aux = matrix[i * MATRIX_SIZE + j];
            freq[aux]++;
        }

        for (int k = 1; k <= 9; k++) {
            if (freq[k] != 1) {
                free(freq);
                return false;
            }
            freq[k] = 0;
        }
    }

    // checking the collumns
    for (j = 0; j < MATRIX_SIZE; j++) {
        for(i = 0; i < MATRIX_SIZE; i++) {
            aux = matrix[i * MATRIX_SIZE + j];
            freq[aux]++;
        }

        for (int k = 1; k <= 9; k++) {
            if (freq[k] != 1) {
                free(freq);
                return false;
            }
            freq[k] = 0;
        }
    }

    free(freq);
    return true;
}

void create_json(bool ok, char *path)
{
    char *lastslash = strrchr(path, '/');
    char *filename = calloc(FILENAME_LEN, sizeof(char));

    if (!filename) {
        printf("Eroare la alocare sir pt. nume fisier\n");
        return;
        }

    if (lastslash != NULL)
        sprintf(filename, "output_task3_%s.json", strtok(lastslash + 1, "."));
    else
        strcpy(filename, path);

    FILE *fp = fopen(filename, "w");
    if (!fp)
        fprintf(stderr, "Eroare la deschidere fisier de output\n");

    char *string = NULL;

    cJSON *root = cJSON_CreateObject();
    char *input_file = malloc(FILENAME_LEN * sizeof(char));
    
    if (!input_file) {
        printf("Eroare alocare nume fisier input.\n");
        return;
    }
    sprintf(input_file, "%s.json", strtok(lastslash + 1, "."));
    cJSON_AddItemToObject(root, "input_file", cJSON_CreateString(input_file));
    if (ok == true)
        cJSON_AddItemToObject(root, "game_state", cJSON_CreateString("Win!"));
    else
        cJSON_AddItemToObject(root, "game_state", 
                            cJSON_CreateString("Loss :("));

    string = cJSON_Print(root);
    fwrite(string, strlen(string), 1, fp);
    fprintf(fp, "\n");
    cJSON_Delete(root);
    free(string);
    free(filename);
    free(input_file);
    fclose(fp);
}