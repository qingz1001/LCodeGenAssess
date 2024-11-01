#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 50
#define MAXS 25

int n;
char machines[MAXN][MAXS][MAXS];
int m[MAXN];
bool can_upgrade[MAXN][MAXN];
int dp[MAXN];

bool is_submachine(int a, int b) {
    for (int i = 0; i < m[b]; i++) {
        bool found = false;
        for (int j = 0; j < m[a]; j++) {
            if (strcmp(machines[b][i], machines[a][j]) == 0) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m[i]);
        for (int j = 0; j < m[i]; j++) {
            scanf("%s", machines[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && is_submachine(i, j)) {
                can_upgrade[i][j] = true;
            }
        }
    }

    int max_length = 0;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (can_upgrade[j][i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_length = max(max_length, dp[i]);
    }

    printf("%d\n", max_length);
    return 0;
}