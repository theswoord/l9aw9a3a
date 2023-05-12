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
int twodlen(char **tableau){
    int i =0;

    while (tableau[i])
    i++;


    return i;
}
void str_replacement(char *str){

    int i =0;
    int o =0; 
    int c =1;
    while (str[i] != '\0')
    {

        if((str[i] == '"' || str[i] == '\'')&& c == 1 )
        {
            o = 1;
            c= 0 ;
            i++;
        }
        if((str[i] == '"' || str[i] == '\'')&& o == 1)
        {
            c = 1;
            o=0;
            i++;
        }
        if(o == 1 && c==1)
        {
            o=0;
            c=0;
        }
            if (str[i] == ' ' && o==0)
               str[i] = '\n';
    i++;
    }
    
}
// void strr_replacement(char *str){

//     int i =ft_strlen(str)-1;
//      int o =0; 
//     while (str[i] != '\0')
//     {
//         // printf("|%c|\n",str[i]);
//         if (str[i] == ' ' && o==0)
//                str[i] = '\n';
//         if(str[i] == '"' || str[i] == '\'')
//         {
//             o = 1;
//         }
//     i--;
//     }
    
// }