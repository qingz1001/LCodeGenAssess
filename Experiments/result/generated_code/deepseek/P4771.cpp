#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000
#define MAXK 100000

int map[MAXN][MAXN];
int N, M, K;

typedef struct {
    int x, y;
} Point;

Point babingbaboom[MAXK];

int isMountain(int x, int y) {
    int h = map[x][y];
    if (x > 0 && map[x-1][y] > h) return 0;
    if (x < N-1 && map[x+1][y] > h) return 0;
    if (y > 0 && map[x][y-1] > h) return 0;
    if (y < M-1 && map[x][y+1] > h) return 0;
    return 1;
}

int chebyshevDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) > abs(y1 - y2) ? abs(x1 - x2) : abs(y1 - y2);
}

int main() {
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &map[i][j]);
        }
    }
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &babingbaboom[i].x, &babingbaboom[i].y);
    }

    for (int i = 0; i < K; i++) {
        int minDist = INT_MAX;
        int found = 0;
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < M; y++) {
                if (isMountain(x, y) && x <= babingbaboom[i].x) {
                    int dist = chebyshevDistance(babingbaboom[i].x, babingbaboom[i].y, x, y);
                    if (dist < minDist) {
                        minDist = dist;
                        found = 1;
                    }
                }
            }
        }
        if (found) {
            printf("%d\n", minDist);
        } else {
            printf("Pool Babingbaboom!\n");
        }
    }

    return 0;
}