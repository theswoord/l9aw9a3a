#include "minishell.h"

// t_tre *node (char* data){

//     t_tre *node = (t_tre *)malloc(sizeof(t_tre));
//     node->token = data;
//     node->left = NULL;
//     node->right =NULL;
//     return(node);


// }

// t_tre *inserttree(char *data){
    
// }


// void insertNode(struct s_tree** root, char* data) {
//     struct s_tree* newNode = (struct s_tree*)malloc(sizeof(struct s_tree));
//     newNode->data = data;
//     newNode->left = NULL;
//     newNode->right = NULL;

//     if (*root == NULL) {
//         *root = newNode;
//         return;
//     }

//     struct s_tree* current = *root;
//     while (1) {
//         if (ft_strncmp(data, current->data,ft_strlen(data)) < 0) {
//             if (current->left == NULL) {
//                 current->left = newNode;
//                 break;
//             } else {
//                 current = current->left;
//             }
//         } else {
//             if (current->right == NULL) {
//                 current->right = newNode;
//                 break;
//             } else {
//                 current = current->right;
//             }
//         }
//     }
// }
void freeTree(struct s_tree* node) {
    if (node == NULL) {
        return;
    }

    freeTree(node->left);
    freeTree(node->right);
    free(node);
}
// int main() {
//     char input[] = "a b c d e f g h";
    // struct s_tree* root = NULL;
    // char* rootData = "WORD";
    // insertNode(&root, rootData);

//     char **words = ft_split(input, ' ');
//         insertNode(&(root->left), words[0]);

//     for (int i = 0; i < 6; i++) {
//         insertNode(&(root->right), words[i]);
//     }

    // printBinaryTree(root, 0, '-');

//     freeTree(root);
//     return 0;
// }