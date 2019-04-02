#include "hashtable/hashtable_char_int.h"
#include "probe/probe.h"
#include "stack/stack_probe.h"
#include "tree/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Data_ * Data;
typedef struct History_ History;
typedef struct Pair_II_ * Pair_II;

struct Data_ {
    int width;
    char **grid;
    int *letterNumber;
    HashTable_CI availableLetter;
    Tree dictionary;
};

struct History_ {
    int size;
    int used;
    Pair_II *array;
};


struct Pair_II_ {
    int first;
    int second;
};

// NE MARCHE PAS MAIS JE COMPRENDS PAS PK
//Data analysisGrid(FILE *gridFile) {
//    printf("\n\nGRID ANALYSIS\n");
//    // Analysis of the grid
//    //   => extract the cells and put them in an usable form
//    //   => extract the letters available to construct the words
//
//    char **grid;
//    grid = malloc(sizeof(char *));
//    grid[0] = NULL;
//    // hold the array of letter that represent each cell
//
//    int *letterNumber;
//    letterNumber = malloc(sizeof(int));
//    letterNumber[0] = 0;
//    // hold the number of letter in the cell
//
//    HashTable_CI availableLetter;
//    availableLetter = HashTable_CI_create();
//    //hold the list of letter encounter in the grid in order to minimize the tree of word extract from the dictionnary file
//
//    int width = 0, height = 0, maxWidth = 1;
//    char ch;
//
//    while ((ch = fgetc(gridFile)) != EOF) {
//        // go through the input grid
//
//        if (ch == '\n') {
//            if (height == 0) {
//                // it's the first EOL, so the size of the grid is known => maxWidth * maxWidth
//                // create the array of the right size to hold all the grid
//                char **gridTmp;
//                gridTmp = malloc(sizeof(char *) * maxWidth * maxWidth);
//                for (int i = 0; i < maxWidth; i++) {
//                    gridTmp[i] = grid[i];
//                }
//                for (int i = maxWidth; i < maxWidth * maxWidth; i++) {
//                    gridTmp[i] = NULL;
//                }
//                free(grid);
//                grid = gridTmp;
//
//                int *letterTmp;
//                letterTmp = malloc(sizeof(int) * maxWidth * maxWidth);
//                for (int i = 0; i < maxWidth; i++) {
//                    letterTmp[i] = letterNumber[i];
//                }
//                for (int i = maxWidth; i < maxWidth * maxWidth; i++) {
//                    letterTmp[i] = 0;
//                }
//                free(letterNumber);
//                letterNumber = letterTmp;
//            }
//            height++;
//            width = 0;
//            if (height > maxWidth) {
//                printf("Incorrect format for the grid file");
//                return NULL;
//            }
//        } else if (ch == ' ') {
//            if (height == 0) {
//                // we are on the first line so the size of the grid is unknown
//                // we increase the size of both array by 1 to hold the next value
//                char **gridTmp;
//                gridTmp = malloc(sizeof(char *) * (maxWidth + 1));
//                for (int i = 0; i < maxWidth; i++) {
//                    gridTmp[i] = grid[i];
//                }
//                gridTmp[maxWidth] = NULL;
//                free(grid);
//                grid = gridTmp;
//
//                int *letterTmp;
//                letterTmp = malloc(sizeof(int) * (maxWidth + 1));
//                for (int i = 0; i < maxWidth; i++) {
//                    letterTmp[i] = letterNumber[i];
//                }
//                letterTmp[maxWidth] = 0;
//                free(letterNumber);
//                letterNumber = letterTmp;
//                maxWidth++;
//            }
//            //go to the next cell
//            width++;
//            if (width > maxWidth) {
//                printf("Incorrect format for the grid file");
//                return NULL;
//            }
//        } else {
//            int cellId = width + height * maxWidth;
//            if (letterNumber[cellId] == 0) {
//                //this is the first letter of the cell, we initialize the array for the cell
//                grid[cellId] = malloc(sizeof(char) * 2);
//                for (int i = 0; i < 2; i++) {
//                    grid[cellId][i] = '\0';
//                }
//            } else {
//                // this is not th first letter, we must increase the array size to hold it
//                char *cellTmp;
//                cellTmp = malloc(sizeof(char) * (letterNumber[cellId] + 2));
//                for (int i = 0; i < letterNumber[cellId]; i++) {
//                    cellTmp[i] = grid[cellId][i];
//                }
//                cellTmp[letterNumber[cellId] + 1] = '\n';
//                free(grid[cellId]);
//                grid[cellId] = cellTmp;
//            }
//            //add the letter to the cell and increase the number of letter by one
//            grid[cellId][letterNumber[cellId]] = ch;
//            letterNumber[cellId]++;
//            if (ch != '#') {
//                //if ch is a letter we add it to the list of the letter
//                int current;
//                if ((current = HashTable_CI_find(availableLetter, ch)) == NOTFOUNDINT) {
//                    HashTable_CI_add(availableLetter, ch, 1);
//                } else {
//                    HashTable_CI_edit(availableLetter, ch, current + 1);
//                }
//            }
//        }
//    }
//
//
//
//    Data output = malloc(sizeof(Data *));
//    output->width = maxWidth;
//    output->grid = grid;
//    output->letterNumber = letterNumber;
//    output->availableLetter = availableLetter;
//    output->dictionary = NULL;
//    return output;
//}


