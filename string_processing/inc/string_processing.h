/*
 ******************************************************************************
 * @file       string_processing.h
 * @author     Luu Ngoc Anh
 * @date       08/04/2025
 ******************************************************************************
 */

#ifndef __STRING_PROCESSING_H__
#define __STRING_PROCESSING_H__

#include <string.h>

int string_processing_count_words(const char *str);
int string_processing_count_digits(const char *str);
int string_processing_count_find_word(const char *str, const char *word);

int string_processing_get_digits_from_string(const char *str, int *digits);
int string_processing_find_word(const char *str, const char *word);

int string_processing_delete_content(char *str, char *str_out, const char *delete_content);
int string_processing_find_replace(char *str, const char *old, const char *replace);
int string_processing_insert_string(char *str, const char *insert, int position);

// #define LN_STRCPY(dest, src) \
//     do { \
//         if (dest != NULL && src != NULL) { \
//             strncpy(dest, src, sizeof(dest)); \
//             dest[sizeof(dest) - 1] = '\0'; \
//         } \
//     } while (0)

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/