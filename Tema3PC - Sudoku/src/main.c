#include "utils.h"
#include "bmp_header.h"

int main(int argc, char **argv)
{

    if (argc != 0) {
        // identifying the task
        // the character which is after k
        // is the task number
        int tasknum = 0;
        for (size_t i = 0; i < strlen(argv[1]); i++)
            if(argv[1][i] == 'k') {
                tasknum = argv[1][i + 1] - '0';
                break;
            }

        if (tasknum == 1) {

            char *buffer = calloc(MAX_LEN, sizeof(char));
            if (!buffer) {
                printf("Eroare la alocare buffer\n");
                return -1;
            }

            FILE *fp;
            fp = fopen(argv[1], "r");
            if (!fp)
                fprintf(stderr, "Eroare la deschidere fisier");

            fread(buffer, MAX_LEN, 1, fp);
            fclose(fp);

            void *fileh = getfromjson_file_header(buffer);
            void *infoh = getfromjson_info_header(buffer);

            color *colorarr = generate_img_task1(buffer, infoh);
            print_bmp(colorarr, argv[1], fileh, infoh, 1, 0);

            color *mirroredarr = mirror_bmp(colorarr, infoh);
            print_bmp(mirroredarr, argv[1], fileh, infoh, 2, 0);

            char **numbers = learn_numbers();
            int *matrix = sudoku_matrix(numbers, mirroredarr, infoh);
            bool ok = sudoku_integrity(matrix);
            create_json(ok, argv[1]);

            for (int i = 0; i <= 10; i++)
                free(numbers[i]);
            free(numbers);
            free(fileh);
            free(infoh);
            free(matrix);
            free(colorarr);
            free(buffer);
            return 0;
        }

    else {
        FILE *fp = fopen(argv[1], "rb");

        if (!fp) {
            printf("Eroare la deschidere imagine\n");
            return -1;
        }
        void *fileh = get_bmp_fileheader(fp);
        void *infoh = get_bmp_infoheader(fp);
        color *colorarr = get_color_arr(fp, infoh);
        char **numbers = learn_numbers();
        int *matrix = sudoku_matrix(numbers, colorarr, infoh);

        int row, col;
        row = 0;
        col = 0;

        if (solve_sudoku(matrix, row, col) == true)
            colorarr = generate_solution(matrix, numbers, colorarr, infoh);
        else
            colorarr = generate_failure(colorarr, infoh, numbers[10]);

        if (tasknum == 4)
            print_bmp(colorarr, argv[1], fileh, infoh, 4, 0);
        else
            print_bmp(colorarr, argv[1], fileh, infoh, 0, 1);

        for (int i = 0; i <= 10; i++)
            free(numbers[i]);
        free(numbers);
        free(matrix);
        free(fileh);
        free(infoh);
        free(colorarr);
        fclose(fp);
    }
    }
    else {
        printf("Comanda nu a primit argumente\n");
        return -1;
    }
}