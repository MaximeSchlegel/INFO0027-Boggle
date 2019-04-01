#include "hashtable/hashtable_char_int.h"
#include "probe/probe.h"
#include "stack/stack_probe.h"
#include "tree/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
    // The args must be the grid file and the dictionary file
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


    printf("\n\nGRID ANALYSIS\n");
    // First Analysis of the grid
    //   => extract the cells and put them in an usable form
    //   => extract the letters available to construct the words

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

    while ((ch = fgetc(gridFile)) != EOF) {
        // go through the input grid
//        printf("w:%i, ", width);
//        printf("h:%i, ", height);
//        printf("mW:%i, ", maxWidth);
//        printf("lN:%i : ", letterNumber[width + height * maxWidth]);

        if (ch == '\n') {
//            printf("EOL :\n");
            if (height == 0) {
                // it's the first EOL, so the size of the grid is known => maxWidth * maxWidth
                // create the array of the right size to hold all the grid
//                printf("        resize grid begin\n");

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
//                printf("          done\n");

//                printf("        resize letterNumber begin\n");
                int *letterTmp;
                letterTmp = malloc(sizeof(int) * maxWidth * maxWidth);
//                printf("          malloc tmp done\n");
                for (int i = 0; i < maxWidth; i++) {
                    letterTmp[i] = letterNumber[i];
                }
//                printf("\n          reassign done\n");
                for (int i = maxWidth; i < maxWidth * maxWidth; i++) {
                    letterTmp[i] = 0;
                }
//                printf("          assgin done\n");
                free(letterNumber);
//                printf("          free done\n");
                letterNumber = letterTmp;
//                printf("          done\n");
            }
            //increase height by one and go to the first cell
            height++;
            width = 0;
            if (height > maxWidth) {
                printf("Incorrect format for the grid file");
                return 1;
            }
        } else if (ch == ' ') {
//            printf("SPACE :\n");
            if (height == 0) {
                // we are on the first line so the size of the grid is unknown
                // we increase the size of both array by 1 to hold the next value
//                printf("        begin resize grid\n");
                char **gridTmp;
                gridTmp = malloc(sizeof(char *) * (maxWidth + 1));
                for (int i = 0; i < maxWidth; i++) {
                    gridTmp[i] = grid[i];
                }
                gridTmp[maxWidth] = NULL;
                free(grid);
                grid = gridTmp;
//                printf("          done\n");

//                printf("        begin resize letterNumber\n");
                int *letterTmp;
                letterTmp = malloc(sizeof(int) * (maxWidth + 1));
                for (int i = 0; i < maxWidth; i++) {
                    letterTmp[i] = letterNumber[i];
                }
                letterTmp[maxWidth] = 0;
                free(letterNumber);
                letterNumber = letterTmp;
//                printf("          done\n");
                maxWidth++;
            }
            //go to the next cell
            width++;
            if (width > maxWidth) {
                printf("Incorrect format for the grid file");
                return 1;
            }
        } else {
//            printf("%c :\n", ch);
            int cellId = width + height * maxWidth;

            if (letterNumber[cellId] == 0) {
                //this is the first letter of the cell, we initialize the array for the cell
//                printf("        new cell\n");
                grid[cellId] = malloc(sizeof(char) * 2);
                for (int i = 0; i < 2; i++) {
                    grid[cellId][i] = '\0';
                }
//                printf("          done\n");
            } else {
                // this is not th first letter, we must increase the array size to hold it
//                printf("        cell size increase\n");
                char *cellTmp;
                cellTmp = malloc(sizeof(char) * (letterNumber[cellId] + 2));
                for (int i = 0; i < letterNumber[cellId]; i++) {
                    cellTmp[i] = grid[cellId][i];
                }
                cellTmp[letterNumber[cellId] + 1] = '\n';
                free(grid[cellId]);
                grid[cellId] = cellTmp;
//                printf("          done\n");
            }
            //add the letter to the cell and increase the number of letter by one
//            printf("        add letter\n");
            grid[cellId][letterNumber[cellId]] = ch;
            letterNumber[cellId]++;
            if (ch != '#') {
                //if ch is a letter we add it to the list of the letter
                int current;
                if ((current = HashTable_CI_find(availableLetter, ch)) == NOTFOUNDINT) {
                    HashTable_CI_add(availableLetter, ch, 1);
                } else {
                    HashTable_CI_edit(availableLetter, ch, current + 1);
                }
            }
//            printf("          done\n");
        }
//        printf("\n");
    }

