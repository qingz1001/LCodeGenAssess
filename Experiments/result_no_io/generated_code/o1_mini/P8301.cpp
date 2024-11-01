#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int a, b;
    int count_a0 = 0, count_b0 = 0;
    for(int i=0;i<n;i++){
        scanf("%d", &a);
        if(a == 0) count_a0++;
    }
    for(int i=0;i<n;i++){
        scanf("%d", &b);
        if(b == 0) count_b0++;
    }
    int diff = count_a0 > count_b0 ? count_a0 - count_b0 : count_b0 - count_a0;
    printf("%d\n", diff);
    return 0;
}