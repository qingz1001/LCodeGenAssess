#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 20;
const int MAXD = 100;
const int INF = INT_MAX;

struct Edge {
    int u, v, w;
};

vector<Edge> edges;
int n, m, k, e, d;
int days[MAXN + 1][MAXD + 1];
int dist[MAXN + 1][MAXN + 1];
int dp[MAXD + 1][1 << MAXN];

int main() {
    scanf("%d%d%d%d", &n, &m, &k, &e);
    
    // 读取航线信息
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edges.push_back({u, v, w});
        edges.push_back({v, u, w});
    }
    
    // 读取码头不可用信息
    scanf("%d", &d);
    for (int i = 0; i < d; ++i) {
        int p, a, b;
        scanf("%d%d%d", &p, &a, &b);
        for (int j = a; j <= b; ++j) {
            days[p][j] = 1;
        }
    }
    
    // 初始化距离矩阵
    memset(dist, 0x3f, sizeof(dist));
    for (const auto& edge : edges) {
        dist[edge.u][edge.v] = min(dist[edge.u][edge.v], edge.w);
        dist[edge.v][edge.u] = min(dist[edge.v][edge.u], edge.w);
    }
    
    // 使用Floyd-Warshall算法计算所有节点对之间的最短路径
    for (int k = 1; k <= m; ++k) {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (i != j && j != k && i != k) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // 初始化dp数组
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    
    // 动态规划求解最小总成本
    for (int i = 1; i <= n; ++i) {
        for (int mask = 0; mask < (1 << m); ++mask) {
            for (int j = 1; j <= m; ++j) {
                if (days[j][i]) continue;
                for (int u = 1; u <= m; ++u) {
                    if (mask & (1 << (u - 1))) {
                        int prev_mask = mask ^ (1 << (u - 1));
                        dp[i][mask] = min(dp[i][mask], dp[i - 1][prev_mask] + dist[u][j]);
                    }
                }
            }
        }
    }
    
    // 找到最小的总成本
    int ans = INF;
    for (int mask = 0; mask < (1 << m); ++mask) {
        ans = min(ans, dp[n][mask] + k * __builtin_popcount(mask));
    }
    
    printf("%d\n", ans);
    return 0;
}