#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 501
#define MAX_P 801
#define MAX_C 1451
#define INF INT_MAX

int N, P, C;
int cow_locations[MAX_N];
int dist[MAX_P][MAX_P];
int total_dist[MAX_P];

void floyd_warshall() {
    for (int k = 1; k <= P; k++) {
        for (int i = 1; i <= P; i++) {
            for (int j = 1; j <= P; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &P, &C);

    for (int i = 0; i < N; i++) {
        scanf("%d", &cow_locations[i]);
    }

    for (int i = 1; i <= P; i++) {
        for (int j = 1; j <= P; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 0; i < C; i++) {
        int A, B, D;
        scanf("%d %d %d", &A, &B, &D);
        dist[A][B] = D;
        dist[B][A] = D;
    }

    floyd_warshall();

    int min_total_dist = INF;
    for (int i = 1; i <= P; i++) {
        total_dist[i] = 0;
        for (int j = 0; j < N; j++) {
            if (dist[cow_locations[j]][i] == INF) {
                total_dist[i] = INF;
                break;
            }
            total_dist[i] += dist[cow_locations[j]][i];
        }
        if (total_dist[i] < min_total_dist) {
            min_total_dist = total_dist[i];
        }
    }

    printf("%d\n", min_total_dist);

    return 0;
}