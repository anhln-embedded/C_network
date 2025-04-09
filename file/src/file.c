#include "file.h"
#include <string.h>

int count_words(FILE *file)
{
    if (file == NULL)
    {
        return -1;
    }
    int count = 0;
    char ch;
    int in_word = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            in_word = 0;
        }
        else if (in_word == 0)
        {
            in_word = 1;
            count++;
        }
    }
    rewind(file);
    return count;
}
int count_digits(FILE *file)
{
    if (file == NULL)
    {
        return -1;
    }
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch >= '0' && ch <= '9')
        {
            count++;
        }
    }
    rewind(file);
    return count;
}
int count_find_word(FILE *file, const char *word)
{
    if (file == NULL || word == NULL)
    {
        return -1;
    }
    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        char *found = strstr(buffer, word);
        while (found != NULL)
        {
            count++;
            found = strstr(found + strlen(word), word);
        }
    }
    rewind(file);

    return count;
}
int get_digits_from_file(FILE *file, int *digits)
{
    if (file == NULL || digits == NULL)
        return 0;

    int count = 0;
    int digit = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch >= '0' && ch <= '9')
        {
            digit = digit * 10 + (ch - '0');

            char next = fgetc(file);
            if (next < '0' || next > '9')
            {
                digits[count++] = digit;
                digit = 0;
            }

            if (next != EOF)
                ungetc(next, file);
        }
    }

    rewind(file); // quay lại đầu file
    return count;
}

int find_word_in_file(FILE *file, const char *word)
{
}
int delete_content_from_file(FILE *file, FILE *output_file, const char *delete_content) {}
int find_replace_in_file(FILE *file, const char *old, const char *replace) {}
int insert_string_in_file(FILE *file, const char *insert, int position) {}