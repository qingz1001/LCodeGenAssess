#include <stdio.h>

int main() {
    int p, q, a1, a2, n, m;
    scanf("%d %d %d %d %d %d", &p, &q, &a1, &a2, &n, &m);

    if (n == 1) {
        printf("%d\n", a1 % m);
        return 0;
    }
    if (n == 2) {
        printf("%d\n", a2 % m);
        return 0;
    }

    long long a_prev2 = a1 % m;
    long long a_prev1 = a2 % m;

    for (int i = 3; i <= n; ++i) {
        long long a_next = (p * a_prev1 + q * a_prev2) % m;
        a_prev2 = a_prev1;
        a_prev1 = a_next;
    }

    printf("%lld\n", a_prev1);

    return 0;
}