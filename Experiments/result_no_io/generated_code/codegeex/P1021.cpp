#include <stdio.h>
#include <stdbool.h>

int N, K;
int maxn = 0;
int a[20], b[20];

bool check(int n, int k) {
    int i, j;
    int f[10000];
    for (i = 0; i <= n * 100; i++) f[i] = 0x3f3f3f3f;
    f[0] = 0;
    for (i = 1; i <= k; i++) {
        for (j = a[i]; j <= n * 100; j++) {
            f[j] = f[j] < f[j - a[i]] + 1 ? f[j] : f[j - a[i]] + 1;
        }
    }
    for (i = 1; i <= n * 100; i++) {
        if (f[i] > n) return false;
    }
    return true;
}

void dfs(int n, int k, int sum) {
    if (n == 0) {
        if (k > maxn) {
            maxn = k;
            for (int i = 1; i <= K; i++) b[i] = a[i];
        }
        return;
    }
    if (sum > maxn) return;
    for (int i = 1; i <= K; i++) {
        if (i != 1 && a[i] <= a[i - 1]) continue;
        a[i] = n - sum + 1;
        if (a[i] > 0 && check(n, K)) {
            dfs(n, k + 1, sum + a[i]);
        }
        a[i] = 0;
    }
}

int main() {
    scanf("%d%d", &N, &K);
    dfs(N, 0, 0);
    for (int i = 1; i <= K; i++) printf("%d ", b[i]);
    printf("\nMAX=%d\n", maxn);
    return 0;
}