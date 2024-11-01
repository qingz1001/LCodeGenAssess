#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50

int n, m, k;
int r[MAXN], d[MAXN];
int castles[MAXN];
int dist[MAXN];

void dijkstra(int start) {
    int visited[MAXN] = {0};
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int minDist = INT_MAX, minIndex = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        if (minIndex == -1) break;
        visited[minIndex] = 1;

        int next = r[minIndex];
        if (!visited[next] && dist[minIndex] + d[minIndex] < dist[next]) {
            dist[next] = dist[minIndex] + d[minIndex];
        }
    }
}

int minMaxDist() {
    int maxDist = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] > maxDist) {
            maxDist = dist[i];
        }
    }
    return maxDist;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &r[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &castles[i]);
    }

    int minMax = INT_MAX;
    for (int i = 0; i < m; i++) {
        dijkstra(castles[i]);
        int currentMax = minMaxDist();
        if (currentMax < minMax) {
            minMax = currentMax;
        }
    }

    printf("%d\n", minMax);
    return 0;
}