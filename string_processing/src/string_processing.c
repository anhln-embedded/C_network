#include "string_processing.h"
#include "safe_string_macros.h"

int string_processing_count_words(const char *str)
{
    if (str == NULL || SAFE_STRLEN(str) == 0)
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

int string_processing_count_digits(const char *str)
{
    if (str == NULL || SAFE_STRLEN(str) == 0)
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

int string_processing_count_find_word(const char *str, const char *word)
{
    if (str == NULL || word == NULL)
        return 0;

    int count = 0;
    const char *found = str;

    while ((found = SAFE_STRSTR(found, word)) != NULL)
    {
        count++;
        found += SAFE_STRLEN(word);
    }

    return count;
}

int string_processing_find_word(const char *str, const char *word)
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

int string_processing_get_digits_from_string(const char *str, int *digits)
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

int string_processing_delete_content(char *str, char *str_out, const char *delete_content)
{
    if (str == NULL || str_out == NULL || delete_content == NULL)
        return -1;
    char *pos = str;
    char *out_pos = str_out;
    while (*pos)
    {

        if(SAFE_STRNCMP(pos, delete_content, strlen(delete_content)) == 0)
        {
            pos += SAFE_STRLEN(delete_content);
        }
        else
        {
            *out_pos++ = *pos++;
        }
    }
    *out_pos = '\0';
    return 0;
}

int string_processing_find_replace(char *str, const char *old, const char *replace)
{
    if (str == NULL || old == NULL || replace == NULL)
    {
        return -1;
    }
    static char buffer[4096];
    char *pos = str;
    while ((pos = SAFE_STRSTR(pos, old)) != NULL)
    {
        SAFE_STRNCPY(buffer, str, pos - str);
        buffer[pos - str] = '\0';
        SAFE_STRCAT(buffer, replace);
        SAFE_STRCAT(buffer, pos + SAFE_STRLEN(old));
        SAFE_STRCPY(str, buffer);
        pos = str + (pos - str) + SAFE_STRLEN(replace);

    }
    return 0;
}

int string_processing_insert_string(char *str, const char *insert, int position)
{
    if(str == NULL || insert == NULL || position < 0)
    {
        return -1;
    }
    int str_len = SAFE_STRLEN(str);
    int insert_len = SAFE_STRLEN(insert);
    if(position > str_len)
    {
        return -1;
    }
    char buffer[4096];  
    SAFE_STRNCPY(buffer, str, position);
    buffer[position] = '\0';
    SAFE_STRCAT(buffer, insert);
    SAFE_STRCAT(buffer, str + position);
    SAFE_STRCPY(str, buffer);
    return 0;
}