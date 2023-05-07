#include "minishell.h"

void tokenisation(char *str)
{

    static t_counter *elements;
    if (!elements)
        elements = (t_counter *)malloc(sizeof(t_counter));
    element_init(elements, str);

    // printf("fdsfds\n");
    // int i = 0;
    char *tmp = ft_calloc(ft_strlen(str), 1);
    ft_strlcpy(tmp, str, ft_strlen(str) + 1);

    // if (syntax_check(elements, str) == 0)
    //     return;

    // if(closed_quotes(tmp) == 3){

    // }
    // if( elements->d_quotes != 0)
    // tmp = quotefixer(tmp,'"');
    // if(elements->quotes != 0 )
    // tmp = quotefixer(tmp,'\'');
    if (elements->quotes != 0 || elements->d_quotes != 0)
    {
        printf("kayn \" %d \n", closed_double_quotes(tmp));
        printf("kayn \'  .%d \n", closed_quotes(tmp));
        // printf("%d\n",closed_quotes(tmp));
        // if(closed_quotes(tmp)==3)
        // printf("%s\n",code_3_quotes(tmp));
        // ------------------------------------------------------------------------ mzyan 9bl rework e"cho" hhf'ds'fsd"qsdf"c"w'x"
        if (closed_quotes(tmp) == 3 || closed_quotes(tmp) == 1)
        {
            if (closed_quotes(tmp) == 1)
            {
                simple_trim(tmp, '\'');
            }
            else
                special_trim(tmp, '\'');
        }

        if (closed_double_quotes(tmp) == 3 || closed_double_quotes(tmp) == 1) // matnsach expand
        {
            if (closed_double_quotes(tmp) == 1)
                simple_trim(tmp, '"');
            else
                special_trim(tmp, '"');
        }
        // if (closed_double_quotes(tmp) == 1)
        //     simple_trim(tmp, '"');
        // if (closed_quotes(tmp) == 1 || closed_double_quotes(tmp) == 1)
        // {
        //     tmp = simple_trim(tmp, '"');
        // }

        // if ((closed_double_quotes(tmp)==3) && elements->d_quotes != 0)
        // {
        //    tmp = special_trim(tmp,'"');
        //     printf("%s\n",tmp);
        // }
        // if ((closed_quotes(tmp)==3 ) && elements->quotes != 0)
        // {
        //    tmp = special_trim(tmp,'\'');
        //     printf("%s\n",tmp);
        // }
        // ------------------------------------------------------------------------
        // else if ((closed_quotes(tmp)==1 ) && elements->quotes != 0)
        // {
        //    tmp = special_trim(tmp,'\'');
        //     printf("%s\n",tmp);
        // }
    }
    printf("%s\n", tmp);
    free(tmp);
    // free(str);
}
char *quotefixer(char *str, char quote)
{

    int i = 0;
    char *found = ft_calloc(1, 1);
    char **fragments;

    fragments = ft_split(str, quote);
    while (fragments[i])
    {
        found = ft_strjoingnl(found, fragments[i]);
        i++;
    }
    free_tableau(fragments, i);
    return (found);
}
void element_init(t_counter *elements, char *str)
{

    elements->pipes = e_search(str, '|');
    elements->quotes = e_search(str, '\'');
    elements->d_quotes = e_search(str, '"');
    elements->r_right = e_search(str, '>');
    elements->r_left = e_search(str, '<');
}
int syntax_check(t_counter *elements, char *str)
{
    int i;
    i = 0;
    if (closed_quotes(str) == 0 || closed_double_quotes(str) == 0)
    {
        printf("syntax error !\n");
        return (0);
        // if (){
        // printf("syntax error !\n");
        // return(0);
        // }
        // if(elements->pipes != 0){

        // }
    }

    return 1;
}
// single ' wst "" makaytlghach li lwst o l3ks
//  wst '' no expand
// ila kant " '$s' " expand
//   " $s " expand
//   '' = "" if no $
//  '$s' no expand

// while (tmp[i])
// {
//     tmp[i]= ft_tolower(tmp[i]);
//     i++;
// }

