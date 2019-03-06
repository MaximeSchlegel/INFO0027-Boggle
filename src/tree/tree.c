#include "tree.h"
#include <malloc.h>
//#include <stdio.h>

TreeNode TreeNode_create(int nodeSize) {
//    printf("   Create Node\n");
    TreeNode treeNode = malloc(sizeof(TreeNode *));
//    printf("    Malloc Ended\n");
    treeNode->isWord = 0;
    treeNode->children = HashTable_CN_create(nodeSize);
//    printf("   Node Created\n");
    return treeNode;
}

void TreeNode_free(TreeNode node) {
    HashTable_CN_free(node->children);
    free(node);
}


Tree Tree_create(int nodeSize) {
//    printf("Create Tree\n");
    Tree tree = malloc(sizeof(Tree *));
    tree->nodeSize = nodeSize;
    tree->root = TreeNode_create(nodeSize);
//    printf("Tree Created\n\n");
    return tree;
}

void Tree_addWord(Tree tree, char * word) {
//    printf("Add Word %s\n", word);
    TreeNode currentNode = tree->root;
    for (int i=0; word[i] != '\0'; i++) {
        if (HashTable_CN_exist(currentNode->children, word[i]) == 1) {
//            printf("  %c exist\n", word[i]);
            currentNode = HashTable_CN_find(currentNode->children, word[i]);
        } else {
//            printf("  Add letter %c\n", word[i]);
            TreeNode child = TreeNode_create(tree->nodeSize);
            HashTable_CN_add(currentNode->children, word[i], child);
            currentNode = child;
//            printf("  Letter Added\n");
        }
    }
    currentNode->isWord = 1;
//    printf("Word Added\n\n");
}

int Tree_isWord(Tree tree, char * word) {
    TreeNode currentNode = tree->root;
    for (int i=0; word[i] != '\0'; i++) {
//        printf("Search for %c\n", word[i]);
        if (HashTable_CN_isEmpty(currentNode->children) == 1) {
//            printf("error 1\n");
            return 0;
        }
        currentNode = HashTable_CN_find(currentNode->children, word[i]);
        if (!currentNode) {
//            printf("error 2\n");
            return 0;
        }
    }
//    printf("word end\n");
    return currentNode->isWord;
}