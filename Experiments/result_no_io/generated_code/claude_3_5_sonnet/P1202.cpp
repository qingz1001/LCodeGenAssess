#include <stdio.h>

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main() {
    int n, year = 1900, month = 1, day = 1, weekday = 1;
    int count[7] = {0};
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    scanf("%d", &n);
    
    while (year < 1900 + n) {
        if (day == 13) {
            count[(weekday + 5) % 7]++;
        }
        
        if (++day > daysInMonth[month - 1] + (month == 2 && isLeapYear(year))) {
            day = 1;
            if (++month > 12) {
                month = 1;
                year++;
            }
        }
        
        weekday = (weekday % 7) + 1;
    }
    
    printf("%d %d %d %d %d %d %d\n", count[5], count[6], count[0], count[1], count[2], count[3], count[4]);
    
    return 0;
}