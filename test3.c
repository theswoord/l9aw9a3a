#include <stdio.h>
#include <string.h>

void removeFirstAndLast(char *str) {
    size_t len = strlen(str);

    // Check if the string has at least two characters
    if (len >= 2) {
        // Remove the first character
        memmove(str, str + 1, len - 1);
        
        // Null-terminate the string to adjust its length
        str[len - 1] = '\0';
    } else {
        // Handle cases where the string has less than two characters
        // (e.g., empty string or a single character string)
        str[0] = '\0'; // Make it an empty string
    }
}

int main() {
    char myString[] = "\'nabil\'";
    
    printf("Original String: %s\n", myString);
    
    removeFirstAndLast(myString);
    
    printf("Modified String: %s\n", myString);
    
    return 0;
}