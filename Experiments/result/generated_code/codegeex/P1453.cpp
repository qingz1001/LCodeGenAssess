#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

int n;
int p[MAXN];
int u[MAXN], v[MAXN];
int vis[MAXN];
int cnt = 0;
int ans = 0;

int cmp(const void *a, const void *b) {
    return p[*(int*)b] - p[*(int*)a];
}

int main() {
    // 读取点的个数
    scanf("%d", &n);
    
    // 读取每个点的人流量
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    
    // 读取边的信息
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &u[i], &v[i]);
    }
    
    // 对人流量进行排序
    qsort(p, n, sizeof(int), cmp);
    
    // 找到环并标记环上的点
    for (int i = 0; i < n; i++) {
        if (!vis[u[i]] && !vis[v[i]]) {
            vis[u[i]] = 1;
            vis[v[i]] = 1;
            cnt++;
        }
    }
    
    // 计算最大利润
    for (int i = 0; i < cnt; i++) {
        ans += p[i];
    }
    
    // 读取常数 k
    double k;
    scanf("%lf", &k);
    
    // 输出结果，保留一位小数
    printf("%.1lf\n", ans * k);
    
    return 0;
}