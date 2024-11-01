#include <stdio.h>
#include <stdlib.h>

#define MAXN 75
#define INF 0x3f3f3f3f

typedef struct Node {
    int data, freq, weight;
    int index;
} Node;

Node nodes[MAXN];
int dp[MAXN][MAXN][MAXN];

int cmp(const void *a, const void *b) {
    return ((Node *)a)->data - ((Node *)b)->data;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nodes[i].data);
        nodes[i].index = i;
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nodes[i].weight);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nodes[i].freq);
    }
    
    qsort(nodes + 1, n, sizeof(Node), cmp);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int l = 1; l <= n; l++) {
                dp[i][j][l] = INF;
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        dp[i][i][nodes[i].index] = nodes[i].freq;
    }
    
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            for (int l = i; l <= j; l++) {
                for (int x = i; x <= l - 1; x++) {
                    for (int y = l + 1; y <= j; y++) {
                        int cost = dp[i][x][l] + dp[x + 1][l][l] + dp[l + 1][y][l] + dp[y + 1][j][l] + k;
                        dp[i][j][l] = min(dp[i][j][l], cost);
                    }
                }
            }
        }
    }
    
    int ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[1][n][i]);
    }
    
    printf("%d\n", ans);
    return 0;
}