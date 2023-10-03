#include "minishell.h"

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}
void* my_realloc(void* ptr, size_t size) {
    if (ptr == NULL) {
        // If the pointer is NULL, it's equivalent to calling malloc(size)
        return malloc(size);
    } else if (size == 0) {
        // If the size is 0, it's equivalent to calling free(ptr)
        free(ptr);
        return NULL;
    } else {
        // Allocate a new block of memory with the given size
        void* new_ptr = malloc(size);
        if (new_ptr) {
            // Copy the contents from the old block to the new block
            size_t old_size = malloc_usable_size(ptr);
            memcpy(new_ptr, ptr, old_size);
            // Free the old block of memory
            free(ptr);
        }
        return new_ptr;
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
