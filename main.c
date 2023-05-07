#include "minishell.h"
void sig(int signal){

    // if (signal == SIGINT){

    // }

    // printf("sig :%d\n",signal);
    // signal(SIGQUIT,sig);
    if (signal == SIGINT){
        // printf("sig engaged %d ",signal);
        rl_on_new_line();
        rl_replace_line(" ", 0);
        rl_redisplay();
    }
}


int main(int ac, char **av, char **env)
{
    int i = 0;
    char *test;
    (void)ac;
    (void)av;
    
    struct sigaction minisignols;
    minisignols.sa_handler = sig;
    sigemptyset(&minisignols.sa_mask);
    sigaddset(&minisignols.sa_mask,SIGQUIT);
    minisignols.sa_flags =0 ;
    // sigprocmask(SIG_BLOCK, &sigblock, NULL);
    // sigaction(SIGINT,&minisignols,NULL);
    sigaction(SIGINT,&minisignols,NULL);
    sigaction(SIGQUIT,&minisignols,NULL);

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