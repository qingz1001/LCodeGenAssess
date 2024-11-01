#include <stdio.h>

int main(){
    int n;
    long long x, y;
    scanf("%d %lld %lld", &n, &x, &y);
    long long total = 0;
    for(int i=0; i<n; i++){
        long long a;
        scanf("%lld", &a);
        long long cost1 = a * x;
        long long cost2 = y;
        if(cost1 < cost2){
            total += cost1;
        }
        else{
            total += cost2;
        }
    }
    printf("%lld\n", total);
    return 0;
}