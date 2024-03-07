// 4.6.23, count.c, Logan Calder
// Script will accept a file directory as a parameter and return the print of words in the file.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Main will accept int argc and char* argv[] as parameters and return the amount of words
// counted in the file directory provided.
int main(int argc, char *argv[])
{
    // Variable declarations
    #define MAX_WORD_LENGTH 30
    char str[MAX_WORD_LENGTH];
    int count = 0;

    // File variables
    FILE *file;
    file = fopen(argv[1], "r"); // Read file provided by argv[1]

    // This chunk of code precents Segmentation Fault:11
    // Prints an error message if file is empty, then exits program
    if (file == 0)
    {
        perror("fopen");
        exit(1);
    }

    // While char c is not end of file, check if is blank space.
    // If not consecutive blank space, increment int words by 1.
    while (fscanf(file,"%s",str)!=EOF){
        count++;
    }

    // Print word count (int words)
    printf("%d Words counted.\n", count);
    return (0);
}