#include <stdio.h>
#include <string.h>

#define MOD 100000000

void multiply(long long F[2][2], long long M[2][2]) {
    long long x = (F[0][0] * M[0][0] + F[0][1] * M[1][0]) % MOD;
    long long y = (F[0][0] * M[0][1] + F[0][1] * M[1][1]) % MOD;
    long long z = (F[1][0] * M[0][0] + F[1][1] * M[1][0]) % MOD;
    long long w = (F[1][0] * M[0][1] + F[1][1] * M[1][1]) % MOD;
    
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(long long F[2][2], char* n) {
    if (strcmp(n, "1") == 0 || strlen(n) == 0)
        return;

    long long M[2][2] = {{1, 1}, {1, 0}};

    power(F, n + 1);

    multiply(F, F);

    if ((n[0] - '0') % 2 == 1)
        multiply(F, M);
}

long long fib(char* n) {
    long long F[2][2] = {{1, 1}, {1, 0}};
    if (strcmp(n, "0") == 0)
        return 0;
    power(F, n);
    return F[0][0];
}

int main() {
    char n[1001];
    scanf("%s", n);
    
    long long result = fib(n);
    printf("%lld\n", result);
    
    return 0;
}