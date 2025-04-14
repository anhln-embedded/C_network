/*
 ******************************************************************************
 * @file       safe_string.h
 * @author     Luu Ngoc Anh
 * @date       11/04/2025
 * @brief      Safe string and memory operation macros
 ******************************************************************************
 */

 #ifndef __SAFE_STRING_H__
 #define __SAFE_STRING_H__
 
 #include <string.h>
 #include <stddef.h>
 
 /* Memory operations */
 #define SAFE_MEMCHR(str, c, n)        (((str) != NULL) ? memchr((str), (c), (n)) : NULL)
 #define SAFE_MEMCMP(s1, s2, n)        (((s1) && (s2)) ? memcmp((s1), (s2), (n)) : -1)
 #define SAFE_MEMCPY(dest, src, n)     (((dest) && (src)) ? memcpy((dest), (src), (n)) : NULL)
 #define SAFE_MEMMOVE(dest, src, n)    (((dest) && (src)) ? memmove((dest), (src), (n)) : NULL)
 #define SAFE_MEMSET(str, c, n)        ((str) ? memset((str), (c), (n)) : NULL)
 
 /* String operations */
 #define SAFE_STRCAT(dest, src)        (((dest) && (src)) ? strcat((dest), (src)) : NULL)
 #define SAFE_STRNCAT(dest, src, n)    (((dest) && (src)) ? strncat((dest), (src), (n)) : NULL)
 #define SAFE_STRCHR(str, c)           ((str) ? strchr((str), (c)) : NULL)
 #define SAFE_STRCMP(s1, s2)           (((s1) && (s2)) ? strcmp((s1), (s2)) : -1)
 #define SAFE_STRNCMP(s1, s2, n)       (((s1) && (s2)) ? strncmp((s1), (s2), (n)) : -1)
 #define SAFE_STRCOLL(s1, s2)          (((s1) && (s2)) ? strcoll((s1), (s2)) : -1)
 #define SAFE_STRCPY(dest, src)        (((dest) && (src)) ? strcpy((dest), (src)) : NULL)
 #define SAFE_STRNCPY(dest, src, n)    (((dest) && (src)) ? strncpy((dest), (src), (n)) : NULL)
 #define SAFE_STRCSPN(s1, s2)          (((s1) && (s2)) ? strcspn((s1), (s2)) : 0)
 #define SAFE_STRERROR(errnum)         strerror((errnum))
 #define SAFE_STRLEN(str)              ((str) ? strlen((str)) : 0)
 #define SAFE_STRPBRK(s1, s2)          (((s1) && (s2)) ? strpbrk((s1), (s2)) : NULL)
 #define SAFE_STRRCHR(str, c)          ((str) ? strrchr((str), (c)) : NULL)
 #define SAFE_STRSPN(s1, s2)           (((s1) && (s2)) ? strspn((s1), (s2)) : 0)
 #define SAFE_STRSTR(hay, needle)      (((hay) && (needle)) ? strstr((hay), (needle)) : NULL)
 #define SAFE_STRTOK(str, delim)       (((str) && (delim)) ? strtok((str), (delim)) : NULL)
 #define SAFE_STRXFRM(dest, src, n)    (((dest) && (src)) ? strxfrm((dest), (src), (n)) : 0)
 
 #endif /* __SAFE_STRING_H__ */
 
 /********************************* END OF FILE ********************************/
 