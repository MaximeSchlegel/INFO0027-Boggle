#include "hashtable/hashtable_char_int.h"
#include "tree/tree.h"
#include "stack/stack_probe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (int argc, char **argv) {
    if (argc != 3) {
        printf("Invalid Arguments");
        return -1;
    }
    FILE *gridFile = fopen(argv[1], "r");
    if (!gridFile) {
        printf("Can Not Open Grid File");
        return -1;
    }
    FILE *dictionaryFile = fopen(argv[2], "r");
    if (!dictionaryFile) {
        printf("Can Not Open Dictionary File");
        return -1;
    }

    char **grid;
    grid = malloc(sizeof(char *));
    grid[0] = NULL;
    // hold the array of letter that represent each cell

    int *letterNumber;
    letterNumber = malloc(sizeof(int));
    letterNumber[0] = 0;
    // hold the number of letter in the cell

    HashTable_CI availableLetter;
    availableLetter = HashTable_CI_create();
    //hold the list of letter encounter in the grid in order to minimize the tree of word extract from the dictionnary file

    int width = 0, height = 0, maxWidth = 1;
    char ch;

    while((ch = fgetc(gridFile)) != EOF) {
        // go through the input grid
        printf("w:%i, ", width);
        printf("h:%i, ", height);
        printf("mW:%i, ", maxWidth);
        printf("lN:%i : ", letterNumber[width + height * maxWidth]);

        if (ch == '\n') {
            printf("EOL :\n");
            if (height == 0) {
                // it's the first EOL, so the size of the grid is known => maxWidth * maxWidth
                // create the array of the right size to hold all the grid
                printf("        resize grid begin\n");

                char **gridTmp;
                gridTmp = malloc(sizeof(char *) * maxWidth * maxWidth);
                for (int i = 0; i < maxWidth; i++) {
                    gridTmp[i] = grid[i];
                }
                for (int i = maxWidth; i < maxWidth * maxWidth; i++) {
                    gridTmp[i] = NULL;

                }
                free(grid);
                grid = gridTmp;
                printf("          done\n");

                printf("        resize letterNumber begin\n");
                int *letterTmp;
                letterTmp = malloc(sizeof(int) * maxWidth * maxWidth);
                printf("          malloc tmp done\n");
                for (int i = 0; i < maxWidth; i++) {
                    letterTmp[i] = letterNumber[i];
                }
                printf("\n          reassign done\n");
                for (int i = maxWidth; i < maxWidth * maxWidth; i++) {
                    letterTmp[i] = 0;
                }
                printf("          assgin done\n");
                free(letterNumber);
                printf("          free done\n");
                letterNumber = letterTmp;
                printf("          done\n");
            }
            //increase height by one and go to the first cell
            height++;
            width = 0;
        } else if (ch == ' ') {
            printf("SPACE :\n");
            if (height == 0) {
                // we are on the first line so the size of the grid is unknown
                // we increase the size of both array by 1 to hold the next value
                printf("        begin resize grid\n");
                char **gridTmp;
                gridTmp = malloc(sizeof(char *) * (maxWidth + 1));
                for (int i = 0; i < maxWidth; i++) {
                    gridTmp[i] = grid[i];
                }
                gridTmp[maxWidth] = NULL;
                free(grid);
                grid = gridTmp;
                printf("          done\n");

                printf("        begin resize letterNumber\n");
                int *letterTmp;
                letterTmp = malloc(sizeof(int) * (maxWidth + 1));
                for (int i = 0; i < maxWidth; i++) {
                    letterTmp[i] = letterNumber[i];
                }
                letterTmp[maxWidth] = 0;
                free(letterNumber);
                letterNumber = letterTmp;
                printf("          done\n");
                maxWidth++;
            }
            //go to the next cell
            width++;
        } else {
            printf("%c :\n", ch);
            int cellId = width + height * maxWidth;

            if (letterNumber[cellId] == 0) {
                //this is the first letter of the cell, we initialize the array for the cell
                printf("        new cell\n");
                grid[cellId] = malloc(sizeof(char));
                printf("          done\n");
            } else {
                // this is not th first letter, we must increase the array size to hold it
                printf("        cell size increase\n");
                char *cellTmp;
                cellTmp = malloc(sizeof(char) * (letterNumber[cellId] + 1));
                for (int i = 0; i < letterNumber[cellId]; i++) {
                    cellTmp[i] = grid[cellId][i];
                }
                free(grid[cellId]);
                grid[cellId] = cellTmp;
                printf("          done\n");
            }
            //add the letter to the cell and increase the number of letter by one
            printf("        add letter\n");
            grid[cellId][letterNumber[cellId]] = ch;
            letterNumber[cellId]++;
            if (ch != '#') {
                //if ch is a letter we add it to the list of the letter
                if (HashTable_CI_exist(availableLetter, ch) == 0) {
                    HashTable_CI_add(availableLetter, ch, 1);
                } else {
                    int current = HashTable_CI_find(availableLetter, ch);
                    HashTable_CI_edit(availableLetter, ch, current + 1);
                }
            }
            printf("          done\n");
        }
        printf("\n");
    }

    printf("\n");

    printf("grid size : %i\n", maxWidth);
    printf("Grid :\n");

    for(int i = 0; i < maxWidth * maxWidth; i++) {
        for (int j = 0; j < letterNumber[i]; j++) {
            printf("%c", grid[i][j]);
        }
        printf(" ");
        if ((i + 1) % maxWidth == 0) {
            printf("\n");
        }
    }

    printf("Program Finish !\n");
    free(grid);
    free(letterNumber);

    HashTable_CI_free(availableLetter);
    return 0;
}
