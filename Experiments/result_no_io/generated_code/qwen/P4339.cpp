#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int find_min_n(int m, int K) {
    if (gcd(m, K) != 1) {
        return -1;
    }
    return m * K + 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int m, K;
        scanf("%d %d", &m, &K);
        printf("%d\n", find_min_n(m, K));
    }
    return 0;
}