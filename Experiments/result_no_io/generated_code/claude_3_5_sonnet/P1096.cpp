#include <stdio.h>

long long hanoi(int n) {
    if (n == 1) {
        return 3;
    }
    return 3 * hanoi(n - 1) + 2;
}

int main() {
    int n;
    scanf("%d", &n);
    
    long long result = hanoi(n);
    printf("%lld\n", result);
    
    return 0;
}