// Vilius Puskunalis 5 grupe 3 uzduotis
#include <stdio.h>
#include <stdlib.h>

#define ARGS_LENGTH 2

#define ASCII_SPACE 32
#define MAX_LINE_LENGTH 256

#define SUCCESS 0
#define READ_ERROR 1
#define WRITE_ERROR 2
#define MEMORY_ERROR 3

char* connectLine(char* line)
{
    int copyLength = 0;
    char *lineCopy = (char*) malloc(sizeof(char) * (MAX_LINE_LENGTH + 1));
    if (lineCopy == NULL)
    {
        return NULL;
    }

    // First symbol will never need to be removed
    lineCopy[0] = line[0];

    for (int i = 0; line[i + 1] != 0; ++i)
    {
        // Do not copy dashes that are between other symbols in a word, unless end of line
        if (line[i] == ASCII_SPACE
         || line[i + 1] != '-'
         || line[i + 2] == ASCII_SPACE
         || line[i + 2] == 0 // Extra case for a line that does not end with a newline symbol
         || line[i + 3] == 0)
        {
            lineCopy[++copyLength] = line[i + 1];
        }
    }

    // Add null symbol
    lineCopy[++copyLength] = 0;

    return lineCopy;
}

int fConnectLines(char* inputFileName, char* outputFileName)
{
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        return READ_ERROR;
    }

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL)
    {
        fclose(inputFile);
        return WRITE_ERROR;
    }

    char *line = (char*) malloc(sizeof(char) * (MAX_LINE_LENGTH + 1));
    if (line == NULL)
    {
        fclose(inputFile);
        fclose(outputFile);
        return MEMORY_ERROR;
    }

    while (fgets(line, MAX_LINE_LENGTH + 1, inputFile))
    {
        char *parsedLine = connectLine(line);
        if (parsedLine == NULL)
        {
            free(line);
            fclose(inputFile);
            fclose(outputFile);
            return MEMORY_ERROR;
        }

        fputs(parsedLine, outputFile);
        free(parsedLine);
    }

    free(line);
    fclose(inputFile);
    fclose(outputFile);
    return SUCCESS;
}

int main(int argc, char* argv[])
{
    if (argc > ARGS_LENGTH)
    {
        switch (fConnectLines(argv[1], argv[2]))
        {
            case READ_ERROR:
                printf("Input file not found!\n");
                break;
            case WRITE_ERROR:
                printf("Cannot create output file!\n");
                break;
            case MEMORY_ERROR:
                printf("Out of memory!\n");
                break;
            case SUCCESS:
                printf("All done.\n");
                break;
        }
    }
    else
    {
        printf("Usage: 3-3.exe [input file] [output file]\n");
    }

    return 0;
}
