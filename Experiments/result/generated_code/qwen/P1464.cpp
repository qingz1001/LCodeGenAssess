#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE 20

long long memo[MAX_VALUE + 1][MAX_VALUE + 1][MAX_VALUE + 1];

long long w(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) return 1;
    if (a > MAX_VALUE || b > MAX_VALUE || c > MAX_VALUE) return w(MAX_VALUE, MAX_VALUE, MAX_VALUE);
    if (memo[a][b][c] != -1) return memo[a][b][c];
    
    if (a < b && b < c) {
        memo[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
    } else {
        memo[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
    }
    
    return memo[a][b][c];
}

int main() {
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c) == 3 && !(a == -1 && b == -1 && c == -1)) {
        for (int i = 0; i <= MAX_VALUE; ++i) {
            for (int j = 0; j <= MAX_VALUE; ++j) {
                for (int k = 0; k <= MAX_VALUE; ++k) {
                    memo[i][j][k] = -1;
                }
            }
        }
        printf("w(%d, %d, %d) = %lld\n", a, b, c, w(a, b, c));
    }
    return 0;
}