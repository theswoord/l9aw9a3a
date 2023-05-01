#include "minishell.h"

void tokenisation(char *str){
int quotes = 0;
int d_quotes = 0;
int pipes = 0;

    // printf("%s\n", where);

pipes = e_search(str,'|');
quotes = e_search(str,'\'');
d_quotes = e_search(str,'"');

if (quotes %2 != 0 || d_quotes %2 != 0){
printf("syntax error !\n");
return;
}
        printf("*%s*\n", str);

}