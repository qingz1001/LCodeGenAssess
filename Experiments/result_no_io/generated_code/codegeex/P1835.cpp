#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int main() {
    int L, R;
    scanf("%d%d", &L, &R);
    int count = 0;
    for (int i = L; i <= R; i++) {
        if (is_prime(i)) count++;
    }
    printf("%d\n", count);
    return 0;
}