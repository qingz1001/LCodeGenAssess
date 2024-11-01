#include <stdio.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    long long result = (long long)(n + 1) * (m + 1);
    printf("%lld\n", result);
    return 0;
}