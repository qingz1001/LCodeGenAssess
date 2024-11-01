#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int counts[7] = {0};
    int current = 0; // 0: Monday, ..., 6: Sunday
    for(int year=1900; year <1900+n; year++){
        for(int month=1; month<=12; month++){
            int weekday_13 = (current +12)%7;
            counts[weekday_13]++;
            int days;
            if(month ==2){
                int leap = 0;
                if(year%4 ==0){
                    if(year%100 !=0 || year%400 ==0){
                        leap =1;
                    }
                }
                days = leap ? 29 : 28;
            }
            else if(month==4 || month==6 || month==9 || month==11){
                days =30;
            }
            else{
                days=31;
            }
            current = (current + days)%7;
        }
    }
    printf("%d %d %d %d %d %d %d\n", counts[5], counts[6], counts[0], counts[1], counts[2], counts[3], counts[4]);
    return 0;
}