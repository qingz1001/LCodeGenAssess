#include <stdio.h>
#include <limits.h>

#define MAX_N 100

int main() {
    int n;
    scanf("%d", &n);

    int dist[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    int min_dist = 0;
    int visited[MAX_N] = {0};
    int current = 0;

    for (int i = 0; i < n; i++) {
        int min = INT_MAX;
        int next = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[current][j] < min) {
                min = dist[current][j];
                next = j;
            }
        }

        if (next == -1) {
            break;
        }

        min_dist += min;
        visited[next] = 1;
        current = next;
    }

    printf("%d\n", min_dist);
    return 0;
}