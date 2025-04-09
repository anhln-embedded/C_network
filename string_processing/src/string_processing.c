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

int delete_content(char *str, char *str_out, const char *delete_content)
{
    if (str == NULL || str_out == NULL || delete_content == NULL)
        return -1;
    char *pos = str;
    char *out_pos = str_out;
    while (*pos)
    {
        if (strncmp(pos, delete_content, strlen(delete_content)) == 0)
        {
            pos += strlen(delete_content);
        }
        else
        {
            *out_pos++ = *pos++;
        }
    }
    *out_pos = '\0';
    return 0;
}

int find_replace(char *str, const char *old, const char *replace)
{
    if (str == NULL || old == NULL || replace == NULL)
    {
        return -1;
    }
    static char buffer[4096];
    char *pos = str;
    while ((pos = strstr(pos, old)) != NULL)
    {
        strncpy(buffer, str, pos - str);
        buffer[pos - str] = '\0';
        strcat(buffer, replace);
        strcat(buffer, pos + strlen(old));
        strcpy(str, buffer);
        pos += strlen(replace);
    }
    return 0;
}

int insert_string(char *str, const char *insert, int position)
{
    if(str == NULL || insert == NULL || position < 0)
    {
        return -1;
    }
    int str_len = strlen(str);
    int insert_len = strlen(insert);
    if(position > str_len)
    {
        return -1;
    }
    char buffer[4096];  
    strncpy(buffer, str, position);
    buffer[position] = '\0';
    strcat(buffer, insert);
    strcat(buffer, str + position);
    strcpy(str, buffer);
    return 0;
}