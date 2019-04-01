#include "tree.h"
#include <malloc.h>

TreeNode TreeNode_create(int nodeSize) {
    TreeNode treeNode = malloc(sizeof(TreeNode *));
    treeNode->isWord = 0;
    treeNode->children = HashTable_CN_create(nodeSize);
    return treeNode;
}

void TreeNode_free(TreeNode node) {
    HashTable_CN_free(node->children);
    free(node);
}


Tree Tree_create(int nodeSize) {
    Tree tree = malloc(sizeof(Tree *));
    tree->nodeSize = nodeSize;
    tree->root = TreeNode_create(nodeSize);
    return tree;
}

void Tree_addWord(Tree tree, char * word) {
    TreeNode currentNode = tree->root;
    for (int i=0; word[i] != '\0'; i++) {
        if (HashTable_CN_exist(currentNode->children, word[i]) == 1) {
            currentNode = HashTable_CN_find(currentNode->children, word[i]);
        } else {
            TreeNode child = TreeNode_create(tree->nodeSize);
            HashTable_CN_add(currentNode->children, word[i], child);
            currentNode = child;
        }
    }
    currentNode->isWord = 1;
}

int Tree_isWord(Tree tree, char * word) {
    TreeNode currentNode = tree->root;
    for (int i=0; word[i] != '\0'; i++) {
        if (HashTable_CN_isEmpty(currentNode->children) == 1) {
            return 0;
        }
        currentNode = HashTable_CN_find(currentNode->children, word[i]);
        if (!currentNode) {
            return 0;
        }
    }
    return currentNode->isWord;
}

void Tree_free(Tree tree) {
    TreeNode_free(tree->root);
    free(tree);
}