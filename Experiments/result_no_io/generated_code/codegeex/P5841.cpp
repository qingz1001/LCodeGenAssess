#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 40005
#define MAXQ 100005
#define MAXS 200005

char s[MAXN][MAXS];
int n, q, ans[MAXN], pos[MAXN], cnt[MAXN];
bool ok[MAXN], used[MAXN];

void dfs(int u) {
    ok[u] = true;
    for (int i = 0; i < cnt[u]; i++) {
        int v = ans[cnt[u] - i - 1];
        if (!ok[v]) dfs(v);
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) scanf("%s", s[i]);

    // 计算每个字符串的哈希值和前缀哈希值
    for (int i = 0; i < n; i++) {
        int len = strlen(s[i]);
        for (int j = 0; j < len; j++) {
            s[i][j] -= 'a';
        }
    }

    // 计算最长公共前缀
    for (int i = 1; i < n; i++) {
        int len1 = strlen(s[i - 1]), len2 = strlen(s[i]), lcp = 0;
        for (int j = 0; j < len1 && j < len2; j++) {
            if (s[i - 1][j] == s[i][j]) lcp++;
            else break;
        }
        ans[i] = lcp;
        cnt[i - 1]++;
    }

    // 深度优先搜索，找到最大价值排列
    dfs(0);

    // 输出最大价值
    printf("%d\n", ans[n - 1] * ans[n - 1]);

    // 处理附加任务
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x > y) {
            int temp = x;
            x = y;
            y = temp;
        }
        if (ok[x - 1] && !ok[y - 1]) {
            used[i] = true;
        }
    }

    // 输出满足附加任务的数量和序号
    printf("%d ", 0);
    for (int i = 0; i < q; i++) {
        if (used[i]) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    // 输出满足最大价值条件的排列
    for (int i = 0; i < n; i++) {
        if (ok[i]) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    return 0;
}