#include "minishell.h"

int e_search(char* str, char c){


    int i;
    int count;
    i =0;
    count = 0;

    while(str[i]!= '\0'){

        if (str[i]== c)
            count++;
        
        i++;
    }
    return count;
}