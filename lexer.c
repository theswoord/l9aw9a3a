#include "minishell.h"

void tokenisation(char *str)
{
    int i = 0;
    char *sa =NULL;
    // static t_counter *elements;
    // if (!elements)
    //     elements = (t_counter *)malloc(sizeof(t_counter));
    // static t_prompt *helper;
    // if (!helper)
    //     helper = (t_prompt *)malloc(sizeof(t_prompt));

    // element_init(elements, str);

    sa = ft_strtok(&str);
    // t_list* list = l_addnode(sa);
    t_list* list = NULL;

    // sa = ft_strtok(&str);

    // add_list(&list,sa);



    // sa = ft_strtok(&str);

    while (sa)
    {
        // add_list(&list,sa);
        printf("|%s|\n", sa);
        sa = ft_strtok(&str);
        // free(sa);

    //     // printf("9lwa\n");
        // if(sa != NULL)
        // add_list(&list,sa);

        // free(sa);
        // l_addback(list,sa);
    //     // printf()
    //     // (*sa)++;

    //     // x++;
    }
    // printf("|%s|\n",list->str);
    // printf("|%s|\n",list->next->str);
    // printf("|%s|\n",list->next->next->str);
    // printf("%d\n",list_size(list));
    // l_print(list);
    // printf("|%s|\n",list->next->next->str);
   
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

int closed_quotes(char *str)
{

    // -------------------------------- working without chat gpt
    int i = 0;
    int o = 0;
    int s = 0;
    int c = 0;
    int start = 0;
    int finish = 0;
    while (str[i] != '\0')
    {

        if (str[i] == '\'' && o == 0)
        {
            o = 1;
            start = i;
            i++;
        }
        if (str[i] == '"' || str[i] == '$')
            s++;

        if (str[i] == '\'' && o == 1)
        {
            c = 1;
            finish = i;
            i++;
        }

        if (c == 1 && pos(str + finish, '\'') > finish)
        {
            o = 0;
            c = 0;
        }
        i++;
    }

    if (o == 0 && c == 0)
        return 5;
    if (o == 1 && c == 0)
        return 0;
    if (s != 0) // c == 0 oula 1
        return 3;

    return 1;
    // --------------------------------------- working with chat gpt
    // int i = 0;
    // int inside = 0;
    // int squotes_o = 0;
    // int squotes_c = 0;
    // int found = 0;

    // while (str[i] != '\0')
    // {
    //     if (str[i] == '\'')
    //     {
    //         if (inside)
    //             squotes_c++;
    //         else
    //             squotes_o++;

    //         inside = !inside;
    //     }
    //     else if ((str[i] == '"' || str[i] == '$') && inside)
    //         found = 1;
    //     i++;
    // }

    // if (inside)
    //     return 0;
    // else if (found)
    //     return 3;
    // else
    //     return 1;
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
    int i = 0;
    int o = 0;
    int s = 0;
    int c = 0;
    int start = 0;
    int finish = 0;
    while (str[i] != '\0')
    {

        if (str[i] == '"' && o == 0)
        {
            o = 1;
            start = i;
            i++;
        }
        if (str[i] == '$' || str[i] == '\'')
            s++;

        if (str[i] == '"' && o == 1)
        {
            c = 1;
            finish = i;
            i++;
        }

        if (c == 1 && pos(str + finish, '"') > finish)
        {
            o = 0;
            c = 0;
        }
        i++;
    }
    if (o == 0 && c == 0)
        return 5;
    if (o == 1 && c == 0)
        return 0;
    if (s != 0)
        return 3;

    return 1;
    // --------------------------------------- working with chat gpt
    // int i = 0;
    // int inside = 0;
    // int squotes_o = 0;
    // int squotes_c = 0;
    // int found = 0;

    // while (str[i] != '\0')
    // {
    //     if (str[i] == '\'')
    //     {
    //         if (inside)
    //             squotes_c++;
    //         else
    //             squotes_o++;

    //         inside = !inside;
    //     }
    //     else if ((str[i] == '"' || str[i] == '$') && inside)
    //         found = 1;
    //     i++;
    // }

    // if (inside)
    //     return 0;
    // else if (found)
    //     return 3;
    // else
    //     return 1;
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

// int isQuotesClosed(const char *str) {
//     int i = 0;
//     int openQuotes = 0;
//     int special = 0;
//     int which = 0;

//     while (str[i] != '\0') {
//         if (str[i] == '"' || str[i] == '\'') {
//             if (str[i] == '"')
//             which = '"';
//             // else if (str[i] == '\'')
//             // which = '\'';

//             openQuotes = !openQuotes; // Toggle the openQuotes flag
//         }
//         else if (str[i] == '$' || str[i] == '\'')
//             special++;
//         i++;
//     }
//     if (special)
//     {
//         /* code */ return (3);
//     }

//     return openQuotes == 0; // Return true if all opening quotes are closed

// }

void the_divider(t_prompt *helper, t_counter *elements, char *str)
{

    if (elements->pipes != 0)
    {
        helper->tempdevider = ft_split(str, '|');
    }
    // if (/* condition */)
    // {
    //     /* code */
    // }

    helper->tempdevider = ft_split(str, '\n');
    helper->twodlen = twodlen(helper->tempdevider);
    // free(str);
}
// void quoter(t_prompt *helper){
// int i = 0;
// while (helper->tempdevider[i])
// {

//     // printf("ster [%d] SQ =%d DQ=%d\n",i,closed_quotes(helper->tempdevider[i]), closed_double_quotes(helper->tempdevider[i]));
//     // printf("ster [%d] SQ =%d  DQ=%d\n",i,quotation(helper->tempdevider[i],'\''),quotation(helper->tempdevider[i],'\"'));

// // if (closed_quotes(helper->tempdevider[i])==0 || closed_double_quotes(helper->tempdevider[i])==0)
// // {
// //     printf("syntax error !\n");
// //     return;
// // }
// if (closed_quotes(helper->tempdevider[i])==1|| closed_double_quotes(helper->tempdevider[i])==1)
// {
//     if(closed_quotes(helper->tempdevider[i])==1)
//         simple_trim(helper->tempdevider[i],'\'');
//     else if (closed_double_quotes(helper->tempdevider[i])==1)
//         simple_trim(helper->tempdevider[i],'"');
// }
// // else if (closed_quotes(helper->tempdevider[i])==3|| closed_double_quotes(helper->tempdevider[i])==3)
// // {
//     if(quotation(helper->tempdevider[i],'\'')==5)
//         special_trim(helper->tempdevider[i],'\'');
//     else if (quotation(helper->tempdevider[i],'\"')==2)
//         special_trim(helper->tempdevider[i],'\"');
// // }
// i++;

// }
// }
int special_char(char c)
{

    if ((c == ' ' || c == '<' || c == '>' || c == '|' || c == '\"' || c == '\'' || c == '\0')) // ||c == '\"'||c == '\''
        return (1);
    return 0;
}
// int quotation(char *str,int c){

//     int i = 0;
// int open = 0 ;
// int li = 0;
// int s = 0;
//     while (str[i]!= '\0')
//     {
//         if ( open == 0 && str[i] == c)
//         {
//             open = 1;
//             li = c;

//         }
//             if (special_char(str[i],li)==1 )
//             s++;
//         else if (open == 1 && str[i] == li )
//         {

//             open = 0;
//         }
//         /* code */
//         i++;
//     }
//     if (open == 1)
//     return 0;
//     // else if (s != 0)
//     // return 3;
//     else if (li == '\'' && s > 0)
//     return 5;
//     else if (li == '\"' && s > 0)
//     return 2;

//     return 1;
// }

char *ft_strtok(char **str)
{

    int i = 0;
    int o = 0;
    int c = 0;
    int chkon = 0;
    char *s1 = *str;
    if (!*s1)
    {
        // printf(".%s.\n",s1);
        // printf("salit\n");
        return NULL;
        /* code */
    }
    while (s1[i])
    {
        if (special_char(s1[i]) == 1 && (s1[i] == '\"' || s1[i] == '\'') && i == 0 && o == 0)
        {
            o = 1;
            chkon = s1[i];
            i++;
            while (s1[i] != chkon)
                i++;
            o = 0;
            i++;
            s1 = ft_substrgnl(*str, 0, i);
            // free(s1);
            *str += i;
        }
        else if (special_char(s1[i]) == 1)
        {
            // printf("1st b=%p c=%s \n",s1,s1);
            // free(s1);
            s1 = ft_substrgnl(*str, 0, i);
            // printf("1st a=%p c=%s \n",s1,s1);
            *str += i;
        }
        if (special_char(s1[i]) == 1 && i == 0)
        {
            i++;
            // printf("2nd b=%p c=%s \n",s1,s1);
            s1 = ft_substrgnl(*str, 0, i);
            // free(s1);
            // printf("2nd a=%p c=%s \n",s1,s1);
            *str += i;
        }

        i++;
    }
    if (s1[i] == '\0' && special_char(s1[i - 1]) != 1)
    {
        // printf("final b=%p c=%s \n",s1,s1);
        s1 = ft_substrgnl(*str, 0, i);
        // printf("final a=%p c=%s \n",s1,s1);
        // free(s1);
        *str += i;
    }
    free(s1);
    return s1;
}
t_list *l_addnode(char *data)
{

    t_list *current = (t_list *)malloc(sizeof(t_list));

    // current->str=data;
    // ft_strlcpy(current->str,data,ft_strlen(data));
    current->str = ft_strdup(data);
    free(data);
    // current->str = ft_strjoingnl(current->str,data);
    
    // ft_strlcpy(current->str,data,ft_strlen(data));

    current->next = NULL;
    // printf("%s\n",current->str);
    return (current);
}
int list_size(t_list *head)
{

    int i = 0;
    t_list *current;
    current = head;
    while (current != 0)
    {
        i++;
        current = current->next;
        /* code */
    }
    return i;
}
void l_addback(t_list*list,char *data){

    t_list *search ; 
    t_list *tmp = malloc(sizeof(t_list));
    search = list;
    // printf("data B = %p\n",data);
    tmp->str = ft_strdup(data);
    free(data);
    // printf("data A = %p\n",tmp->str);

    // ft_strlcpy(tmp->str,data,ft_strlen(data));
    // tmp->str = ft_strjoingnl(tmp->str,data);

    tmp->next = NULL;
    while (search->next != NULL)
    {
        search=search->next;
        /* code */
    }
    search->next=tmp;
    // t_list* current =(t_list*)

}
void l_print(t_list *list){


     t_list *search ;
    search = list;
    while(search != 0){
        printf("|%s|\n",search->str);
        search = search->next;
    }
    
}
void add_list(t_list **head,char *s){


    t_list *new_node;
    t_list *last;
    if(ft_strlen(s) == 0){
        free (s);
        return;
    }
    last = *head;
    new_node =create_node(s);
    if (*head==NULL)
    {
        *head = new_node;
    
        /* code */
    }
    else
    {
        while (last->next)
        {
            last=last->next;
            /* code */
        }
        last->next = new_node;
        
    }
    
}
t_list *create_node(char* s){

    t_list *new_node;
    new_node = malloc(sizeof(t_list));
    new_node->str = ft_strdup(s);
    // free(s);
    new_node->next=NULL;
    return(new_node);
}
char	*ft_substrmini(char *s, unsigned int start, size_t len)
{
	size_t			b;
	char			*subs;
	unsigned int	test;

	if (!s)
	{
		return (0);
	}
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	b = 0;
	test = ft_strlen(s);
	subs = malloc(len * sizeof(char) + 1);
	if (!subs)
		return (0);
	while (b < len && test >= start)
	{
		subs[b] = s[start];
		b++;
		start++;
	}
	subs[b] = '\0';
    free(s);
	return (subs);
}
