#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 55
#define MAXS 105

int n;
int s[MAXN];
char magic[MAXN][MAXS][MAXS];
bool can_upgrade[MAXN][MAXN];
int dp[MAXN];

bool is_subsequence(char *a, char *b) {
    int i = 0, j = 0;
    while (a[i] && b[j]) {
        if (a[i] == b[j]) i++;
        j++;
    }
    return !a[i];
}

bool can_upgrade_from_to(int a, int b) {
    for (int i = 0; i < s[a]; i++) {
        for (int j = 0; j < s[b]; j++) {
            if (is_subsequence(magic[a][i], magic[b][j])) {
                return true;
            }
        }
    }
    return false;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
        for (int j = 0; j < s[i]; j++) {
            scanf("%s", magic[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                can_upgrade[i][j] = can_upgrade_from_to(i, j);
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