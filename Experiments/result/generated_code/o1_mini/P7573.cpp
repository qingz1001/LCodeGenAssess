#include <stdio.h>

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        long long n;
        scanf("%lld", &n);
        if(n ==1){
            printf("0\n");
        }
        else{
            printf("%lld\n", (n +1)/2);
        }
    }
    return 0;
}