#include "string_processing.h"

#include <string.h>

int count_words(const char *str)
{
    if (str == NULL || strlen(str) == 0)
        return 0;

    int count = 0;
    int in_word = 0;

    while (*str)
    {
        if (*str == ' ' || *str == '\t' || *str == '\n')
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            in_word = 1;
            count++;
        }
        str++;
    }

    return count;
}

int count_digits(const char *str)
{
    if (str == NULL || strlen(str) == 0)
        return 0;

    int count = 0;

    while (*str)
    {
        if (*str >= '0' && *str <= '9')
        {
            count++;
        }
        str++;
    }

    return count;
}

int count_find_word(const char *str, const char *word)
{
    if (str == NULL || word == NULL)
        return 0;

    int count = 0;
    const char *found = str;

    while ((found = strstr(found, word)) != NULL)
    {
        count++;
        found += strlen(word);
    }

    return count;
}

int find_word(const char *str, const char *word)
{
    if (str == NULL || word == NULL)
        return -1;

    const char *found = strstr(str, word);
    if (found != NULL)
    {
        return found - str;
    }
    return -1;
}

int get_digits_from_string(const char *str, int *digits)
{
    if (str == NULL || digits == NULL)
        return 0;

    int count = 0;
    int digit = 0;
    while (*str)
    {
        if (*str >= '0' && *str <= '9')
        {
            digit = digit * 10 + (*str - '0');
            if (*(str + 1) < '0' || *(str + 1) > '9')
            {
                digits[count++] = digit;
                digit = 0;
            }
        }
        str++;
    }

    return count;
}

void delete_content(char *str, char *str_out, const char *delete_content)
{
    if (str == NULL || str_out == NULL || delete_content == NULL)
        return;

    const char *found = str;
    int len = strlen(delete_content);
    char *out_ptr = str_out;

    while ((found = strstr(found, delete_content)) != NULL)
    {
        while (str < found)
        {
            *out_ptr++ = *str++;
        }
        str += len; // Skip the delete_content
        found = str;
    }

    // Copy the remaining part of the string
    while (*str)
    {
        *out_ptr++ = *str++;
    }

    *out_ptr = '\0'; // Null-terminate the output string
}