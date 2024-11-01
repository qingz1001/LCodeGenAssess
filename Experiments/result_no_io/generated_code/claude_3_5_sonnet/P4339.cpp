#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1000000

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int solve(int m, int K) {
    if (K == 1) return 1;
    if (m == 1) return -1;
    
    int order = 1;
    int cycle = 1;
    
    while (1) {
        if (order % K == 0) return cycle;
        order = (order * m) % K;
        cycle++;
        if (order == 1) return -1;
        if (cycle > MAX_N) return -1;
    }
}

int main() {
    int T, m, K;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d", &m, &K);
        printf("%d\n", solve(m, K));
    }
    
    return 0;
}