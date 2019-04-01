#include "hashtable_char_int.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>


Bucket_CI Bucket_CI_create(char key, int value) {
    Bucket_CI element = malloc(sizeof(Bucket_CI *));
    element->key = key;
    element->value = value;
    return element;
}

void Bucket_CI_free(Bucket_CI element) {
    free(element);
}


HashTable_CI HashTable_CI_create() {
    int size = 5;
    HashTable_CI table;
    table = malloc(sizeof(HashTable_CI *));
    table->size = 5;
    table->used = 0;
    table->elements = malloc(sizeof(Bucket_CI) * size);
    for (int i=0; i < size; i++) {
        table->elements[i] = NULL;
    }
    return table;
}

int HashTable_CI_isEmpty(HashTable_CI table) {
    if (table->used == 0) {
        return 1;
    }
    return 0;
}

void HashTable_CI_add(HashTable_CI table, char key, int value) {
    if (table->used * 2 >= table->size) {
        // if we have used more than the half of the hashtable we double it's size (for efficiency reason
        Bucket_CI * elementsTmp = malloc(sizeof(Bucket_CI) * table->size * 2);
        for (int i = 0; i < table->size * 2; ++i) {
            elementsTmp[i] = NULL;
        }
        for (int i=0; i < table->size; i++) {
            if (table->elements[i] != NULL) {
                int insertPosition = hashChar(table->size, table->elements[i]->key);
                while (table->elements[insertPosition]) {
                    insertPosition++;
                }
                elementsTmp[i] = table->elements[i];
            }
        }
        free(table->elements);
        table->elements = elementsTmp;
        table->size = table->size * 2;
    }
    Bucket_CI element = Bucket_CI_create(key, value);
    int insertPosition = hashChar(table->size, key);
    while (table->elements[insertPosition]) {
        insertPosition++;
    }
    table->elements[insertPosition] = element;
    table->used++;
}

int HashTable_CI_exist(HashTable_CI table, char key){
    int findPosition = hashChar(table->size, key);
    while (findPosition < table->size) {
        if (table->elements[findPosition] && table->elements[findPosition]->key == key) {
            return 1;
        }
        findPosition++;
    }
    return 0;
}

int HashTable_CI_find(HashTable_CI table, char key) {
    int findPosition = hashChar(table->size, key);
    while (findPosition < table->size) {
        if (table->elements[findPosition] && table->elements[findPosition]->key == key) {
            return table->elements[findPosition]->value;
        }
        findPosition++;
    }
    return NOTFOUNDINT;
}

void HashTable_CI_edit(HashTable_CI table, char key, int newValue){
    int findPosition = hashChar(table->size, key);
    while (findPosition < table->size) {
        if (table->elements[findPosition] && table->elements[findPosition]->key == key) {
            table->elements[findPosition]->value = newValue;
            return;
        }
        findPosition++;
    }
}

void HashTable_CI_free(HashTable_CI table) {
    if (!table) {
        return;
    }
    for (int i=0; i < table->size; i++) {
        if (table->elements[i]) {
            Bucket_CI_free(table->elements[i]);
        }
    }
    free(table->elements);
    free(table);
}