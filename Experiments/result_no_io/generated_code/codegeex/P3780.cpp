#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int MAXN = 20000;
const int MAXK = 500000;
const int MAXV = 100;

struct Node {
    int parent;
    int apples;
    int happiness;
};

int Q;
int n, k;
Node nodes[MAXN + 1];
int dp[MAXN + 1][MAXK + 1];
int h[MAXN + 1];
int inDegree[MAXN + 1];

vector<int> children[MAXN + 1];

void dfs(int u) {
    if (u != 1) {
        dfs(nodes[u].parent);
    }
    for (int i = 1; i <= k; ++i) {
        dp[u][i] = dp[nodes[u].parent][i - 1] + nodes[u].happiness;
    }
    for (int i = 1; i <= nodes[u].apples; ++i) {
        for (int j = k; j >= i; --j) {
            dp[u][j] = max(dp[u][j], dp[u][j - i] + nodes[u].happiness);
        }
    }
}

int main() {
    scanf("%d", &Q);
    while (Q--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; ++i) {
            scanf("%d %d %d", &nodes[i].parent, &nodes[i].apples, &nodes[i].happiness);
            children[nodes[i].parent].push_back(i);
            inDegree[nodes[i].parent]++;
        }

        memset(dp, 0, sizeof(dp));
        memset(h, 0, sizeof(h));

        dfs(1);

        int maxHappiness = 0;
        for (int i = 1; i <= k; ++i) {
            maxHappiness = max(maxHappiness, dp[1][i]);
        }

        printf("%d\n", maxHappiness);

        for (int i = 1; i <= n; ++i) {
            children[i].clear();
            inDegree[i] = 0;
        }
    }
    return 0;
}