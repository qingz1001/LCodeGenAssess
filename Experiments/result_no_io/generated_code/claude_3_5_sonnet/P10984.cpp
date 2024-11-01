#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 18
#define MOD 1000000007

int digit_codes[10] = {
    0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011,
    0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011
};

int states[MAX_DIGITS];
long long dp[MAX_DIGITS][2];

int is_valid(int state, int digit) {
    return (state & digit_codes[digit]) == state;
}

int main() {
    int i, j, k;
    
    for (i = 0; i < MAX_DIGITS; i++) {
        scanf("%d", &states[i]);
    }

    memset(dp, 0, sizeof(dp));
    
    for (j = 0; j < 10; j++) {
        if (is_valid(states[0], j)) {
            dp[0][j > 0] = 1;
        }
    }

    for (i = 1; i < MAX_DIGITS; i++) {
        for (j = 0; j < 10; j++) {
            if (is_valid(states[i], j)) {
                for (k = 0; k < 2; k++) {
                    dp[i][k || j > 0] = (dp[i][k || j > 0] + dp[i-1][k]) % MOD;
                }
            }
        }
    }

    printf("%lld\n", (dp[MAX_DIGITS-1][0] + dp[MAX_DIGITS-1][1]) % MOD);

    return 0;
}