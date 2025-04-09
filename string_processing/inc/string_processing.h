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

int count_words(const char *str);
int count_digits(const char *str);  
int count_find_word(const char *str, const char *word);

int get_digits_from_string(const char *str, int *digits);
int find_word(const char *str, const char *word);

void delete_content(char *str, char *str_out, const char *delete_content);
void find_replace(char *str, const char *old, const char *replace);
 #endif
 
 /********************************* END OF FILE ********************************/
 /******************************************************************************/