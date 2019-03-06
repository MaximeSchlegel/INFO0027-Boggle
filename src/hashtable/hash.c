#include "hash.h"


int hashChar(int size, char key) {
    return (key - 'A') % size;
}