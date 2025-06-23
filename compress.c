#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool argument_check(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    if (!argument_check(argc, argv))
    {
        return 1;
    }
    return 0;
}

bool argument_check(int argc, char* argv[])
{
    if (argc != 5) {
        printf("Usage: ./boots (-c|-d) (-rle|-huff) <input_file> <output_file>");
        return false;
    }

    if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0) {
        return false;
    }

    if (strcmp(argv[2], "-rle") != 0 && strcmp(argv[2], "-huff") != 0) {
        return false;
    }

    return true;
}