#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    long long base = 1;
    for (int i = 2; i <= N; i++) {
        base = (base * i) % 10007;
    }
    
    printf("%lld\n", base);
    
    return 0;
}