#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* customStrndup(const char* input, size_t length) {
    char* result = malloc(length + 1); // +1 for the null terminator
    if (result != NULL) {
        strncpy(result, input, length);
        result[length] = '\0'; // Null-terminate the string
    }
    return result;
}

char* expandVariablesRecursive(const char *input, const char *variables[], const char *values[], size_t numVariables) {
    size_t i, j;
    char *result = strdup(input);

    for (i = 0; i < numVariables; ++i) {
        char *variablePos = strstr(result, variables[i]);
        if (variablePos != NULL) {
            size_t prefixLen = variablePos - result;
            char *prefix = customStrndup(result, prefixLen);
            size_t suffixLen = strlen(variablePos + strlen(variables[i]));
            char *suffix = customStrndup(variablePos + strlen(variables[i]), suffixLen);
            free(result);
            result = malloc(strlen(prefix) + strlen(values[i]) + suffixLen + 1);
            strcpy(result, prefix);
            strcat(result, values[i]);
            strcat(result, suffix);
            free(prefix);
            free(suffix);
        }
    }

    return result;
}

int main() {
    char input[] = "hello $USER $PATH hey";
    const char *variables[] = {"$USER", "$PATH"}; // Add more variables if needed
    const char *values[] = {getenv("USER"), getenv("PATH")}; // Get values dynamically
    size_t numVariables = sizeof(variables) / sizeof(variables[0]);

    char *expandedString = expandVariablesRecursive(input, variables, values, numVariables);
    printf("Expanded string: %s\n", expandedString);
    free(expandedString); // Remember to free the allocated memory
    return 0;
}
