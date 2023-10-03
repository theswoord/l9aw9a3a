#include "minishell.h"

    // return a static variable and change it's adress
    
    // t_shell g_struct;
void sig(int signal){

    // if (signal == SIGINT){

    // }

    // printf("sig :%d\n",signal);
    // signal(SIGQUIT,sig);
    if (signal == SIGINT){
        // printf("sig engaged %d ",signal);
        printf("\n");
        rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();
    }
}
    // g_struct = (t_shell *)malloc(sizeof(t_shell));

int main(int ac, char **av, char **env)
{
    t_shell g_struct;

    int i = 0;
    char *test;
    (void)ac;
    (void)av;
    struct sigaction minisignols;
    minisignols.sa_handler = sig;
    sigemptyset(&minisignols.sa_mask);
    sigaddset(&minisignols.sa_mask,SIGQUIT);
    minisignols.sa_flags = 0;
    // sigprocmask(SIG_BLOCK, &sigblock, NULL);
    // sigaction(SIGINT,&minisignols,NULL);
    sigaction(SIGINT,&minisignols,NULL);
    sigaction(SIGQUIT,&minisignols,NULL);
    // t_env *myenv;
    // g_struct.c = 15;
    // printf("hhhhhhhhhhhhhh%s\n",env[5]);
    // catch_env(env,myenv);
    // printf("11%s\n",myenv->next->envir);
    // print_env(myenv);
    // catch_environ(&myenv,env);
    // print_environ();
    // printf("fsdfsd\n");
    // printf("%d\n",g_struct.count);
    // g_struct.count=0;
    initialize_environment(&g_struct,&g_struct.envlist,env);
    // while (1)
    // {
    //     /* code */
    // }
    
    // printf("%d\n",g_struct.count);
    // print_env(g_struct.envlist,0);
    // while (1)
    // {
    //     /* code */
    // }
    
    // printf("%s hh",g_struct.envlist->next->next->value);
    // print_env(g_struct.envlist,1);
//  char *prompt;
//  prompt = better_prompt();
    // while (1)
    // {
    //     test = readline("minishell -> : ");
    //     // free(prompt);
    //     // test = get_next_line(0);
    //     // readline("gggg");


        if (!test)
        {
            free(test);
            free_env(g_struct.envlist);
            return g_struct.exit_status;
        }
       if (ft_strlen(test) > 0)
        add_history(test);
       
    //    tokenisation(test,&g_struct,env);
    //    free(test);
    // }
    g_struct.heredoc_list = NULL;
    heredoc(&g_struct, "eof");
    heredoc(&g_struct, "end");
    heredoc(&g_struct, "fin");
    while (g_struct.heredoc_list != NULL)
    {
        printf("%i\n", g_struct.heredoc_list->fd);
        g_struct.heredoc_list = g_struct.heredoc_list->next;
    }
}

// char *better_prompt(void){

//     char* user;
//     user =  env_nav(&g_struct.envlist,"USER");
//     char* folder;
//     char* tmp ;
//     tmp = env_nav(&g_struct.envlist,"PWD");
//     folder = ft_strdup(ft_strrchr(tmp,'/'));
//     char* out;
//     out = ft_strjoingnl(user,":");
    
//     out = ft_strjoingnl(out,"~");
//     out = ft_strjoingnl(out,folder);
//     out = ft_strjoingnl(out,"$ ");
//     free( tmp );
//     // free( user);
//     free(folder);
//     return out;

// }
// void handler(char *string)