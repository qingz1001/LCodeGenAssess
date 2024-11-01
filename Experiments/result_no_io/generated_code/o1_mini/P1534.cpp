#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int a, b;
    long long sum = 0;
    for(int i=0;i<n;i++){
        scanf("%d %d", &a, &b);
        sum += (a + b - 8);
    }
    printf("%lld\n", sum);
    return 0;
}