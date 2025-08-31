#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <windows.h>

#define CLEAR_SCREEN "\033[2J\033[H"
#define RESET_CURSOR "\033[H"
#define SAVE_CURSOR_POS "\033[s"
#define RESTORE_CURSOR_POS "\033[u"

char buffer[1000];    
int total_characters = 0;

void print_file()
{

    fprintf(stdout, CLEAR_SCREEN);
    for(int char_p = 0; char_p <= total_characters; char_p++)
    {
        fprintf(stdout, "%c", buffer[char_p]);
    }
    fprintf(stdout, RESET_CURSOR);
}

int editor(char* filename)
{
    FILE* fp = fopen(filename, "a+");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return -1;
    }

    // file buffer -> contains contents of the file
    char c;

    // Fill buffer
    while ((c = fgetc(fp)) != EOF)
    {
        if (total_characters < 1000)
        {
            buffer[total_characters++] = c;
        }
        else
        {
            fprintf(stderr, "File is too big\n");
            return -1;
        }
    }
    int cursor_pos = 0;

    print_file();
}

int main (int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: clit <filename>\n");
        exit(-1);
    }

    // argv[1] -> filename
    int rc = editor(argv[1]);

    return rc;
}