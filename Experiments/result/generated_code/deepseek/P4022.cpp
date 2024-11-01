#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1100000
#define MAX_M 1000

char standard_essays[MAX_M][MAX_LEN];
char essays[MAX_LEN];
int dp[MAX_LEN];
int max_len[MAX_LEN];

bool is_substring(char *str, char *sub, int len) {
    for (int i = 0; i <= strlen(str) - len; i++) {
        if (strncmp(str + i, sub, len) == 0) {
            return true;
        }
    }
    return false;
}

int calculate_L0(char *essay, int M) {
    int len = strlen(essay);
    int left = 1, right = len, L0 = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        bool found = false;

        for (int i = 0; i < M; i++) {
            if (is_substring(standard_essays[i], essay, mid)) {
                found = true;
                break;
            }
        }

        if (found) {
            L0 = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return L0;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%s", standard_essays[i]);
    }

    for (int i = 0; i < N; i++) {
        scanf("%s", essays);
        int L0 = calculate_L0(essays, M);
        printf("%d\n", L0);
    }

    return 0;
}