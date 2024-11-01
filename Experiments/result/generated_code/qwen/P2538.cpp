#include <stdio.h>
#include <stdlib.h>

#define MAXN 50

int n, m, k;
int r[MAXN], d[MAXN];
int castle[MAXN];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int bfs(int dist[]) {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 0; i < n; i++) {
        if (castle[i]) {
            queue[rear++] = i;
            dist[i] = 0;
        } else {
            dist[i] = -1;
        }
    }

    while (front != rear) {
        int u = queue[front++];
        for (int i = 0; i < n; i++) {
            if (r[u] == i && dist[u] + d[u] < dist[i]) {
                dist[i] = dist[u] + d[u];
                queue[rear++] = i;
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        if (!castle[i] && dist[i] != -1) {
            result = max(result, dist[i]);
        }
    }

    return result;
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
        scanf("%d", &castle[i]);
    }

    int left = 0, right = 1000000, best = 1000000;
    while (left <= right) {
        int mid = (left + right) / 2;
        int dist[MAXN];
        if (bfs(dist) <= mid) {
            best = min(best, mid);
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", best);

    return 0;
}