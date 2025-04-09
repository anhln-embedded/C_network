#include <stdio.h>
#include "file.h"

int digit[100];
int g_number_of_digits = 0;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <File Name>\n", argv[0]);
        return 1;
    }

    FILE *read_file = fopen(argv[1], "r");
    if (read_file == NULL)
    {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }
    FILE *write_file = fopen("output.txt", "w");


    g_number_of_digits = get_digits_from_file(read_file, digit);
    printf("Number of digits: %d\n", g_number_of_digits);
    int i;
    for (i = 0; i < g_number_of_digits; i++)
    {
        printf("Digit %d: %d\n", i + 1, digit[i]);
    }

    if (write_file == NULL)
    {
        printf("Error opening output file\n");
        fclose(read_file);
        return 1;
    }
    fclose(write_file);
    fclose(read_file);
    return 0;
}