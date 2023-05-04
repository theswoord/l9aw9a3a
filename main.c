#include "minishell.h"
int main(int ac, char **av, char **env)
{
    int i = 0;
    char *test;
    (void)ac;
    (void)av;
    
    // printf("%s\n",env[3]);
    while (1)
    {
        test = readline("{9aw9a3a hh}: \% ");
        // test = get_next_line(0);
        // readline("gggg");

        if (!test)
        {
            free(test);
            return 1;
        }
       if (ft_strlen(test) > 0)
        add_history(test);
       
       tokenisation(test);
       free(test);
    }
}

// void handler(char *string)