#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int N, m1, m2;
    scanf("%d", &N);
    scanf("%d %d", &m1, &m2);
    long long M = 1LL * m1 * m2;

    int S[10001];
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }

    int result = -1;
    for (int i = 0; i < N; i++) {
        int s = S[i];
        if (gcd(s, M) == 1) {
            continue;
        }
        int time = 0;
        while ((long long)s % M != 0) {
            s *= S[i];
            time++;
        }
        if (result == -1 || time < result) {
            result = time;
        }
    }

    printf("%d\n", result);

    return 0;
}