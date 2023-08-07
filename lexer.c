#include "minishell.h"


void tokenisation(char * str)
{

    char **done = ft_strsplit(str); // pit eveyone in a node

    int i = 0;

    while (done[i])
    {
        printf("|%s|\n",done[i]);
        i++;
        /* code */
    }
    

}
static int	skip_sep(char *s)
{
	int		i;
	int		opmax;
	int		counter;
	char	quotation_type;

	i = 0;
	quotation_type = s[i];
	opmax = 2;
	counter = 0;
	// if (s[i] == '(' || s[i] == ')')
	// 	opmax = 1;
	while (s[i] == quotation_type && s[i] != '\0' && counter++ < opmax)
		i++;
	return (i);
}

static int	ft_word_len(char *s)
{
	char	quotation_type;
	int		i;

	i = 0;
	if (s[i] == '>' || s[i] == '<'
		|| s[i] == '|')
		i += skip_sep(s);
	else
	{
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0'
			&& s[i] != '>' && s[i] != '<'
			&& s[i] != '|' )
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				quotation_type = s[i++];
				while (s[i] != quotation_type && s[i] != '\0')
					i++;
			}
			i++;
		}
	}
	return (i);
}

// ft_count - counts how many words are in the string given
// DESCRIPTION : 
//// the function starts by loopping through a string
//// then skips any tab or space using a loop
//// checks if the string doesnt only contain spaces 
static int	ft_count(char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] != '\0')
			count++;
		i += ft_word_len(&s[i]);
	}
	return (count);
}

// ft_strsplit - splits a string based on spaces and tabs or special chars 
// special chars >, <, &, |, ",'
char	**ft_strsplit(char *s)
{
	char	**splitted ;
	int		splitted_iterator;
	int		i;
	int		word_len;

	splitted = (char **) ft_calloc((ft_count(s) + 1), sizeof(char *));
	i = 0;
	splitted_iterator = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		word_len = ft_word_len(&s[i]);
		splitted[splitted_iterator] = (char *) malloc(word_len + 1);
		ft_strlcpy(splitted[splitted_iterator++], &s[i], word_len + 1);
		i += word_len;
	}
	return (splitted);
}