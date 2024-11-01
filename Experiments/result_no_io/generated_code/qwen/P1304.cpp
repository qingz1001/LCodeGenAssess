#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void find_min_prime_pair(int n, int *p1, int *p2) {
    for (*p1 = 2; *p1 <= n / 2; (*p1)++) {
        if (is_prime(*p1)) {
            *p2 = n - *p1;
            if (is_prime(*p2)) {
                break;
            }
        }
    }
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 1; 2 * i + 2 <= N; i++) {
        int p1, p2;
        find_min_prime_pair(2 * i + 2, &p1, &p2);
        printf("%d=%d+%d\n", 2 * i + 2, p1, p2);
    }
    return 0;
}