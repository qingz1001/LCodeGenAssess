#include <stdio.h>

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        long long n;
        scanf("%lld", &n);
        if(n ==1){
            printf("0\n");
            continue;
        }
        int k=0;
        long long power=1;
        while(power <n){
            power <<=1;
            k++;
        }
        printf("%d\n", k);
    }
    return 0;
}