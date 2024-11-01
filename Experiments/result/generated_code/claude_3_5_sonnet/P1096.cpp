#include <stdio.h>

long long hanoi(int n) {
    if (n == 1) {
        return 2;
    }
    return 3 * hanoi(n - 1) + 2;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", hanoi(n));
    return 0;
}