#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGUMENTS 10

typedef struct Argument {
    char *value;
    struct Argument *next;
} Argument;

typedef struct Query {
    short type;
    char hasF;
    Argument *arguments;
    int numArguments;
    struct Query *next;
} Query;

// Parse a line and populate a Query struct
void parseLine(const char *line, Query *query) {
    // Assuming the line format is: <type> <hasF> <numArguments> <arg1> <arg2> ...
    sscanf(line, "%hd %c %d", &query->type, &query->hasF, &query->numArguments);

    // Process the arguments
    char *token;
    char *rest = strdup(line);  // Duplicate the line because strsep modifies the string
    char *saveptr;

    for (int i = 0; i < query->numArguments; ++i) {
        token = strtok_r(rest, " ", &saveptr);
        if (token == NULL) {
            fprintf(stderr, "Error parsing arguments in line: %s\n", line);
            break;
        }

        Argument *arg = malloc(sizeof(Argument));
        if (!arg) {
            fprintf(stderr, "Memory allocation error\n");
            exit(1);
        }

        arg->value = strdup(token);
        arg->next = NULL;

        if (i == 0) {
            query->arguments = arg;
        } else {
            Argument *lastArg = query->arguments;
            while (lastArg->next != NULL) {
                lastArg = lastArg->next;
            }
            lastArg->next = arg;
        }

        rest = NULL;  // For subsequent calls to strtok_r
    }

    free(rest);  // Free duplicated string
}

// Free memory allocated for arguments
void freeArguments(Argument *arguments) {
    while (arguments != NULL) {
        Argument *nextArg = arguments->next;
        free(arguments->value);
        free(arguments);
        arguments = nextArg;
    }
}

int main() {
    // Example usage
    const char *line = "3 F 3 HTL1201";
    Query query;
    parseLine(line, &query);

    // Print the parsed data
    printf("Type: %d, hasF: %c, Num Arguments: %d\n", query.type, query.hasF, query.numArguments);
    Argument *arg = query.arguments;
    while (arg != NULL) {
        printf("Argument: %s\n", arg->value);
        arg = arg->next;
    }

    // Free allocated memory
    freeArguments(query.arguments);

    return 0;
}
