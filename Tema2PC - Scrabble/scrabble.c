#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util/scrabble.h"
#include "util/print_board.h"

#define SIZE 15
#define STRSIZE 5
#define BUFFERSIZE 50

// TASK 0 //

void task_0(char game_board[SIZE][SIZE])
{
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            game_board[i][j] = '.';
    // initalizing all elements with '.'
}

// TASK 1 //

void word_inputter(char game_board[SIZE][SIZE], int row, int col,
                   int dir, char *word)
{
    // a function for adding a word to the matrix
    size_t i;
    int j;

    // placing the word horizontally or vertically
    // depending on the given direction

    if (dir == 0) {
        j = col;
        for (i = 0; i < strlen(word); i++) {
            game_board[row][j] = word[i];
            j++;
        }
    }

    else {
        j = row;
        for (i = 0; i < strlen(word); i++) {
            game_board[j][col] = word[i];
            j++;
        }
    }
}

void task_1(char game_board[SIZE][SIZE])
{
    task_0(game_board);

    char buffer[BUFFERSIZE];
    char n[STRSIZE], col[STRSIZE], row[STRSIZE], dir[STRSIZE], word[16];
    int i;

    fgets(buffer, BUFFERSIZE, stdin);
    strncpy(n, buffer, STRSIZE);

    for (i = 0; i < atoi(n); i++) {
        fgets(buffer, BUFFERSIZE, stdin);

        strcpy(row, strtok(buffer, " "));
        strncpy(col, strtok(NULL, " "), STRSIZE);
        strncpy(dir, strtok(NULL, " "), STRSIZE);
        strncpy(word, strtok(NULL, " "), 16);
        if (word[strlen(word) - 1] == '\n')
            word[strlen(word) - 1] = '\0';

        word_inputter(game_board, atoi(row), atoi(col), atoi(dir), word);
    }
}

// TASK 2 //