//void analysisDictionary(FILE *dictionaryFile, Data input) {
//    printf("\n\nDICT ANALYSIS\n");
//    // Analysis of the dictionnary file
//    //   => extract the word than can be contructed with the available letters
//
//    Tree words;
//    words = Tree_create(input->availableLetter->size);
//    // holds the prefix tree of the available words
//
//    HashTable_CI encounterLetter;
//    encounterLetter = HashTable_CI_create();
//    //holds the encouter letter in the current word to check against the available letter
//
//    char *wordBuffer;
//    wordBuffer = malloc(sizeof(char) * 7);
//    for (int i = 0; i < 7; i++) {
//        wordBuffer[i] = '\0';
//    }
//    // according to https://sci-hub.se/https://www.sciencedirect.com/science/article/pii/0378375886901692
//    // 7 is the mean of the english word length
//
//    int wordLen = 0, bufferSize = 7, skipline = 0;
//    char ch;
//
//    while ((ch = fgetc(dictionaryFile)) != EOF) {
//        if (ch == '\n') {
//            if (skipline == 0) {
//                // if we don't have to skip the line we had the word to the tree
//                printf("  Word added");
//                Tree_addWord(words, wordBuffer);
//            } else {
//                printf("  Word skiped  ");
//            }
//            // at the end of the line we reinitialize the word buffer and the encounter letters
//            free(wordBuffer);
//            wordBuffer = malloc(sizeof(char) * 7);
//            for (int i = 0; i < 7; i++) {
//                wordBuffer[i] = '\0';
//            }
//            HashTable_CI_free(encounterLetter);
//            encounterLetter = HashTable_CI_create();
//            wordLen = 0;
//            bufferSize = 7;
//            skipline = 0;
//        } else if (skipline == 0) {
//            int current = HashTable_CI_find(encounterLetter, ch);
//            if (current == NOTFOUNDINT) {
//                HashTable_CI_add(encounterLetter, ch, 1);
//            } else {
//                HashTable_CI_edit(encounterLetter, ch, current + 1);
//            }
//            int available = HashTable_CI_find(input->availableLetter, ch);
//            if (available == NOTFOUNDINT || available < current + 1) {
//                skipline = 1;
//            } else {
//                if (wordLen == bufferSize - 1) {
//                    char *wordTmp;
//                    wordTmp = malloc(sizeof(char) * (bufferSize + 1));
//                    for (int i = 0; i < wordLen; i++) {
//                        wordTmp[i] = wordBuffer[i];
//                    }
//                    wordBuffer[bufferSize] = '\0';
//                    free(wordBuffer);
//                    wordBuffer = wordTmp;
//                    bufferSize++;
//                }
//                wordBuffer[wordLen] = ch;
//                wordLen++;
//            }
//        }
//        printf("%c", ch);
//    }
//
//    HashTable_CI_free(encounterLetter);
//    free(wordBuffer);
//
//    input->dictionary = words;
//}


Pair_II Pair_II_create(int first, int second) {
    Pair_II pair = malloc(sizeof(Pair_II *));
    pair->first = first;
    pair->second = second;
    return pair;
}

Pair_II Pair_II_free(Pair_II pair) {
    free(pair);
}



int constructCandidates(Pair_II currentPosition, TreeNode currentNode, History history, Pair_II *candidates, Data data) {
    int nCandidates = 0, x, y, cellId, validCandidate;
    TreeNode node;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            x = currentPosition->first + i;
            y = currentPosition->second + j;
            validCandidate = 1;

            if ((i != 0 || j !=0 ) && 0 <= x && x < data->width && 0 <= y && y < data->width ) {
                //test if the cell is valid
                cellId = x + data->width * y;

                if (data->grid[cellId][0] == '#') {
                    //if the next cell contain the stop sign there no more word to search
                    validCandidate = 0;
                }

                //test if the cell has not already been visited
                for (int k=0; k < history.used && validCandidate == 1; i++){
                    if (history.array[k]->first == x && history.array[k]->second == y) {
                        validCandidate = 0;
                    }
                }

                node = currentNode;
                for (int k = 0; k < data->letterNumber[cellId] && node != NOTFOUNDNODE && validCandidate == 1; k++){
                    //test if there is a node accessible with the letter on the next cell
                    if ((node = HashTable_CN_find(currentNode->children, data->grid[cellId][k])) == NOTFOUNDNODE) {
                        validCandidate = 0;
                    }
                }

                if (validCandidate == 1) {
                    //if the candidate has pass all the test we had it to the list
                    candidates[nCandidates] = Pair_II_create(x, y);
                    nCandidates++;
                }
            }
        }
    }
    return nCandidates;
}


void makeMove(int a[], int k,Data input){
    //TODO: makeMove
    //Update the position
    //Update the current node in the tree;
    //Add the letter to the word
    //Update wordLen
    //Add previous position to the history
}
void unmakeMove(int a[], int k,Data input){
    //TODO: unmakeMove
    //pop the last position of the history
    //Rollback the current positon to the poped one
    //Remove the letter from the word
    //Update the word len
}


