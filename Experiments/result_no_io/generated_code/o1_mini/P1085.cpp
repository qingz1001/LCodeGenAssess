#include <stdio.h>

int main(){
    int school, mom;
    int total;
    int max_sum = -1;
    int max_day = 0;

    for(int day=1; day<=7; day++){
        scanf("%d %d", &school, &mom);
        total = school + mom;
        if(total > 8){
            if(total > max_sum){
                max_sum = total;
                max_day = day;
            }
        }
    }

    if(max_sum > 8){
        printf("%d\n", max_day);
    }
    else{
        printf("0\n");
    }

    return 0;
}