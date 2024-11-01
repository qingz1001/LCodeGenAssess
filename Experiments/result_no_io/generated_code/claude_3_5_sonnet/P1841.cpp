#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 201
#define MAX_M 20000
#define INF 1000000000

int N, M;
int dist[MAX_N][MAX_N];
int original_dist[MAX_N][MAX_N];

void floyd_warshall() {
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int is_important(int city) {
    for (int i = 1; i <= N; i++) {
        if (i == city) continue;
        for (int j = i + 1; j <= N; j++) {
            if (j == city) continue;
            if (dist[i][j] > original_dist[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        dist[a][b] = dist[b][a] = c;
    }

    floyd_warshall();
    memcpy(original_dist, dist, sizeof(dist));

    int important_count = 0;
    for (int city = 1; city <= N; city++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i == city || j == city) {
                    dist[i][j] = INF;
                } else {
                    dist[i][j] = original_dist[i][j];
                }
            }
        }

        floyd_warshall();

        if (is_important(city)) {
            if (important_count > 0) {
                printf(" ");
            }
            printf("%d", city);
            important_count++;
        }
    }

    if (important_count == 0) {
        printf("No important cities.\n");
    } else {
        printf("\n");
    }

    return 0;
}