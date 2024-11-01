#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000
#define MAX_K 100000
#define INF 1000000000

int N, M, K;
int h[MAX_N][MAX_M];
int is_mountain[MAX_N][MAX_M];
int dist[MAX_N][MAX_M];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void find_mountains() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            is_mountain[i][j] = 1;
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < N && nj >= 0 && nj < M && h[ni][nj] > h[i][j]) {
                    is_mountain[i][j] = 0;
                    break;
                }
            }
        }
    }
}

void calculate_distances() {
    for (int j = 0; j < M; j++) {
        int last_mountain = INF;
        for (int i = N - 1; i >= 0; i--) {
            if (is_mountain[i][j]) {
                last_mountain = i;
            }
            dist[i][j] = last_mountain == INF ? INF : last_mountain - i;
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &h[i][j]);
        }
    }

    find_mountains();
    calculate_distances();

    for (int k = 0; k < K; k++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;

        int min_dist = INF;
        for (int j = 0; j < M; j++) {
            if (dist[x][j] != INF) {
                int d = dist[x][j] + abs(j - y);
                if (d < min_dist) {
                    min_dist = d;
                }
            }
        }

        if (min_dist == INF) {
            printf("Pool Babingbaboom!\n");
        } else {
            printf("%d\n", min_dist);
        }
    }

    return 0;
}