#ifndef INFO0027_PROJECT_1_TREE_H
#define INFO0027_PROJECT_1_TREE_H

typedef struct TreeNode_ * TreeNode;
typedef struct Tree_ * Tree;

#include "../hashtable/hashtable_char_node.h"


struct TreeNode_{
    HashTable_CN children;
    int isWord;
};

struct Tree_ {
    TreeNode root;
    int nodeSize;
};
Tree Tree_create(int nodeSize);
void Tree_addWord(Tree tree, char * word);
int Tree_isWord(Tree tree, char * word);
void Tree_free(Tree);
void TreeNode_free(TreeNode node);



#endif //INFO0027_PROJECT_1_TREE_H