void backtrack(Pair_II currentPosition, TreeNode currentNode, char *word, int wordLen, History history, Data input) {
    if (currentNode->isWord) {
        printf("%s\n", word);
        currentNode->isWord = 0;
        // we don't want to send multiple time the same word so when we have found it we don't consider it anymore
    }

    if (!currentNode->children->isEmpty) {
        Pair_II candidates[8];           // Candidates for next position
        int nCandidates;                 // Next position candidate count
        nCandidates = constructCandidates(currentPosition, currentNode, history, candidates, input);

        for (int i = 0; i < nCandidates; i++) {
            //TODO: Main loop of backtrack
//            makeMove(candidates[i], currentNode, word, );
//            backtrack(a, k, input);
//            unmakeMove(a, k, input);
//            if (finished)
//                return;
        }
    }
}






// A GARDER SERVIRA A L'INITIALISATION DU BACKTRACK

//for (int i = 0; i < maxWidth * maxWidth; i++) {
//    currentNode = words->root;
//    skipCell = 0;
//    for (int j = 0; j < letterNumber[i] && skipCell == 0; j++) {
//        if (grid[i][j] == '#' || HashTable_CN_isEmpty(currentNode->children)
//            || (currentNode = HashTable_CN_find(currentNode->children, grid[i][j])) == NOTFOUNDNODE) {
//            // we skip the sell if the symbol is the end one, the Node don't have anymore child
//            // or if no child is accessible with the letter
//            skipCell = 1;
//        }
//    }
//    if (skipCell == 0) {
//        // if we found a child that answer all the criteria we create a new probe that will start at that position
//        printf("Add Probe %s\n", grid[i]);
//        int height = i / maxWidth;
//        int width = i % maxWidth;
//        Probe probe = Probe_create(width, height, grid[i], currentNode);
//        Stack_P_add(stack, probe);
//    }
//}






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
    // Analysis of the grid
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

        if (ch == '\n') {
            if (height == 0) {
                // it's the first EOL, so the size of the grid is known => maxWidth * maxWidth
                // create the array of the right size to hold all the grid
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

                int *letterTmp;
                letterTmp = malloc(sizeof(int) * maxWidth * maxWidth);
                for (int i = 0; i < maxWidth; i++) {
                    letterTmp[i] = letterNumber[i];
                }
                for (int i = maxWidth; i < maxWidth * maxWidth; i++) {
                    letterTmp[i] = 0;
                }
                free(letterNumber);
                letterNumber = letterTmp;
            }
            height++;
            width = 0;
            if (height > maxWidth) {
                printf("Incorrect format for the grid file");
                return -1;
            }
        } else if (ch == ' ') {
            if (height == 0) {
                // we are on the first line so the size of the grid is unknown
                // we increase the size of both array by 1 to hold the next value
                char **gridTmp;
                gridTmp = malloc(sizeof(char *) * (maxWidth + 1));
                for (int i = 0; i < maxWidth; i++) {
                    gridTmp[i] = grid[i];
                }
                gridTmp[maxWidth] = NULL;
                free(grid);
                grid = gridTmp;

                int *letterTmp;
                letterTmp = malloc(sizeof(int) * (maxWidth + 1));
                for (int i = 0; i < maxWidth; i++) {
                    letterTmp[i] = letterNumber[i];
                }
                letterTmp[maxWidth] = 0;
                free(letterNumber);
                letterNumber = letterTmp;
                maxWidth++;
            }
            //go to the next cell
            width++;
            if (width > maxWidth) {
                printf("Incorrect format for the grid file");
                return -1;
            }
        } else {
            int cellId = width + height * maxWidth;
            if (letterNumber[cellId] == 0) {
                //this is the first letter of the cell, we initialize the array for the cell
                grid[cellId] = malloc(sizeof(char) * 2);
                for (int i = 0; i < 2; i++) {
                    grid[cellId][i] = '\0';
                }
            } else {
                // this is not th first letter, we must increase the array size to hold it
                char *cellTmp;
                cellTmp = malloc(sizeof(char) * (letterNumber[cellId] + 2));
                for (int i = 0; i < letterNumber[cellId]; i++) {
                    cellTmp[i] = grid[cellId][i];
                }
                cellTmp[letterNumber[cellId] + 1] = '\n';
                free(grid[cellId]);
                grid[cellId] = cellTmp;
            }
            //add the letter to the cell and increase the number of letter by one
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
        }
    }

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
                printf("  Word skiped");
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

    HashTable_CI_free(encounterLetter);
    free(wordBuffer);


    printf("%i\n", Tree_isWord(words, "BA"));
    printf("%i\n", Tree_isWord(words, "BAU"));
    printf("%i\n", Tree_isWord(words, "ZAP"));


    Data data = malloc(sizeof(Data *));
    data->width = maxWidth;
    data->grid = grid;
    data->letterNumber = letterNumber;
    data->availableLetter = availableLetter;
    data->dictionary = words;



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
