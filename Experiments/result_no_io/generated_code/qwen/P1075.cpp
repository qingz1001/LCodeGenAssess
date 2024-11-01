#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int n, p1, p2;
    scanf("%d", &n);

    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0 && is_prime(i) && is_prime(n / i)) {
            p1 = i;
            p2 = n / i;
            break;
        }
    }

    printf("%d\n", p2 > p1 ? p2 : p1);
    return 0;
}