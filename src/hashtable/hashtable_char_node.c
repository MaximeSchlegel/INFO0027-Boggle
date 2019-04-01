#include "hashtable_char_node.h"
#include "hash.h"
#include <stdlib.h>
//#include <stdio.h>


Bucket_CN Bucket_CN_create(char key, TreeNode value) {
//    printf("   Create Bucket\n");
    Bucket_CN elements = malloc(sizeof(Bucket_CN *));
    elements->key = key;
    elements->value = value;
//    printf("   Finish\n");
    return elements;
}

void Bucket_CN_free(Bucket_CN element) {
    TreeNode_free(element->value);
    free(element);
}

HashTable_CN HashTable_CN_create(int size) {
//    printf("    Create HashTable\n");
    HashTable_CN table = (HashTable_CN) malloc(sizeof(HashTable_CN *));
    table->size = size;
    table->isEmpty = 1;
    table->elements = malloc(sizeof(Bucket_CN) * size);
    for (int i=0; i < size; i++) {
        table->elements[i] = NULL;
    }
//    printf("    HashTable Created\n");
    return table;
}

int HashTable_CN_isEmpty(HashTable_CN table) {
    return table->isEmpty;
}

void HashTable_CN_add(HashTable_CN table, char key, TreeNode value) {
    table->isEmpty = 0;
    Bucket_CN element = Bucket_CN_create(key, value);
    int insertPosition = hashChar(table->size, key);
    while (table->elements[insertPosition]) {
        insertPosition++;
    }
    table->elements[insertPosition] = element;
}

int HashTable_CN_exist(HashTable_CN table, char key) {
    int findPosition = hashChar(table->size, key);
    while (findPosition < table->size - 1) {
        if (table->elements[findPosition] && table->elements[findPosition]->key == key) {
            return 1;
        }
        findPosition++;
    }
    return 0;
}

TreeNode HashTable_CN_find(HashTable_CN table, char key) {
    int findPosition = hashChar(table->size, key);
    while (findPosition < table->size) {
        if (table->elements[findPosition] && table->elements[findPosition]->key == key) {
            return table->elements[findPosition]->value;
        }
        findPosition++;
    }
    return NOTFOUNDNODE;
}

void HashTable_CN_free(HashTable_CN table) {
    if (!table) {
        return;
    }
    for (int i=0; i < table->size; i++) {
        if (table->elements[i]) {
            Bucket_CN_free(table->elements[i]);
        }
    }
    free(table->elements);
    free(table);
}