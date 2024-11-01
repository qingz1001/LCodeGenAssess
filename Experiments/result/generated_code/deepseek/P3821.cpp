#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ROOMS 50
#define MAX_EDGES 1250
#define IMPOSSIBLE "IMP0SSBLE!!"

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    int room;
    int time;
} MonsterPath;

int n, m, s, t, k;
Edge edges[MAX_EDGES];
MonsterPath monsters[MAX_ROOMS];
int monsterCount;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int canReach(int blood) {
    int dp[MAX_ROOMS][k + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = INT_MAX;
        }
    }
    dp[s - 1][0] = 0;

    for (int time = 0; time < k; time++) {
        for (int i = 0; i < m; i++) {
            int u = edges[i].u - 1;
            int v = edges[i].v - 1;
            int w = edges[i].w;
            if (w <= blood) {
                if (dp[u][time] != INT_MAX) {
                    dp[v][time + 1] = min(dp[v][time + 1], dp[u][time] + w);
                }
                if (dp[v][time] != INT_MAX) {
                    dp[u][time + 1] = min(dp[u][time + 1], dp[v][time] + w);
                }
            }
        }
    }

    for (int i = 0; i < monsterCount; i++) {
        int monsterRoom = monsters[i].room - 1;
        int monsterTime = monsters[i].time;
        if (dp[monsterRoom][monsterTime] != INT_MAX) {
            return 0;
        }
    }

    return dp[t - 1][k] != INT_MAX;
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &s, &t, &k);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    scanf("%d", &monsterCount);
    for (int i = 0; i < monsterCount; i++) {
        int T;
        scanf("%d", &T);
        int path[4];
        for (int j = 0; j < T; j++) {
            scanf("%d", &path[j]);
        }
        for (int j = 0; j < k; j++) {
            monsters[i].room = path[j % T];
            monsters[i].time = j;
        }
    }

    int low = 0, high = INT_MAX;
    int result = INT_MAX;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canReach(mid)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (result == INT_MAX) {
        printf("%s\n", IMPOSSIBLE);
    } else {
        printf("%d\n", result);
    }

    return 0;
}