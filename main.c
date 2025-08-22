#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define CLEAR_SCREEN() printf("\e[1;1H\e[2J")

int editor(char* filename)
{
    FILE* fp = fopen(filename, "a+");
    if (fp == NULL) {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    // file buffer -> contains contents of the file
    char buffer[1000];    
    char c;
    int total_characters = 0;

    // Fill buffer
    while ((c = fgetc(fp)) != EOF)
    {
        if (total_characters < 1000)
        {
            buffer[total_characters++] = c;
        }
        else
        {
            printf("File is too big\n");
            return -1;
        }
    }
    int cursor_pos = 0;
    while (1)
    {
        CLEAR_SCREEN();
        for(int char_p = 0; char_p <= total_characters; char_p++)
        {
            printf("%c", buffer[char_p]);
        }
    }

}

int main (int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: clit <filename>\n");
        exit(-1);
    }

    // argv[1] -> filename
    int rc = editor(argv[1]);

    return rc;
}