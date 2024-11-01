#include <stdio.h>

int main(){
    int k;
    scanf("%d", &k);
    int total = 0;
    int current_n = 1;
    while(k > 0){
        int days = current_n;
        if(k < days){
            days = k;
        }
        total += days * current_n;
        k -= days;
        current_n++;
    }
    printf("%d\n", total);
    return 0;
}