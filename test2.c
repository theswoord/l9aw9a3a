#include <stdio.h>

int isQuotesClosed(const char *str) {
    int i = 0;
    int openQuotes = 0;
    int special = 0;
    int which = 0;

    while (str[i] != '\0') {
        if (str[i] == '"' || str[i] == '\'') {
            if (str[i] == '"')
            which = '"';
            else if (str[i] == '\'')
            which = '\'';

            
            openQuotes = !openQuotes; // Toggle the openQuotes flag
        }
        else if (str[i] == '$' || str[i] == '\'')
            special++;
        i++;
    }
    if (special)
    {
        /* code */ return (3);
    }
    
    return openQuotes == 0; // Return true if all opening quotes are closed
}

int main() {
    const char *string1 = "This is a \"valid\" st\"ring.";
    const char *string2 = "This is an \"invalid string.";
    
    if (isQuotesClosed(string1)) {
        printf("The quotes in string1 are properly closed.\n");
    } else {
        printf("The quotes in string1 are not properly closed.\n");
    }

    if (isQuotesClosed(string2)) {
        printf("The quotes in string2 are properly closed.\n");
    } else {
        printf("The quotes in string2 are not properly closed.\n");
    }

    return 0;
}