int score_check(char *word)
{
    int k, score;
    size_t i;

    int score_grid[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1,
                          1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    score = 0;

    // index = ASCII code - A's ASCII Code
    for (i = 0; i < strlen(word); i++) {
        k = word[i] - 'A';
        score += score_grid[k];
    }

    return score;
}

void task_2(void)
{
    char buffer[BUFFERSIZE];
    char n[STRSIZE], col[STRSIZE], row[STRSIZE], dir[STRSIZE], word[16];
    int i, player1_score, player2_score;

    player1_score = 0;
    player2_score = 0;

    fgets(buffer, BUFFERSIZE, stdin);
    strncpy(n, buffer, STRSIZE);

    for (i = 0; i < atoi(n); i++) {
        fgets(buffer, BUFFERSIZE, stdin);

        strncpy(row, strtok(buffer, " "), STRSIZE);
        strncpy(col, strtok(NULL, " "), STRSIZE);
        strncpy(dir, strtok(NULL, " "), STRSIZE);
        strncpy(word, strtok(NULL, " "), 16);
        if(word[strlen(word) - 1] == '\n')
            word[strlen(word) - 1] = '\0';

        // player 1 plays first
        if (i % 2 == 0)
            player1_score += score_check(word);

        else
            player2_score += score_check(word);
    }
    printf("Player 1: %d Points\n", player1_score);
    printf("Player 2: %d Points\n", player2_score);
}

// TASK 3 //

int simple_bonus(int row, int col, int dir, char *word)
{
    // if on the bonus board there is 1 then
    // bonus x2
    size_t i;
    int bonus, j;
    bonus = 1;
    if (dir == 0) {
        j = col;
        for (i = 0; i < strlen(word); i++) {
            if (bonus_board[row][j] == 1)
                bonus *= 2;
            j++;
        }
    }

    else {
        j = row;
        for (i = 0; i < strlen(word); i++) {
            if (bonus_board[j][col] == 1)
                bonus *= 2;
            j++;
        }
    }
    return bonus;
}

int double_bonus(int row, int col, int dir, char *word)
{
    // if on the bonus board there is 2 then
    // bonus x3
    size_t i;
    int bonus, j;
    bonus = 1;

    if (dir == 0) {
        j = col;
        for (i = 0; i < strlen(word); i++) {
            if(bonus_board[row][j] == 2)
                bonus *= 3;
            j++;
        }
    }

    else {
        j = row;
        for (i = 0; i < strlen(word); i++) {
            if (bonus_board[j][col] == 2)
                bonus *= 3;
            j++;
        }
    }
    return bonus;
}

void task_3(void)
{
    char buffer[BUFFERSIZE];
    char n[STRSIZE], col[STRSIZE], row[STRSIZE], dir[STRSIZE], word[16];
    int i, player1_score, player2_score, round_score;
    char sylab[STRSIZE], bonus1[STRSIZE], bonus2[STRSIZE];

    fgets(buffer, BUFFERSIZE, stdin);

    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';

    strncpy(bonus1, buffer, STRSIZE);

    fgets(buffer, BUFFERSIZE, stdin);

    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';

    strncpy(bonus2, buffer, STRSIZE);

    fgets(buffer, BUFFERSIZE, stdin);
    strncpy(n, buffer, STRSIZE);

    player1_score = 0;
    player2_score = 0;
    round_score = 0;

    for (i = 0; i < atoi(n); i++) {
        fgets(buffer, BUFFERSIZE, stdin);

        strncpy(row, strtok(buffer, " "), STRSIZE);
        strncpy(col, strtok(NULL, " "), STRSIZE);
        strncpy(dir, strtok(NULL, " "), STRSIZE);
        strncpy(word, strtok(NULL, " "), 16);
        if (word[strlen(word) - 1] == '\n')
            word[strlen(word) - 1] = '\0';

        strcpy(sylab, word + strlen(word) - 2);

        if (i % 2 == 0) {
            round_score += score_check(word);
            // condition for bonus x3
            // (last 2 letters = YY)
            // where YY is a given string
            if (strstr(sylab, bonus2))
                round_score *= double_bonus(atoi(row), atoi(col),
                                            atoi(dir), word);

            // condition for bonus x2
            // (the word contains XX)
            // where XX is a given string
            if (strstr(word, bonus1))
                round_score *= simple_bonus(atoi(row), atoi(col),
                                            atoi(dir), word);

            player1_score += round_score;
            round_score = 0;

        }
        else {
            round_score += score_check(word);
            if (strstr(sylab, bonus2))
                round_score *= double_bonus(atoi(row), atoi(col), 
                                            atoi(dir), word);

            if (strstr(word, bonus1))
                round_score *= simple_bonus(atoi(row), atoi(col),
                                            atoi(dir), word);

            player2_score += round_score;
            round_score = 0;
        }
    }
    printf("Player 1: %d Points\n", player1_score);
    printf("Player 2: %d Points\n", player2_score);
}

// TASK 4 //

void word_remover(char *word, int *length)
{
    int i, pos, ok = 0;

    for (i = 0 ; i < *length ; i++)
        // finding the index of the word in the array
        // also if it is in the array
        if (strcmp(word, words[i]) == 0) {
            pos = i;
            ok = 1;
        }
    // if the word is in the array
    // all elements are moved to the left
    // starting with the identified word
    if (ok) {
    for (i = pos; i < *length; i++)
        strcpy(words[i], words[i + 1]);

    (*length)--;
    }
}

int vert_check(char game_board[SIZE][SIZE], char *word,
               int row, int col)
{
    size_t i;
    int j;
    // checking if it is possible to put a word vertically
    j = row + 1;
    for (i = 0; i < strlen(word) - 1; i++) {
        if (game_board[j][col] != '.' || j == SIZE)
            return 0;
        j++;
    }
    return 1;
}

int horiz_check(char game_board[SIZE][SIZE],
                char *word, int row, int col)
{
    size_t i;
    int j;
    j = col + 1;
    // checking if it is possible to put a word horizontally
    for(i = 0; i < strlen(word) - 1; i++) {
        if (game_board[row][j] != '.' || j == SIZE)
            return 0;
        j++;
    }

    return 1;
}

void word_picker(char game_board[SIZE][SIZE], int length)
{
    int k, i, j, pos[40], count, ok = 0;
    char word[16];

    k = 0;
    while(k < length) {
        // for every word in the array
        strcpy(word, words[k]);
        count = 0;
        // if the first letter is in the matrix
        // I check if you can put it on the board vertically/orizontally

        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
                if (word[0] == game_board[i][j]) {
                    pos[count] = i;
                    pos[count + 1] = j;
                    count += 2;
                    ok = 1;
                }
        if (ok == 1) {
            for (i = 0; i < count; i += 2) {
                if (vert_check(game_board, word, pos[i], pos[i + 1])) {
                    word_inputter(game_board, pos[i], pos[i + 1], 1, word);
                    print_board(game_board);
                    return;
                }

                if (horiz_check(game_board, word, pos[i], pos[i + 1])) {
                    word_inputter(game_board, pos[i], pos[i + 1], 0, word);
                    print_board(game_board);
                    return;
                }
            }
        }
        count = 0;
        k++;
        ok = 0;
    }
}

void task_4(char game_board[SIZE][SIZE])
{
    task_0(game_board);
    char n[STRSIZE], col[STRSIZE], row[STRSIZE], dir[STRSIZE], word[16];
    char buffer[BUFFERSIZE];
    char bonus1[STRSIZE], bonus2[STRSIZE];
    int i, len;
    len = 100;

    fgets(buffer, BUFFERSIZE, stdin);
    if(buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    strncpy(bonus1, buffer, STRSIZE);

    fgets(buffer, BUFFERSIZE, stdin);
    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    strncpy(bonus2, buffer, STRSIZE);

    fgets(buffer, BUFFERSIZE, stdin);
    strncpy(n, buffer, STRSIZE);

    for (i = 0; i < atoi(n); i++) {
        fgets(buffer, BUFFERSIZE, stdin);

        strncpy(row, strtok(buffer, " "), STRSIZE);
        strncpy(col, strtok(NULL, " "), STRSIZE);
        strncpy(dir, strtok(NULL, " "), STRSIZE);
        strncpy(word, strtok(NULL, " "), 16);
        if (word[strlen(word) - 1] == '\n')
            word[strlen(word) - 1] = '\0';

        word_inputter(game_board, atoi(row), atoi(col), atoi(dir), word);
        word_remover(word, &len);
    }
    word_picker(game_board, len);
}

// TASK 5 //

void perfect_move(char game_board[SIZE][SIZE], int len, int dif,
                  char *bonus1, char *bonus2)
{
    int k = 0, i, j, pos[40], count, ok = 0, max = 0;
    char word[16], word_max[16], sylab[STRSIZE];
    int poz1_max, poz2_max, dir_max;
    int score = 0;
    
    while (k < len) {
        strcpy(word, words[k]);
        strncpy(sylab, word + strlen(word) - 2, 2);
        count = 0;
        // for every word in the array
        // I calculate the score
        // I save the maximum score and the word which generates it
        // and its position in the array

        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
                if (word[0] == game_board[i][j]) {
                    pos[count] = i;
                    pos[count + 1] = j;
                    count += 2;
                    ok = 1;
                }

        if (ok == 1) {
            for (i = 0; i < count; i += 2) {
                if (vert_check(game_board, word, pos[i], pos[i + 1])) {
                    score = score_check(word);

                    if (strstr(sylab, bonus2))
                        score *= double_bonus(pos[i], pos[i + 1], 1, word);

                    if (strstr(word, bonus1))
                        score *= simple_bonus(pos[i], pos[i + 1], 1, word);

                    // if two words produce the maximum
                    // then I select the one with the smallest row
                    // if the rows are equal, the one with the smallest column

                    if (max == score && pos[i] < poz1_max) {
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 1;
                        strcpy(word_max, word);
                    }

                    else if (max == score && pos[i] == poz1_max &&
                            pos[i + 1] < poz2_max) {
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 1;
                        strcpy(word_max, word);
                    }

                    // if the score is greater than the maximum
                    // I remember the position and the new maximum

                    if (max < score) {
                        max = score;
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 1;
                        strcpy(word_max, word);
                    }
                }

                score = 0;
                if (horiz_check(game_board, word, pos[i], pos[i + 1])) {
                    score = score_check(word);

                    if(strstr(sylab, bonus2))
                        score *= double_bonus(pos[i], pos[i + 1], 0, word);

                    if(strstr(word, bonus1))
                        score *= simple_bonus(pos[i], pos[i + 1], 0, word);

                    if (max == score && pos[i] < poz1_max) {
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 0;
                        strcpy(word_max, word);
                    }

                    else if (max == score && pos[i] == poz1_max &&
                            pos[i + 1] < poz2_max) {
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 0;
                        strcpy(word_max, word);
                    }

                    if (max < score) {
                        max = score;
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 0;
                        strcpy(word_max, word);
                    }
                }
            }
        }
        score = 0;
        count = 0;
        k++;
        ok = 0;
    }
    // if the maximum
    // is greater or equal than the gap
    // the word is placed on the board
    if (max >= dif) {
        word_inputter(game_board, poz1_max, poz2_max, dir_max, word_max);
        print_board(game_board);
    }
    // otherwise FAIL
    else
        printf("Fail!\n");
}

void task_5(char game_board[SIZE][SIZE])
{
    task_0(game_board);
    char n[STRSIZE], col[STRSIZE], row[STRSIZE], dir[STRSIZE], word[16];
    char buffer[BUFFERSIZE];
    char sylab[STRSIZE], bonus1[STRSIZE], bonus2[STRSIZE];
    int player1_score, player2_score, round_score, dif;
    int i, len;
    len = 100;

    fgets(buffer, BUFFERSIZE, stdin);
    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    strncpy(bonus1, buffer, STRSIZE);

    fgets(buffer, BUFFERSIZE, stdin);
    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    strncpy(bonus2, buffer, STRSIZE);

    fgets(buffer, BUFFERSIZE, stdin);
    strncpy(n, buffer, STRSIZE);

    player1_score = 0;
    player2_score = 0;
    round_score = 0;
    // same as task 3
    // but I also update the word array and the board

    for (i = 0; i < atoi(n); i++) {
        fgets(buffer, BUFFERSIZE, stdin);

        strncpy(row, strtok(buffer, " "), STRSIZE);
        strncpy(col, strtok(NULL, " "), STRSIZE);
        strncpy(dir, strtok(NULL, " "), STRSIZE);
        strncpy(word, strtok(NULL, " "), 16);

        if (word[strlen(word) - 1] == '\n')
            word[strlen(word) - 1] = '\0';

        strcpy(sylab, word + strlen(word) - 2);
        
        if (i % 2 == 0) {
            round_score += score_check(word);

            if (strstr(sylab, bonus2))
                round_score *= double_bonus(atoi(row), atoi(col),
                                            atoi(dir), word);
            if (strstr(word, bonus1))
                round_score *= simple_bonus(atoi(row), atoi(col),
                                            atoi(dir), word);

            player1_score += round_score;
            round_score = 0;
        }

        else {
            round_score += score_check(word);
            if(strstr(sylab, bonus2))
                round_score *= double_bonus(atoi(row), atoi(col),
                                            atoi(dir), word);

            if(strstr(word, bonus1))
                round_score *= simple_bonus(atoi(row), atoi(col),
                                            atoi(dir), word);

            player2_score += round_score;
            round_score = 0;
        }

        word_inputter(game_board, atoi(row), atoi(col), atoi(dir), word);
        word_remover(word, &len);
    }
    // the gap
    dif = player1_score - player2_score;
    // the best move
    perfect_move(game_board, len, dif, bonus1, bonus2);
}

// BONUS //

void player2_move(char game_board[SIZE][SIZE], int *len, char *bonus1,
                  char *bonus2, int *player_score)
{
    int k, i, j, pos[40], count, ok = 0, max = 0;
    char word[16], word_max[16], sylab[STRSIZE];
    int poz1_max, poz2_max, dir_max;
    int score = 0;
    
    k = 0;

    while (k < *len) {
        strcpy(word, words[k]);
        strncpy(sylab, word + strlen(word) - 2, 2);
        count = 0;

        for (i = 0; i < SIZE; i++)
            for (j = 0; j < SIZE; j++)
                if (word[0] == game_board[i][j]) {
                    pos[count] = i;
                    pos[count + 1] = j;
                    count += 2;
                    ok = 1;
                }

        if (ok == 1) {
            for (i = 0; i < count; i += 2) {

                if (vert_check(game_board, word, pos[i], pos[i + 1])) {
                    score = score_check(word);

                    if(strstr(sylab, bonus2))
                        score *= double_bonus(pos[i], pos[i + 1], 1, word);

                    if(strstr(word, bonus1))
                        score *= simple_bonus(pos[i], pos[i + 1], 1, word);

                    if (max == score && pos[i] < poz1_max) {
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 1;
                        strcpy(word_max, word);
                    }

                    else if (max == score && pos[i] == poz1_max &&
                            pos[i + 1] < poz2_max) {
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 1;
                        strcpy(word_max, word);
                    }

                    if (max < score) {
                        max = score;
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 1;
                        strcpy(word_max, word);
                    }
                }
                
                score = 0;

                if (horiz_check(game_board, word, pos[i], pos[i + 1])) {

                    score = score_check(word);

                    if (strstr(sylab, bonus2))
                        score *= double_bonus(pos[i], pos[i + 1], 0, word);

                    if (strstr(word, bonus1))
                        score *= simple_bonus(pos[i], pos[i + 1], 0, word);

                    if (max == score && pos[i] < poz1_max) {
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 0;
                        strcpy(word_max, word);
                    }

                    else if (max == score && pos[i] == poz1_max &&
                            pos[i + 1] < poz2_max) {
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 0;
                        strcpy(word_max, word);
                    }

                    if (max < score) {
                        max = score;
                        poz1_max = pos[i];
                        poz2_max = pos[i + 1];
                        dir_max = 0;
                        strcpy(word_max, word);
                    }
                }
            }
        }
        score = 0;
        count = 0;
        k++;
        ok = 0;
    }
    *player_score += max;
    word_inputter(game_board, poz1_max, poz2_max, dir_max, word_max);
    word_remover(word_max, len);

}

void task_6(char game_board[SIZE][SIZE])
{
    task_0(game_board);
    char n[STRSIZE], col[STRSIZE], row[STRSIZE], dir[STRSIZE], word [16];
    char buffer[BUFFERSIZE];
    char sylab[STRSIZE], bonus1[STRSIZE], bonus2[STRSIZE];
    int player1_score, player2_score, round_score;
    int i, len;
    len = 100;

    fgets(buffer, BUFFERSIZE, stdin);
    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    strncpy(bonus1, buffer, STRSIZE);

    fgets(buffer, BUFFERSIZE, stdin);
    if(buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    strncpy(bonus2, buffer, STRSIZE);

    fgets(buffer, BUFFERSIZE, stdin);
    strncpy(n, buffer, STRSIZE);

    player1_score = 0;
    player2_score = 0;
    round_score = 0;

    // for every round I calculate the scores
    // and I put the words on the table and update the word array

    for (i = 0; i < 2 * atoi(n); i++) {
       if (i % 2 == 0){
            fgets(buffer, BUFFERSIZE, stdin);

            strncpy(row, strtok(buffer, " "), STRSIZE);
            strncpy(col, strtok(NULL, " "), STRSIZE);
            strncpy(dir, strtok(NULL, " "), STRSIZE);
            strncpy(word, strtok(NULL, " "), 16);

            if (word[strlen(word) - 1] == '\n')
                word[strlen(word) - 1] = '\0';

            strcpy(sylab, word + strlen(word) - 2);

            round_score += score_check(word);

            if (strstr(sylab, bonus2))
                round_score *= double_bonus(atoi(row), atoi(col),
                                            atoi(dir), word);
            if (strstr(word, bonus1))
                    round_score *= simple_bonus(atoi(row), atoi(col),
                                                atoi(dir), word);

            player1_score += round_score;
            round_score = 0;

            word_inputter(game_board, atoi(row), atoi(col), atoi(dir), word);
            word_remover(word, &len);
        }
            else
                player2_move(game_board, &len, bonus1, bonus2, &player2_score);
    }

    print_board(game_board);

    if (player1_score > player2_score)
        printf("Player 1 Won!\n");
    else
        printf("Player 2 Won!\n");

}

int main()
{
    char test_id[3];
    fgets(test_id, 3, stdin);
    char game_board[SIZE][SIZE];

    switch (test_id[0]) {  // identifying the test id
        case '0':
            task_0(game_board);
            print_board(game_board);
            break;

        case '1':
            task_1(game_board);
            print_board(game_board);
            break;
        
        case '2':
            task_2();
            break;

        case '3':
            task_3();
            break;

        case '4':
            task_4(game_board);
            break;

        case '5':
            task_5(game_board);
            break;

        case '6':
            task_6(game_board);
            break;
    }
    return 0;
}