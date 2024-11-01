#include <stdio.h>
#include <string.h>

#define MAXN 40005
#define MAXQ 100005
#define MAXS 200005

char s[MAXN][MAXS];
int n, q, x[MAXQ], y[MAXQ];
int f[MAXN], fa[MAXN], val[MAXN], cnt[MAXN], ans[MAXN], tot;

void init() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        val[i] = cnt[i] = 0;
    }
}

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        fa[fx] = fy;
        val[fy] += val[fx];
        cnt[fy] += cnt[fx];
    }
}

int main() {
    // 读取输入
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i]);
        f[i] = strlen(s[i]);
    }
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }

    // 初始化并查集
    init();

    // 计算每个字符串的哈希值并排序
    for (int i = 1; i <= n; i++) {
        merge(i, i - 1);
    }

    // 输出最大价值
    printf("%d\n", val[find(1)] * val[find(1)]);

    // 处理附加任务
    for (int i = 1; i <= q; i++) {
        int fx = find(x[i]), fy = find(y[i]);
        if (fx != fy) {
            merge(fx, fy);
            ans[++tot] = i;
        }
    }

    // 输出满足附加任务的数量和任务序号
    printf("%d ", tot);
    for (int i = 1; i <= tot; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    // 输出排列 P^*_B
    for (int i = 1; i <= n; i++) {
        printf("%d ", find(i));
    }
    printf("\n");

    return 0;
}