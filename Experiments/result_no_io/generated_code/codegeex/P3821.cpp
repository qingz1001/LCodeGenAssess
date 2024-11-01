#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 51
#define INF 0x3f3f3f3f

int n, m, s, t, k;
int adj[MAXN][MAXN];
int minBlood[MAXN][200001];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                adj[i][j] = adj[i][j] < adj[i][k] + adj[k][j] ? adj[i][j] : adj[i][k] + adj[k][j];
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    memset(adj, INF, sizeof(adj));
    memset(minBlood, INF, sizeof(minBlood));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        adj[u][v] = w;
        adj[v][u] = w;
    }

    floyd();

    int a;
    scanf("%d", &a);

    for (int i = 1; i <= n; i++) {
        minBlood[i][0] = 0;
    }

    for (int i = 1; i <= a; i++) {
        int T;
        scanf("%d", &T);
        int rooms[T];
        for (int j = 0; j < T; j++) {
            scanf("%d", &rooms[j]);
        }

        for (int j = 1; j <= k; j++) {
            for (int l = 0; l < T; l++) {
                int currentRoom = rooms[l];
                for (int m = 1; m <= n; m++) {
                    if (adj[m][currentRoom] != INF) {
                        minBlood[m][j] = minBlood[m][j] < minBlood[m][j - 1] ? minBlood[m][j] : minBlood[m][j - 1];
                        minBlood[m][j] = minBlood[m][j] < minBlood[currentRoom][j - 1] + adj[m][currentRoom] ? minBlood[m][j] : minBlood[currentRoom][j - 1] + adj[m][currentRoom];
                    }
                }
            }
        }
    }

    if (minBlood[t][k] == INF) {
        printf("IMP0SSBLE!!");
    } else {
        printf("%d", minBlood[t][k]);
    }

    return 0;
}