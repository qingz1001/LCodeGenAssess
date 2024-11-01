#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int L, R;
    scanf("%d %d", &L, &R);
    int count = 0;
    for (int i = L; i <= R; i++) {
        if (is_prime(i)) count++;
    }
    printf("%d\n", count);
    return 0;
}