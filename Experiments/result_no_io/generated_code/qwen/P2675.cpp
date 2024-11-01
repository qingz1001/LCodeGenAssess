#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    long long maxBase = 0;
    
    for (int i = 0; i < N; i++) {
        long long base = 1;
        for (int j = 0; j <= i; j++) {
            base = (base * (i - j + 1)) / (j + 1) % 10007;
        }
        if (base > maxBase) {
            maxBase = base;
        }
    }
    
    printf("%lld\n", maxBase);
    
    return 0;
}