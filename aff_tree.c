#include "minishell.h"

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void printBinaryTree(struct s_tree* root, int level, char direction) {
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
void printInOrderIndented(struct s_tree* node, int depth) {
    if (node == NULL) {
        return;
    }

    const int INDENTATION_SPACES = 4;
    int indentation = depth * INDENTATION_SPACES;

    printInOrderIndented(node->left, depth + 1);

    printf("%*s%s\n", indentation, "", node->data);

    printInOrderIndented(node->right, depth + 1);
}

void printTree(struct s_tree* root) {
    printf("Binary Tree:\n");
    printInOrderIndented(root, 0);
}
