#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = 1000005;
const int MAXM = 1000005;

struct Edge {
    int to, next;
} edges[MAXN * 2];

int head[MAXN], edgeCount;
int n, m;
char treeChars[MAXN];
char pattern[MAXM];
int dp[MAXM][26];
int dpCount[MAXM];
int dpRoot[MAXM];
int dpDepth[MAXM];
int dpSize[MAXM];
int dpParent[MAXM];
int dpChildrenCount[MAXM];
int dpChildren[MAXN * 2];
int dpChildrenHead[MAXN];
int dpChildrenIndex;
int result;

void addEdge(int u, int v) {
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dfs(int node, int parent) {
    dp[0][treeChars[node] - 'A'] = 1;
    dpCount[0]++;
    dpRoot[0] = node;
    dpDepth[0] = 0;
    dpSize[0] = 1;
    dpParent[0] = parent;
    dpChildrenCount[0] = 0;
    dpChildrenHead[node] = -1;
    dpChildrenIndex = 0;

    for (int i = head[node]; i != -1; i = edges[i].next) {
        int neighbor = edges[i].to;
        if (neighbor == parent) continue;
        dfs(neighbor, node);
        int neighborDepth = dpDepth[0];
        int neighborSize = dpSize[0];
        int neighborChildrenCount = dpChildrenCount[0];
        int neighborChildrenHead = dpChildrenHead[node];
        int neighborChildrenIndex = dpChildrenIndex;

        dp[0][treeChars[neighbor] - 'A'] = 1;
        dpCount[0]++;
        dpRoot[0] = node;
        dpDepth[0] = 0;
        dpSize[0] = 1;
        dpParent[0] = parent;
        dpChildrenCount[0] = 0;
        dpChildrenHead[node] = -1;
        dpChildrenIndex = 0;

        for (int j = 0; j <= neighborDepth; j++) {
            for (int k = 0; k < 26; k++) {
                if (dp[j][k] == 0) continue;
                for (int l = 0; l <= neighborDepth; l++) {
                    if (pattern[(j + l) % m] - 'A' != k) continue;
                    dp[j + l][k] = 1;
                    dpCount[j + l]++;
                    dpRoot[j + l] = node;
                    dpDepth[j + l] = j + l;
                    dpSize[j + l] = dpSize[j] + dpSize[l];
                    dpParent[j + l] = parent;
                    dpChildrenCount[j + l]++;
                    dpChildren[neighborChildrenIndex++] = j + l;
                    if (dpChildrenHead[node] == -1) {
                        dpChildrenHead[node] = dpChildrenIndex - 1;
                    }
                }
            }
        }

        dpDepth[0] += neighborDepth;
        dpSize[0] += neighborSize;
        dpChildrenCount[0] += neighborChildrenCount;
        dpChildrenHead[node] = neighborChildrenHead;
        dpChildrenIndex = neighborChildrenIndex;
    }

    for (int i = 0; i <= dpDepth[0]; i++) {
        if (dpCount[i] == m) {
            result++;
        }
    }
}

int main() {
    int C;
    scanf("%d", &C);

    while (C--) {
        scanf("%d %d", &n, &m);
        scanf("%s", treeChars);
        memset(head, -1, sizeof(head));
        edgeCount = 0;
        result = 0;

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }

        scanf("%s", pattern);

        dfs(1, -1);

        printf("%d\n", result);
    }

    return 0;
}