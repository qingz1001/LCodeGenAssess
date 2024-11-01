#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
int n, p[MAXN], w[MAXN], c[MAXN], dp[MAXN];
vector<int> tree[MAXN];

void dfs(int u) {
    dp[u] = 1; // 初始化自身长度为1
    for (int v : tree[u]) {
        dfs(v); // 递归处理子节点
        if (dp[v] + 1 <= c[u] - w[u]) {
            dp[u] = max(dp[u], dp[v] + 1); // 更新dp[u]
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &p[i]);
        tree[p[i]].push_back(i); // 建树
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &w[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);
    }
    dfs(1); // 从根节点开始DFS
    for (int i = 1; i <= n; ++i) {
        printf("%d ", dp[i]);
    }
    printf("\n");
    return 0;
}