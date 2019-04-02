cmake_minimum_required(VERSION 3.13)
project(INFO0027-Project_1)

set(CMAKE_C 11)

add_executable(Boggle
        src/main.c
        src/hashtable/hash.h src/hashtable/hash.c
        src/hashtable/hashtable_char_int.h src/hashtable/hashtable_char_int.c
        src/hashtable/hashtable_char_node.h src/hashtable/hashtable_char_node.c
        src/pair/pair_int_int.h src/pair/pair_int_int.c
        src/stack/stack_pair.h src/stack/stack_pair.c
        src/tree/tree.h src/tree/tree.c)