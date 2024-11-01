#include <stdio.h>
#include <string.h>

#define N 18
#define MOD 1000000007

int stateCodes[N] = {
    0b0000011, 0b1001011, 0b0000001, 0b0100001, 0b0101011, 0b0110110,
    0b1111111, 0b0010110, 0b0101001, 0b0010110, 0b1011100, 0b0100110,
    0b1010000, 0b0010011, 0b0001111, 0b0101101, 0b0110101, 0b1101010
};

int digitCodes[10] = {
    0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011,
    0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011
};

long long dp[N][2];

int isPossible(int stateCode, int digit) {
    return (stateCode & digitCodes[digit]) == stateCode;
}

int main() {
    memset(dp, 0, sizeof(dp));
    
    for (int digit = 0; digit <= 9; digit++) {
        if (isPossible(stateCodes[0], digit)) {
            dp[0][digit > 0] = 1;
        }
    }
    
    for (int i = 1; i < N; i++) {
        for (int digit = 0; digit <= 9; digit++) {
            if (isPossible(stateCodes[i], digit)) {
                dp[i][1] = (dp[i][1] + dp[i-1][0] + dp[i-1][1]) % MOD;
                if (digit == 0) {
                    dp[i][0] = (dp[i][0] + dp[i-1][0]) % MOD;
                }
            }
        }
    }
    
    printf("%lld\n", (dp[N-1][0] + dp[N-1][1]) % MOD);
    
    return 0;
}