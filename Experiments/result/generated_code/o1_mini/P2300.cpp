#include <stdio.h>
#include <stdint.h>

int main(){
    int n;
    scanf("%d", &n);
    if(n <=0){
        printf("0\n");
        return 0;
    }
    int i;
    uint64_t p;
    uint64_t previous_sum = 0;
    uint64_t current_sum = 0;
    int count =0;
    for(i=0;i<n;i++){
        scanf("%llu", &p);
        current_sum += p;
        if(current_sum >= previous_sum){
            count++;
            previous_sum = current_sum;
            current_sum =0;
        }
    }
    printf("%d\n", n - count);
    return 0;
}