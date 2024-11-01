#include <stdio.h>
#include <string.h>

#define MAXM 10001
#define MAXO 5
#define MAXS 301
#define MAXU 101

long long dp[MAXM][MAXO][MAXS][MAXU];
long long sum[MAXM];

int M, P, A, O, S, U;

long long quick_pow(long long base, int exp) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = res * base % P;
        base = base * base % P;
        exp >>= 1;
    }
    return res;
}

int main() {
    scanf("%d %d", &M, &P);
    scanf("%d", &A);
    scanf("%d", &O);
    scanf("%d", &S);
    scanf("%d", &U);

    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = 1;

    for (int m = 0; m <= M; m++) {
        for (int o = 0; o < O; o++) {
            for (int s = 0; s < S; s++) {
                for (int u = 0; u < U; u++) {
                    if (dp[m][o][s][u] == 0) continue;
                    
                    long long val = dp[m][o][s][u];
                    sum[m] = (sum[m] + val) % P;

                    if (m < M) {
                        int no = (o + 1) % O;
                        int ns = (s + 1) % S;
                        int nu = (u + 1) % U;
                        dp[m+1][no][ns][nu] = (dp[m+1][no][ns][nu] + val) % P;
                    }
                }
            }
        }
    }

    long long result = 1;
    for (int i = 1; i <= A; i++) {
        if (i <= M) {
            result = result * ((sum[M] - sum[M-i] + P) % P) % P;
        } else {
            result = result * ((O * (i*i % P) % P + S * i % P + U) % P) % P;
        }
    }

    printf("%lld\n", result);
    return 0;
}