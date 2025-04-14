#include <stdio.h>
#include "string_processing.h"

const char *str = "Hello, World! This is a test string. Let's count the words, sentences, paragraphs, characters, vowels, consonants, and digits. "
                  "Programming in C is fun; it helps us understand how computers work. "
                  "Do you enjoy solving problems? I hope you do! "
                  "1234567890 are digits, and they are often used in calculations. "
                  "Paragraphs are separated by newlines.\n"
                  "This is the second paragraph. It contains more text to process.";

static char str2[] = "C programming is powerful 400 and versatile. "
                        "It allows you to write efficient and high-performance code. ";
    

static char str3[] = "This is Ngoc Anh. ";

int res[100];

int main()
{
    printf("Input string:\n%s\n", str2);
    printf("size of str: %zu\n", sizeof(str));
    printf("size of str2: %zu\n", sizeof(str2));
    printf("Number of words: %d\n", string_processing_count_words(str2));
    printf("Number of digits: %d\n", string_processing_count_digits(str2));
    printf("Number of words in str2: %d\n", string_processing_count_find_word(str2, "powerful"));
    printf("Number of chars in str3: %d\n", string_processing_count_find_word(str3, "i"));
    int number_of_digits = string_processing_get_digits_from_string(str2, res);
    int i;
    for (i = 0; i < number_of_digits; i++)
    {
        printf("Digit %d: %d\n", i + 1, res[i]);
    }
    printf("find_word: %d\n", string_processing_find_word(str2, "powerful"));
    if(string_processing_find_replace(str2, "powerful", "awesome") == 0)
    {
        printf("After find_replace: %s\n", str2);
    }
    else
    {
        printf("find_replace failed\n");
    }

    if(string_processing_insert_string(str2, "Hello ", 0) == 0)
    {
        printf("After insert_string: %s\n", str2);
    }
    else
    {
        printf("insert_string failed\n");
    }

    return 0;
}