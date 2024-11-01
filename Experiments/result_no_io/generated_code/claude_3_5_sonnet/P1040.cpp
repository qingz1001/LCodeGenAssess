#include <stdio.h>
#include <string.h>

#define MAX_N 30

long long dp[MAX_N][MAX_N];
int root[MAX_N][MAX_N];
int score[MAX_N];
int n;

void init() {
    memset(dp, 0, sizeof(dp));
    memset(root, 0, sizeof(root));
}

long long max(long long a, long long b) {
    return a > b ? a : b;
}

void solve() {
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][j] = score[i];
                root[i][j] = i;
            } else {
                for (int k = i; k <= j; k++) {
                    long long left = (k == i) ? 1 : dp[i][k-1];
                    long long right = (k == j) ? 1 : dp[k+1][j];
                    long long total = left * right + score[k];
                    if (total > dp[i][j]) {
                        dp[i][j] = total;
                        root[i][j] = k;
                    }
                }
            }
        }
    }
}

void print_preorder(int i, int j) {
    if (i > j) return;
    int r = root[i][j];
    printf("%d ", r);
    if (i == j) return;
    print_preorder(i, r-1);
    print_preorder(r+1, j);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &score[i]);
    }

    init();
    solve();

    printf("%lld\n", dp[1][n]);
    print_preorder(1, n);
    printf("\n");

    return 0;
}