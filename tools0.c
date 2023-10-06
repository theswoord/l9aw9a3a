#include "minishell.h"


void print_pointers2(t_redi_node* head){
	t_redi_node* current;
	current = head;
	while (current != NULL)
	{
		printf ("ptr |%p| strptr |%p| \n",current,current->file);
		current = current->next;
		/* code */
	}
	
}
void print_pointers(t_tlist *head){
	t_tlist *current;
	current = head;
	while (current != NULL)
	{
		printf ("ptr |%p| str |%s| strptr |%p| \n",current,current->str,current->str);
		current = current->next;
		/* code */
	}
	
}
void special_free(t_shell *g_struct) {
	t_tlist *current;
	current = g_struct->tlist;
	while (current != NULL) {
    if (current->str) {
        free(current->str);
    }
    
    if (current->next) {
        free(current->next->str);
        free(current->next);
    }
    
    free(current);
    current = NULL; // Set to NULL to indicate that the memory has been freed
}
}
int list_size(t_tlist *head)
{

	t_tlist *current = head;
	int size = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
		/* code */
	}
	return size;
}

char **from_list_to_arr(t_tlist *head)
{

	int i = 0;
	int size;
	size = list_size(head);
	char **arr;
	t_tlist *current = head;
	arr = malloc(size * sizeof(char *) + 1);
	while (current != NULL)
	{
		// arr[i]=malloc()
		// /* code */
		// i++;
		arr[i] = current->str;
		// free(current->str);
		// printf("*%s*\n",arr[i]);
		i++;
		current = current->next;
		// printf("%p\n",arr);
	}
	
	arr[i] = NULL;

	return arr;
}