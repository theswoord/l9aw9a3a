
struct Node {
    char* data;
    struct Node* left;
    struct Node* right;
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printInOrderIndented(struct Node* node, int depth) {
    if (node == NULL) {
        return;
    }

    // Increase the indentation for each level of the tree
    const int INDENTATION_SPACES = 4;
    int indentation = depth * INDENTATION_SPACES;

    // Print the left subtree
    printInOrderIndented(node->left, depth + 1);

    // Print the current node
    printf("%*s%s\n", indentation, "", node->data);

    // Print the right subtree
    printInOrderIndented(node->right, depth + 1);
}

void printTree(struct Node* root) {
    printf("Binary Tree:\n");
    printInOrderIndented(root, 0);
}

char** splitString(char* input, int* count) {
    // Count the number of words
    int wordCount = 1;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ' ') {
            wordCount++;
        }
    }

    // Allocate memory for the array of strings
    char** words = (char**)malloc(wordCount * sizeof(char*));
    if (words == NULL) {
        *count = 0;
        return NULL;
    }

    // Split the input string into words
    char* token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        words[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    *count = wordCount;
    return words;
}
void insertNode(struct Node** root, char* data) {
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    // If the tree is empty, make the new node the root
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    // Traverse the tree to find the appropriate position to insert the node
    struct Node* current = *root;
    while (1) {
        // If the data is less than the current node's data, go to the left subtree
        if (strcmp(data, current->data) < 0) {
            if (current->left == NULL) {
                current->left = newNode;
                break;
            } else {
                current = current->left;
            }
        }
        // If the data is greater than or equal to the current node's data, go to the right subtree
        else {
            if (current->right == NULL) {
                current->right = newNode;
                break;
            } else {
                current = current->right;
            }
        }
    }
}
void printInOrder(struct Node* node) {
    if (node == NULL) {
        return;
    }

    printInOrder(node->left);
    printf("%s ", node->data);
    printInOrder(node->right);
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
    char input[] = "ls -la echo hhhh";
    int i =0;
    int j = 0;
    int count;
    char** words = splitString(input, &count);
    printf("1 = %s , %s = 2\n", words[0],words[1]);
    struct Node* root = NULL;
    char* rootData = "WORD";
    insertNode(&root, rootData);

    // Create the left node with "echo"
    char* leftData = words[0];
    insertNode(&(root->left), leftData);

    // Create the right node with "'hello'"
    char* rightData =words[1];
    insertNode(&(root->right), rightData);

    // while (words[j][i])
    // {
    //     while (j)
    //     {
    //         /* code */
    //     }
        
    // }
    
    // for (int i = 0; i < count; i++) {
    //     insertNode(&root, words[i]);
    // }

    // Print the binary tree (in-order traversal)
    // printf("Binary Tree (In-order traversal):\n");
        printTree(root);
    // printInOrder(root);printf("\n");

    // Free allocated memory
    freeTree(root);
    free(words);
        return 0;
}