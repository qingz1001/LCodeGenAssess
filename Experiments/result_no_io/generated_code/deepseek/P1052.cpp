#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 1000000000
#define MAX_M 100
#define MAX_ST 10

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int L, S, T, M;
    int stones[MAX_M];
    int dp[MAX_L + 1];
    int stone_map[MAX_L + 1];

    scanf("%d", &L);
    scanf("%d %d %d", &S, &T, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d", &stones[i]);
    }

    // Sort stones
    for (int i = 0; i < M - 1; i++) {
        for (int j = i + 1; j < M; j++) {
            if (stones[i] > stones[j]) {
                int temp = stones[i];
                stones[i] = stones[j];
                stones[j] = temp;
            }
        }
    }

    // Compress the stone positions
    int last_pos = 0;
    int new_pos = 0;
    for (int i = 0; i < M; i++) {
        if (stones[i] - last_pos > 100) {
            new_pos += 100;
        } else {
            new_pos += stones[i] - last_pos;
        }
        last_pos = stones[i];
        stones[i] = new_pos;
    }
    L = new_pos + 100;

    // Initialize dp array
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    // Initialize stone map
    memset(stone_map, 0, sizeof(stone_map));
    for (int i = 0; i < M; i++) {
        stone_map[stones[i]] = 1;
    }

    // Dynamic programming
    for (int i = 1; i <= L; i++) {
        for (int j = S; j <= T; j++) {
            if (i - j >= 0) {
                dp[i] = min(dp[i], dp[i - j] + stone_map[i]);
            }
        }
    }

    // Find the minimum stones to step on
    int min_stones = dp[L];
    for (int i = L - T + 1; i <= L; i++) {
        min_stones = min(min_stones, dp[i]);
    }

    printf("%d\n", min_stones);

    return 0;
}