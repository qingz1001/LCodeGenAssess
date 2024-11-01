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

    int a_prev2 = a1, a_prev = a2, a_next;
    for (int i = 3; i <= n; ++i) {
        a_next = (p * a_prev + q * a_prev2) % m;
        a_prev2 = a_prev;
        a_prev = a_next;
    }

    printf("%d\n", a_next);
    return 0;
}