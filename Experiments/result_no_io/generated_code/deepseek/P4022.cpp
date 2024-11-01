#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1100000
#define MAX_M 1000

char standard_essays[MAX_M][MAX_LEN];
char essays[MAX_LEN];
int dp[MAX_LEN];
bool is_familiar[MAX_LEN];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%s", standard_essays[i]);
    }

    for (int i = 0; i < N; i++) {
        scanf("%s", essays);
        int len = strlen(essays);

        memset(is_familiar, false, sizeof(is_familiar));
        for (int l = 1; l <= len; l++) {
            bool found = false;
            for (int j = 0; j < M; j++) {
                int std_len = strlen(standard_essays[j]);
                for (int k = 0; k <= std_len - l; k++) {
                    if (strncmp(&standard_essays[j][k], &essays[0], l) == 0) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            is_familiar[l] = found;
        }

        int left = 0, right = len;
        while (left < right) {
            int mid = (left + right + 1) / 2;
            memset(dp, 0, sizeof(dp));
            for (int j = 1; j <= len; j++) {
                dp[j] = dp[j - 1];
                for (int k = 1; k <= mid; k++) {
                    if (j >= k && is_familiar[k] && dp[j - k] + k > dp[j]) {
                        dp[j] = dp[j - k] + k;
                    }
                }
            }
            if (dp[len] * 10 >= len * 9) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        printf("%d\n", left);
    }

    return 0;
}