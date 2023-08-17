#include "minishell.h"

void free_tableau(char **tableau, int lines)
{

    int i;
    i = 0;
    while (i < lines)
    {
        free(tableau[i]);
        i++;
    }
    free(tableau);
}