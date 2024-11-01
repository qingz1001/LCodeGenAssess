#include <stdio.h>
#include <string.h>

#define MAX_N 30

long long dp[MAX_N][MAX_N];
int root[MAX_N][MAX_N];
int score[MAX_N];
int n;

void print_preorder(int left, int right) {
    if (left > right) return;
    int r = root[left][right];
    printf("%d ", r);
    if (left == right) return;
    print_preorder(left, r - 1);
    print_preorder(r + 1, right);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &score[i]);
        dp[i][i] = score[i];
        root[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = 0;
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

    printf("%lld\n", dp[1][n]);
    print_preorder(1, n);
    printf("\n");

    return 0;
}