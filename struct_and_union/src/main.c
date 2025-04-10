#include <stdio.h>
#include <stdint.h>

// typedef struct {
//     uint16_t day : 5;
//     uint16_t month : 4;
//     uint16_t year : 7;
// } Date_t;
/* Remember that the year is based at 1980 */

typedef struct {
    uint16_t hour : 5;
    uint16_t min : 6;
    uint16_t sec : 5;
} Time_t;

typedef union{
    struct{
        uint16_t day : 5;
        uint16_t month : 4;
        uint16_t year : 7;
    } date;
    uint16_t date_time;
}Date_t;

int main()
{
    Date_t date;
    date.date_time = 0x1234;
    printf("Date: %u/%u/%u\n", date.date.day, date.date.month, date.date.year);
    printf("Date time: %u\n", date.date_time);
    printf("Size of Date_t: %zu bytes\n", sizeof(Date_t));
}