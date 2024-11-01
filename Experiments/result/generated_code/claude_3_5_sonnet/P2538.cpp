#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define INF 0x3f3f3f3f

int n, m, k;
int r[MAX_N], d[MAX_N];
int castle[MAX_N];
int dist[MAX_N][MAX_N];

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int check(int mid) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        int min_dist = INF;
        for (int j = 0; j < n; j++) {
            if (castle[j] && dist[i][j] < min_dist) {
                min_dist = dist[i][j];
            }
        }
        if (min_dist > mid) {
            count++;
            castle[i] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!castle[i]) {
            castle[i] = 0;
        }
    }
    return count <= k;
}

int binary_search() {
    int left = 0, right = INF;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &r[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    memset(dist, 0x3f, sizeof(dist));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        dist[i][r[i]] = dist[r[i]][i] = d[i];
    }

    floyd();

    memset(castle, 0, sizeof(castle));
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        castle[x] = 1;
    }

    printf("%d\n", binary_search());

    return 0;
}