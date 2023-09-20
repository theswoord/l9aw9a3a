#include "minishell.h"

void linkwithex(char **tableau){

    struct s_tree* root = NULL;
    int len = twodlen(tableau);
    int i = 1;
    int k = 0;
    // if (!ft_strchr())
    // {
    //     /* code */
    // }
    // if (!ft_strchr(tableau[0],))
    // {
    //     /* code */
    // }
    // char* rootData = "WORD";
        while (tableau[k])
    {
        printf("[%d] fragments: %s\n",k ,tableau[k]);
        k++;
    }
    // insertNode(&root, "CMD");
    // insertNode(&(root->left), tableau[0]);

    // while (i < len)
    // {
    // insertNode(&(root->right), tableau[i]);
    // i++;
    // }
    
    // printBinaryTree(root, 0, '-');
    // printf("root %s left node %s right node %s tanya %s \n",root->data,root->left->data ,root->right->data,root->right->right->data );
    // insert code here

    // freeTree(root);
    
}
// int start_builtins(char *str, t_shell *g_struct , char **env){

//     if(ft_strcmp(str,"echo"))
    
// }