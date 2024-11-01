#include <stdio.h>
#include <string.h>

int maxn, k, a[20], dp[20][1000], temp[20], ans[20], sum = 0;

void dfs(int cur, int cnt, int max) {
    if (cur == k + 1) {
        if (max > sum) {
            sum = max;
            memcpy(ans, temp, sizeof(temp));
        }
        return;
    }
    for (int i = cnt + 1; i <= maxn; i++) {
        temp[cur] = i;
        dfs(cur + 1, i, max + i);
    }
}

int main() {
    scanf("%d%d", &maxn, &k);
    dfs(1, 0, 0);

    for (int i = 1; i <= k; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    printf("MAX=%d\n", sum);

    return 0;
}