int closed_quotes(char *str)
{

    // -------------------------------- working without chat gpt
    // int i = 0;
    // int o = 0;
    // int s =0;
    // int c = 0;
    // int start = 0;
    // int finish = 0;
    // while (str[i]!= '\0')
    // {

    // if (str[i] == '\'' && o == 0){
    //  o=1;
    //  start = i;
    //  i++;
    // }
    // if (str[i] == '"' ||str[i] == '$')
    // s++;

    // if(str[i] == '\'' && o == 1){
    // c = 1;
    // finish = i;
    // i++;
    // }

    // if(c == 1 && pos(str+finish,'\'') > finish){
    // o = 0;
    // c = 0;
    // }
    // i++;
    // }

    // if(o == 1 && c == 0)
    // return 0;
    // if (s != 0)
    // return 3;

    // return 1;
    // --------------------------------------- working with chat gpt
    int i = 0;
    int inside = 0;
    int squotes_o = 0;
    int squotes_c = 0;
    int found = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '\'')
        {
            if (inside)
                squotes_c++;
            else
                squotes_o++;

            inside = !inside;
        }
        else if ((str[i] == '"' || str[i] == '$') && inside)
            found = 1;
        i++;
    }

    if (inside)
        return 0;
    else if (found)
        return 3;
    else
        return 1;
    //--------------------------------------------------------
}
char *code_3_quotes(char *str)
{

    char *result;
    result = ft_strtrim(str, "\'");
    return result;
}
int closed_double_quotes(char *str)
{

    // -------------------------------- working without chat gpt // dkhel expand
    // int i = 0;
    // int o = 0;
    // int s =0;
    // int c = 0;
    // int start = 0;
    // int finish = 0;
    // while (str[i]!= '\0')
    // {

    // if (str[i] == '"' && o == 0){
    //  o=1;
    //  start = i;
    //  i++;
    // }
    // if (str[i] == '$'|| str[i] == '\'')
    // s++;

    // if(str[i] == '"' && o == 1){
    // c = 1;
    // finish = i;
    // i++;
    // }

    // if(c == 1 && pos(str+finish,'"') > finish){
    // o = 0;
    // c = 0;
    // }
    // i++;
    // }

    // if(o == 1 && c == 0)
    // return 0;
    // if (s != 0)
    // return 3;

    // return 1;
    // --------------------------------------- working with chat gpt
    int i = 0;
    int inside = 0;
    int squotes_o = 0;
    int squotes_c = 0;
    int found = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '\'')
        {
            if (inside)
                squotes_c++;
            else
                squotes_o++;

            inside = !inside;
        }
        else if ((str[i] == '"' || str[i] == '$') && inside)
            found = 1;
        i++;
    }

    if (inside)
        return 0;
    else if (found)
        return 3;
    else
        return 1;
    //--------------------------------------------------------
}
char *special_trim(char *str, char c)
{
    int i = 0;
    int foundfront = 0;
    int foundback = 0;
    int j = ft_strlen(str) - 2;
    int idxToDel = 0;
    while (str[i] != '\0')
    {
        if (foundfront == 0 && str[i] == c)
        {
            idxToDel = i;
            i++;
            foundfront++;
        }
        i++;
    }
    ft_memmove(&str[idxToDel], &str[idxToDel + 1], ft_strlen(str) - idxToDel);
    // j-=1;
    // printf("%c <-ach kayn hna",str[j]);
    while (str[j] != '\0')
    {
        if (foundback == 0 && str[j] == c)
        {
            // printf("|%c| %d",str[j],j);
            idxToDel = j;
            j--;
            foundback++;
        }
        j--;
    }
    // printf("idx%d\n",idxToDel);
    ft_memmove(&str[idxToDel], &str[idxToDel + 1], ft_strlen(str) - idxToDel);
    return str;
}
char *simple_trim(char *str, char c)
{

    int i = 0;
    int idxToDel = 0;
    // char* toreturn;
    while (str[i] != '\0')
    {

        if (str[i] == c)
        {
            idxToDel = i;
            ft_memmove(&str[idxToDel], &str[idxToDel + 1], ft_strlen(str) - idxToDel);
            // printf("%s\n",str);
            // i++;
        }
        i++;
    }
    return (str);
}