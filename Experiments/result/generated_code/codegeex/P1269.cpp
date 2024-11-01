#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 20001

struct Edge {
    int to;
    int weight;
};

int n;
struct Edge graph[MAXN][MAXN];
int maxDecay[MAXN];
int signalStrength;
int visited[MAXN];

void dfs(int node, int currentDecay) {
    visited[node] = 1;
    for (int i = 0; i < maxDecay[node]; i++) {
        int nextNode = graph[node][i].to;
        int nextDecay = graph[node][i].weight;
        if (!visited[nextNode]) {
            dfs(nextNode, currentDecay + nextDecay);
            maxDecay[node] = currentDecay + nextDecay;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        maxDecay[i] = INT_MIN;
        for (int j = 0; j < k; j++) {
            int to, weight;
            scanf("%d %d", &to, &weight);
            graph[i][j].to = to;
            graph[i][j].weight = weight;
            maxDecay[i] = (maxDecay[i] < weight) ? weight : maxDecay[i];
        }
    }
    scanf("%d", &signalStrength);

    int root = 1;
    dfs(root, 0);

    int totalAmplifiers = 0;
    for (int i = 1; i <= n; i++) {
        if (maxDecay[i] >= signalStrength) {
            totalAmplifiers++;
        }
    }

    if (totalAmplifiers == 0) {
        printf("No solution.\n");
    } else {
        printf("%d\n", totalAmplifiers);
    }

    return 0;
}