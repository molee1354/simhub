#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lang.h"

int main(int argc, char** argv) {
    // for file input
    if (argc > 1) {
        FILE *file;
        long fileSize;
        char *content;

        // Open the file in read mode
        file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("Error opening the file");
            return 1;
        }

        // Determine the file size
        fseek(file, 0, SEEK_END);
        fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Allocate memory for the content
        content = (char *)malloc(fileSize + 1);
        if (content == NULL) {
            perror("Memory allocation error");
            return 1;
        }

        // Read file content into the allocated memory
        fread(content, 1, fileSize, file);
        content[fileSize] = '\0';  // Null-terminate the content

        // Close the file
        fclose(file);

        // Now 'content' holds the file's content as a character array
        puts("File content:");
        printf("---\n%s\n---\n\n", content);

        // tokenize file into tokens
        Array* myTokens = tokenize(content, fileSize);
        printArray(myTokens);

        /* 
         * deleteHead() must come after any access to the 'head' token
         */

        /* Token head = getElement(myTokens, 0);
        printf("head: {%s, %d}\n", head.value, head.type);
        deleteHead(myTokens);
        printArray(myTokens); */

        // Free the allocated memory
        free(content);
        freeArray(myTokens);
    }

    // shell
    else {
        puts("mlang v0.1.0");
        while (1) {
            char input[128];
            printf("\n>>> ");
            scanf("%[^\n]s", input);
            getchar();
            if (!strcmp("exit", input)) {
                exit(0);
            } 
            Array* genTokens = tokenize(input, strlen(input));
            printArray(genTokens);
            freeArray(genTokens);
        }
    }
    return 0;
}
