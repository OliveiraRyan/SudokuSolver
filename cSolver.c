#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "time_util.h"

typedef enum {F,T} boolean;

int board[9][9] = {
    {0,0,1,2,0,3,4,0,0},
    {0,0,0,6,0,7,0,0,0},
    {5,0,0,0,0,0,0,0,3},
    {3,7,0,0,0,0,0,8,1},
    {0,0,0,0,0,0,0,0,0},
    {6,2,0,0,0,0,0,3,7},
    {1,0,0,0,0,0,0,0,8},
    {0,0,0,8,0,5,0,0,0},
    {0,0,6,4,0,2,5,0,0}
};

int const MAX_VALUE = 9;
int const BOARD_SIZE = 9;

// int num_solutions = 0;
int keep_going = 0;

// Prints the current board state, formatted to look like a sudoku grid
void print_board(){
    printf(" ───────────────────────\n");
    for(int i = 0; i < BOARD_SIZE; i++){
        if (i%3 == 0 && i != 0){
            printf(" ───────────────────────\n");
        }
        for (int j = 0; j < BOARD_SIZE; j++){
            if (j%3 == 0){
                printf("| ");
            }
            
            if (j == 8){
                printf("%d |\n", board[i][j]);
            } else {
                printf("%d ", board[i][j]);
            }
        }
    } 
    printf(" ───────────────────────\n");
    return;
}


// Returns a boolean enum, T if current board state is valid, F otherwise
boolean is_valid(int num, int row, int col){
    int box_x = col/3;
    int box_y = row/3;

    // check row
    for (int i = 0; i < BOARD_SIZE; i++){
        if (board[row][i] == num && col != i){
            return F;
        }
    }

    // check col
    for (int i = 0; i < BOARD_SIZE; i++){
        if (board[i][col] == num && row != i){
            return F;
        }
    }

    // check box
    for (int i = box_y*3; i < box_y*3 + 3; i++){
        for (int j = box_x*3; j < box_x*3 + 3; j++){
            if (board[i][j] == num && i != row && j != col){
                return F;
            }
        }
    }

    return T;
}


// Recursive function that uses backtracking to solve the initial board
int solve(int r, int c){
    // printf("%d, %d", r, c);
    int found_solutions = 0;

    // int co;
    // for (int row = r; row < MAX_VALUE; row++){
    //     if (row == r){
    //         co = c;
    //     } else {
    //         co = 0;
    //     }

    //     for (int col = co; col < MAX_VALUE; col ++){

    int ro;
    for (int col = c; col < MAX_VALUE; col++){
        // printf("col: %d\n", col);
        if (col == c){
            ro = r;
        } else {
            ro = 0;
        }

        for (int row = ro; row < MAX_VALUE; row ++){



            if (board[row][col] == 0){
                for (int n = 1; n < 10; n++){
                    // printf("n: %d\n", n);
                    // printf("valid: %d\n", is_valid(n, row, col) == T);
                    if (is_valid(n, row, col) == T){
                        board[row][col] = n;
                        found_solutions += solve(row, col);
                        board[row][col] = 0;
                    }
                }
                return found_solutions;
            }



        }
    }

    // num_solutions ++;
    if (keep_going == 0){
        printf("\nSolved board:\n");
        print_board();
    }

    if (keep_going == 1){
        char answer;
        while (tolower(answer) != 'y' && tolower(answer) != 'n'){
            printf("This board does not have a unique solution. Keep going and count the number of solutions? [Y/n] ");
            scanf("%c", &answer);  
        }
            

        if (tolower(answer) == 'y'){
            keep_going = -1;
        } else {
            exit(0);
        }
    } 
    

    return 1;
}





int main(int argc, char** argv){
    printf("Unsolved board:\n");
    print_board();

    struct timespec start, stop;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int num_solutions = solve(0,0);
    clock_gettime(CLOCK_MONOTONIC, &stop);

    struct timespec diff = difftimespec(stop, start);
    double time = timespec_to_sec(diff);

    printf("The number of unique solutions: %d\n", num_solutions);
    printf("Checking all possibilities took %f seconds", time);

    return 0;
}