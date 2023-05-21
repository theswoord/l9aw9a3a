#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* data;
    struct Node* left;
    struct Node* right;
};

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void printBinaryTree(struct Node* root, int level, char direction) {
    if (root == NULL) {
        return;
    }

    int indentation = level * 4;

    printBinaryTree(root->right, level + 1, 'r');

    printSpaces(indentation);

    if (direction == 'r') {
        printf(" /");
    } else if (direction == 'l') {
        printf(" \\");
    }

    printf("-- %s\n", root->data);

    printBinaryTree(root->left, level + 1, 'l');
}

void printInOrderIndented(struct Node* node, int depth) {
    if (node == NULL) {
        return;
    }

    const int INDENTATION_SPACES = 4;
    int indentation = depth * INDENTATION_SPACES;

    printInOrderIndented(node->left, depth + 1);

    printf("%*s%s\n", indentation, "", node->data);

    printInOrderIndented(node->right, depth + 1);
}

void printTree(struct Node* root) {
    printf("Binary Tree:\n");
    printInOrderIndented(root, 0);
}

void insertNode(struct Node** root, char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (*root == NULL) {
        *root = newNode;
        return;
    }

    struct Node* current = *root;
    while (1) {
        if (strcmp(data, current->data) < 0) {
            if (current->left == NULL) {
                current->left = newNode;
                break;
            } else {
                current = current->left;
            }
        } else {
            if (current->right == NULL) {
                current->right = newNode;
                break;
            } else {
                current = current->right;
            }
        }
    }
}

void freeTree(struct Node* node) {
    if (node == NULL) {
        return;
    }

    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    char input[] = "a b c d e f g h";
    struct Node* root = NULL;
    char* rootData = "WORD";
    insertNode(&root, rootData);

    char **words = ft_split(input, ' ');
        insertNode(&(root->left), words[0]);

    for (int i = 0; i < 6; i++) {
        insertNode(&(root->right), words[i]);
    }

    printBinaryTree(root, 0, '-');

    freeTree(root);
    return 0;
}