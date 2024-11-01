#include <stdio.h>

int main(){
    int budget[12];
    for(int i=0;i<12;i++) {
        scanf("%d", &budget[i]);
    }
    int current =0;
    long long saving=0;
    for(int i=0;i<12;i++){
        current +=300;
        if(current < budget[i]){
            printf("-%d",i+1);
            return 0;
        }
        current -= budget[i];
        if(current >=100){
            int saved = (current /100)*100;
            saving += saved;
            current -= saved;
        }
    }
    long long final_total = current + saving + saving /5;
    printf("%lld", final_total);
    return 0;
}