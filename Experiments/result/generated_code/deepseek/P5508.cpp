#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50000
#define MAXM 50000

typedef struct {
    int s_l, s_r, t_l, t_r, w;
} TunnelGroup;

int n, m;
int v[MAXN + 1];
TunnelGroup tunnels[MAXM];

int minTime = INT_MAX;
int bestPath[MAXN + 1];
int pathCount = 0;

void findMinTime(int current, int time, int path[], int pathLen) {
    if (current == n) {
        if (time < minTime) {
            minTime = time;
            pathCount = pathLen;
            for (int i = 0; i < pathLen; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }

    for (int i = 0; i < m; i++) {
        if (current >= tunnels[i].s_l && current <= tunnels[i].s_r) {
            for (int j = tunnels[i].t_l; j <= tunnels[i].t_r; j++) {
                path[pathLen] = j;
                findMinTime(j, time + tunnels[i].w, path, pathLen + 1);
            }
        }
    }

    if (v[current] != 0) {
        for (int j = current + 1; j <= n; j++) {
            if (v[j] != 0) {
                path[pathLen] = j;
                findMinTime(j, time + abs(current - j) * v[current], path, pathLen + 1);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d %d", &tunnels[i].s_l, &tunnels[i].s_r, &tunnels[i].t_l, &tunnels[i].t_r, &tunnels[i].w);
    }

    int path[MAXN + 1];
    path[0] = 1;
    findMinTime(1, 0, path, 1);

    if (minTime == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", minTime);
        if (pathCount > 0) {
            printf("%d\n", pathCount);
            for (int i = 0; i < pathCount; i++) {
                printf("%d ", bestPath[i]);
            }
            printf("\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}