//    printf("\n");

    printf("grid size : %i\n", maxWidth);
    printf("Grid :\n");

    for (int i = 0; i < maxWidth * maxWidth; i++) {
        for (int j = 0; j < letterNumber[i]; j++) {
            printf("%c", grid[i][j]);
        }
        printf(" ");
        if ((i + 1) % maxWidth == 0) {
            printf("\n");
        }
    }


    printf("\n\nDICT ANALYSIS\n");
    // Analysis of the dictionnary file
    //   => extract the word than can be contructed with the available letters

    Tree words;
    words = Tree_create(availableLetter->size);
    // holds the prefix tree of the available words

    HashTable_CI encounterLetter;
    encounterLetter = HashTable_CI_create();
    //holds the encouter letter in the current word to check against the available letter

    char *wordBuffer;
    wordBuffer = malloc(sizeof(char) * 7);
    for (int i = 0; i < 7; i++) {
        wordBuffer[i] = '\0';
    }
    // according to https://sci-hub.se/https://www.sciencedirect.com/science/article/pii/0378375886901692
    // 7 is the mean of the english word length

    int wordLen = 0, bufferSize = 7, skipline = 0;

    while ((ch = fgetc(dictionaryFile)) != EOF) {
        if (ch == '\n') {
            if (skipline == 0) {
                // if we don't have to skip the line we had the word to the tree
                printf("  Word added");
                Tree_addWord(words, wordBuffer);
            } else {
                printf("  Word skiped  ");
            }
            // at the end of the line we reinitialize the word buffer and the encounter letters
            free(wordBuffer);
            wordBuffer = malloc(sizeof(char) * 7);
            for (int i = 0; i < 7; i++) {
                wordBuffer[i] = '\0';
            }
            HashTable_CI_free(encounterLetter);
            encounterLetter = HashTable_CI_create();
            wordLen = 0;
            bufferSize = 7;
            skipline = 0;
        } else if (skipline == 0) {
            int current = HashTable_CI_find(encounterLetter, ch);
            if (current == NOTFOUNDINT) {
                HashTable_CI_add(encounterLetter, ch, 1);
            } else {
                HashTable_CI_edit(encounterLetter, ch, current + 1);
            }
            int available = HashTable_CI_find(availableLetter, ch);
            if (available == NOTFOUNDINT || available < current + 1) {
                skipline = 1;
            } else {
                if (wordLen == bufferSize - 1) {
                    char *wordTmp;
                    wordTmp = malloc(sizeof(char) * (bufferSize + 1));
                    for (int i = 0; i < wordLen; i++) {
                        wordTmp[i] = wordBuffer[i];
                    }
                    wordBuffer[bufferSize] = '\0';
                    free(wordBuffer);
                    wordBuffer = wordTmp;
                    bufferSize++;
                }
                wordBuffer[wordLen] = ch;
                wordLen++;
            }
        }
        printf("%c", ch);
    }


    printf("%i\n", Tree_isWord(words, "BA"));
    printf("%i\n", Tree_isWord(words, "BAU"));
    printf("%i\n", Tree_isWord(words, "ZAP"));




    printf("\n\nPROBE CREATION\n");
    //create the probe for each sell
    Stack_P stack;
    stack = Stack_P_create(maxWidth * maxWidth);
    //hold all the probes

    TreeNode currentNode;
    int skipCell = 0;

    for (int i = 0; i < maxWidth * maxWidth; i++) {
        currentNode = words->root;
        skipCell = 0;
        for (int j = 0; j < letterNumber[i] && skipCell == 0; j++) {
            if (grid[i][j] == '#' || HashTable_CN_isEmpty(currentNode->children)
                || (currentNode = HashTable_CN_find(currentNode->children, grid[i][j])) == NOTFOUNDNODE) {
                // we skip the sell if the symbol is the end one, the Node don't have anymore child
                // or if no child is accessible with the letter
                skipCell = 1;
            }
        }
        if (skipCell == 0) {
            // if we found a child that answer all the criteria we create a new probe that will start at that position
            printf("Add Probe %s\n", grid[i]);
            int height = i / maxWidth;
            int width = i % maxWidth;
            Probe probe = Probe_create(width, height, grid[i], currentNode);
            Stack_P_add(stack, probe);
        }
    }



//    for (int i = 0; i < maxWidth * maxWidth; i++) {
//        free(grid[i]);
//    }
//    free(grid);
//    free(letterNumber);
//    HashTable_CI_free(availableLetter);
//    HashTable_CI_free(encounterLetter);
//    HashTable_CI_free(encounterLetter);
//    Tree_free(words);
    printf("Program Finish !\n");
    return 0;
}
