#ifndef INFO0027_PROJECT_1_HASHTABLE_CHAR_INT_H
#define INFO0027_PROJECT_1_HASHTABLE_CHAR_INT_H

#define NOTFOUNDINT -999
typedef struct Bucket_CI_ * Bucket_CI;
typedef struct HashTable_CI_ * HashTable_CI;


struct Bucket_CI_ {
    char key;
    int value;
};

struct HashTable_CI_ {
    int size;
    int used;
    Bucket_CI * elements;
};


HashTable_CI HashTable_CI_create();  // create a new hashtable
void HashTable_CI_add(HashTable_CI table, char key, int value);  // add a pair (key, value) to the hashtable
int HashTable_CI_isEmpty(HashTable_CI table);  // test if the table is empty
int HashTable_CI_exist(HashTable_CI table, char key);  // test if a key exist in the table
int HashTable_CI_find(HashTable_CI table, char key);  // if the key exist return the value link to it
void HashTable_CI_edit(HashTable_CI table, char key, int newValue);  //change the value for the given key to the newValue
void HashTable_CI_free(HashTable_CI table);  // destructor of the table and recursivly destroy of the bucket

#endif //INFO0027_PROJECT_1_HASHTABLE_CHAR_INT_H
