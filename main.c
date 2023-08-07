#include "minishell.h"
    t_shell g_struct;
void sig(int signal){

    // if (signal == SIGINT){

    // }

    // printf("sig :%d\n",signal);
    // signal(SIGQUIT,sig);
    if (signal == SIGINT){
        // printf("sig engaged %d ",signal);
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}
    // g_struct = (t_shell *)malloc(sizeof(t_shell));

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
    // t_env *myenv;
    g_struct.c = 15;
    // printf("hhhhhhhhhhhhhh%s\n",env[5]);
    // catch_env(env,myenv);
    // printf("11%s\n",myenv->next->envir);
    // print_env(myenv);
    // catch_environ(&myenv,env);
    // print_environ();
    // printf("fsdfsd\n");
    initialize_environment(&g_struct.envlist,env);
    // printf("%s hh",g_struct.envlist->next->next->value);
    // print_env(g_struct.envlist,1);
 char *prompt;
 prompt = better_prompt();
    while (1)
    {
        test = readline(prompt);
        // free(prompt);
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

char *better_prompt(void){

    char* user;
    user =  env_nav(&g_struct.envlist,"USER");
    char* folder;
    char* tmp ;
    tmp = env_nav(&g_struct.envlist,"PWD");
    folder = ft_strdup(ft_strrchr(tmp,'/'));
    char* out;
    out = ft_strjoingnl(user,":");
    
    out = ft_strjoingnl(out,"~");
    out = ft_strjoingnl(out,folder);
    out = ft_strjoingnl(out,"$ ");
    free( tmp );
    // free( user);
    free(folder);
    return out;

}
// void handler(char *string)