#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

bool argument_check(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    if (!argument_check(argc, argv))
    {
        return 1;
    }

    char *test_literal = "AAAABBBAABBBBBCCCCCCCDABCDBAAABBBBCCCD";
    char test[100];
    strcpy(test, test_literal);
    char rle[200];

    int length = 1;
    for (int i = 0, n = strlen(test); i < n; i++)
    {
        if (test[i] == test[i + 1])
        {
            length++;
        }
        else 
        {
            length = 1;
        }
        
        if (length >= 4)
        {
            rle[i] = length;
            rle[i + 1] = test[i];
        }
    }

    for (int i = 0, n = strlen(rle); i < n; i++)
    {
        if (isdigit(rle[i]))
        {
            printf("%i", rle[i]);
        }
        else
        {
            printf("%c", rle[i]);
        }
    }
    return 0;
}

bool argument_check(int argc, char* argv[])
{
    if (argc != 5) {
        printf("Usage: ./boots (-c|-d) (-rle|-huff) <input_file> <output_file>");
        return false;
    }

    if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0) 
    {
        printf("First argument must be -c or -d.\n");
        return false;
    }

    if (strcmp(argv[2], "-rle") != 0 && strcmp(argv[2], "-huff") != 0)
    {
        printf("Second argument must be -rle or -huff.\n");
        return false;
    }

    FILE *file = fopen(argv[3], "rb");
    if (file == NULL)
    {
        printf("Could not open input file: %s", argv[3]);
        return false;
    }
    fclose(file);

    return true;
}

// char* rle_compress(const char* )