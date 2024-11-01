#include <stdio.h>

int main(){
    int budget[12];
    for(int i=0;i<12;i++) {
        scanf("%d", &budget[i]);
    }
    int hand=0, saved_total=0;
    for(int month=1; month<=12; month++){
        hand +=300;
        int expected_end = hand - budget[month-1];
        if(expected_end >=100){
            int to_save = (expected_end /100) *100;
            saved_total += to_save;
            hand -= to_save;
        }
        if(hand >= budget[month-1]){
            hand -= budget[month-1];
        }
        else{
            printf("-%d", month);
            return 0;
        }
    }
    int total_saved_with_interest = saved_total * 120 /100;
    int result = total_saved_with_interest + hand;
    printf("%d", result);
    return 0;
}