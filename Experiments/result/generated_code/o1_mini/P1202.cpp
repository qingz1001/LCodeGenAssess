#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int counts[7] = {0};
    int current_day = 0; // 0: Monday, ..., 6: Sunday
    for(int year = 1900; year < 1900 + n; year++){
        // Determine if leap year
        int leap = 0;
        if(year % 400 == 0){
            leap = 1;
        }
        else if(year % 100 == 0){
            leap = 0;
        }
        else if(year % 4 == 0){
            leap = 1;
        }
        // Iterate over each month
        for(int month = 1; month <= 12; month++){
            // Calculate day of week for 13th
            int day_13 = (current_day + 12) % 7;
            int index = (day_13 + 2) % 7;
            counts[index]++;
            // Determine days in month
            int days_in_month;
            if(month == 2){
                days_in_month = leap ? 29 : 28;
            }
            else if(month == 4 || month == 6 || month == 9 || month == 11){
                days_in_month = 30;
            }
            else{
                days_in_month = 31;
            }
            current_day = (current_day + days_in_month) % 7;
        }
    }
    printf("%d %d %d %d %d %d %d", counts[0], counts[1], counts[2], counts[3], counts[4], counts[5], counts[6]);
    return 0;
}