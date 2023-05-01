#include "minishell.h"
int main(void)
{
    int i = 0;
    char *test;
    while (1)
    {
        test = readline("{9aw9a3a hh}: \% ");
        // readline("gggg");

        if (!test)
        {
            free(test);
            return 1;
        }
       if (ft_strlen(test) > 0)
        add_history(test);
       
       tokenisation(test);
    }
}

// void handler(char *string)