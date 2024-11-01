#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000
#define MAXK 100000

int map[MAXN][MAXN];
int mountains[MAXN][MAXN];
int N, M, K;

typedef struct {
    int x, y;
} Point;

Point babingbaboom[MAXK];

int isMountain(int x, int y) {
    int height = map[x][y];
    if (x > 0 && map[x-1][y] >= height) return 0;
    if (x < N-1 && map[x+1][y] >= height) return 0;
    if (y > 0 && map[x][y-1] >= height) return 0;
    if (y < M-1 && map[x][y+1] >= height) return 0;
    return 1;
}

void findMountains() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (isMountain(i, j)) {
                mountains[i][j] = 1;
            }
        }
    }
}

int chebyshevDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) > abs(y1 - y2) ? abs(x1 - x2) : abs(y1 - y2);
}

int findNearestMountain(int x, int y) {
    int minDistance = INT_MAX;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (mountains[i][j] && i <= x) {
                int distance = chebyshevDistance(x, y, i, j);
                if (distance < minDistance) {
                    minDistance = distance;
                }
            }
        }
    }
    return minDistance == INT_MAX ? -1 : minDistance;
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

    findMountains();

    for (int i = 0; i < K; i++) {
        int result = findNearestMountain(babingbaboom[i].x, babingbaboom[i].y);
        if (result == -1) {
            printf("Pool Babingbaboom!\n");
        } else {
            printf("%d\n", result);
        }
    }

    return 0;
}