#include "hashtable_char_int.h"
#include "hash.h"
#include <stdlib.h>


Bucket_CI Bucket_CI_create(char key, int value) {
    Bucket_CI element = malloc(sizeof(Bucket_CI *));
    element->key = key;
    element->value = value;
    return element;
}

void Bucket_CI_free(Bucket_CI element) {
    free(element);
}


HashTable_CI HashTable_CI_create(int size) {
    HashTable_CI table;
    table = malloc(sizeof(HashTable_CI *));
    table->size = size;
    table->isEmpty = 1;
    table->elements = malloc(sizeof(Bucket_CI) * size);
    for (int i=0; i < size; i++) {
        table->elements[i] = NULL;
    }
    return table;
}

int HashTable_CI_isEmpty(HashTable_CI table) {
    return table->isEmpty;
}

void HashTable_CI_add(HashTable_CI table, char key, int value) {
    table->isEmpty = 0;
    Bucket_CI element = Bucket_CI_create(key, value);
    int insertPosition = hashChar(table->size, key);
    while (table->elements[insertPosition]) {
        insertPosition++;
    }
    table->elements[insertPosition] = element;
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

void HashTable_CI_free(HashTable_CI table) {
    for (int i=0; i < table->size; i++) {
        Bucket_CI_free(table->elements[i]);
    }
    free(table->elements);
    free(table);
}