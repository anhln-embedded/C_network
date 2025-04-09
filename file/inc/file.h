/*
 ******************************************************************************
 * @file       file.h
 * @author     Luu Ngoc Anh
 * @date       09/04/2025
 ******************************************************************************
 */

#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>

int count_words(FILE *file);
int count_digits(FILE *file);
int count_find_word(FILE *file, const char *word);
int get_digits_from_file(FILE *file, int *digits);
int find_word_in_file(FILE *file, const char *word);
int delete_content_from_file(FILE *file, FILE *output_file, const char *delete_content);
int find_replace_in_file(FILE *file, const char *old, const char *replace);
int insert_string_in_file(FILE *file, const char *insert, int position);


#endif  

 /********************************* END OF FILE ********************************/
/******************************************************************************/