#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int n, m;
int station_level[MAXN];
int visited[MAXN];
int max_level;

void dfs(int station, int level) {
    if (station_level[station] < level) {
        station_level[station] = level;
        if (level > max_level) {
            max_level = level;
        }
    }
    if (visited[station] >= level) {
        return;
    }
    visited[station] = level;
    for (int i = 1; i <= n; i++) {
        if (station_level[i] >= level) {
            dfs(i, level + 1);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        station_level[i] = 1;
        visited[i] = 0;
    }
    max_level = 1;

    for (int i = 0; i < m; i++) {
        int s;
        scanf("%d", &s);
        int stations[s];
        for (int j = 0; j < s; j++) {
            scanf("%d", &stations[j]);
        }
        for (int j = 0; j < s; j++) {
            for (int k = j + 1; k < s; k++) {
                if (station_level[stations[k]] < station_level[stations[j]] + 1) {
                    station_level[stations[k]] = station_level[stations[j]] + 1;
                    if (station_level[stations[k]] > max_level) {
                        max_level = station_level[stations[k]];
                    }
                }
            }
        }
    }

    printf("%d\n", max_level);
    return 0;
}