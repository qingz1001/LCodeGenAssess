#include <stdio.h>

int main(){
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);
    long long total = 0;
    for(int i = 0; i < n; i++){
        int a;
        scanf("%d", &a);
        long long cost = (long long)x * a;
        if(cost > y){
            cost = y;
        }
        total += cost;
    }
    printf("%lld\n", total);
    return 0;
}