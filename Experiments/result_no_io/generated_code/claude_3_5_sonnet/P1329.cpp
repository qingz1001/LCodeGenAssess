#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MOD 18446744073709551616ULL

unsigned long long dp[MAX_N + 1][MAX_N * 2 + 1];
int sequence[MAX_N];
int n, s;
unsigned long long count = 0;
int printed = 0;

void generate_sequence(int index, int last, int sum) {
    if (index == n) {
        if (sum == s) {
            if (printed < 100) {
                for (int i = 0; i < n; i++) {
                    printf("%d ", sequence[i]);
                }
                printf("\n");
                printed++;
            }
        }
        return;
    }
    
    if (last == 0) {
        sequence[index] = 1;
        generate_sequence(index + 1, 1, sum + 1);
        sequence[index] = 0;
        generate_sequence(index + 1, 0, sum);
    } else {
        sequence[index] = last - 1;
        generate_sequence(index + 1, last - 1, sum + last - 1);
        sequence[index] = last + 1;
        generate_sequence(index + 1, last + 1, sum + last + 1);
    }
}

unsigned long long count_sequences() {
    memset(dp, 0, sizeof(dp));
    dp[1][MAX_N] = 1;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= MAX_N * 2; j++) {
            if (j > 0) dp[i][j] += dp[i-1][j-1];
            if (j < MAX_N * 2) dp[i][j] += dp[i-1][j+1];
            dp[i][j] %= MOD;
        }
    }
    
    return dp[n][s + MAX_N];
}

int main() {
    scanf("%d %d", &n, &s);
    
    count = count_sequences();
    printf("%llu\n", count);
    
    sequence[0] = 0;
    generate_sequence(1, 0, 0);
    
    return 0;
}