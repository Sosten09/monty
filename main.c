#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

#define MAX_LINE_LENGTH 1024

bus_t bus = {NULL, NULL, NULL, 0};

int main(int argc, char *argv[])
{
    char *content = NULL;
    FILE *file;
    size_t size = MAX_LINE_LENGTH;
    stack_t *stack = NULL;
    unsigned int counter = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    bus.file = file;

    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fgets(content, MAX_LINE_LENGTH, file) != NULL)
    {
        bus.content = content;
        counter++;

        // Remove the newline character if present
        size_t len = strlen(content);
        if (len > 0 && content[len - 1] == '\n') {
            content[len - 1] = '\0';
        }

        execute(content, &stack, counter, file);
        free(content);
    }

    free_stack(stack);
    fclose(file);
    return 0;
}
}
