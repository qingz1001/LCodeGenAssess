#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 10 == 2 || i % 10 == 0 || i % 10 == 1 || i % 10 == 9) {
            sum += i;
        }
    }
    
    printf("%lld\n", sum);
    
    return 0;
}