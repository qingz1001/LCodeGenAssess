#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 50
#define INF 1000000000

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
        for (int j = 0; j < m; j++) {
            if (dist[i][castle[j]] < min_dist) {
                min_dist = dist[i][castle[j]];
            }
        }
        if (min_dist > mid) {
            count++;
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
    for (int i = 0; i < m; i++) {
        scanf("%d", &castle[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
        dist[i][r[i]] = d[i];
        dist[r[i]][i] = d[i];
    }

    floyd();
    int result = binary_search();
    printf("%d\n", result);

    return 0;
}